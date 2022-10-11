#include <elf/elf.h>

elf_section_header_t * elf_find_section_header(void * address, const char * name)
{
	elf_header_t * f_header = (elf_header_t*) address;
	elf_section_header_t * f_section_header = (elf_section_header_t*) (address + f_header->shoffset);
	elf_section_header_t * f_strtab = (elf_section_header_t*) &f_section_header[f_header->shstrndx];

	const char * sh_strtab = (const char *) (address + f_strtab->offset);

	for (size_t i = 0; i < f_header->shnum; i++)
	{
		if(strcmp(name, sh_strtab + f_section_header[i].name) == 0)
			return &f_section_header[i];
	}
	return NULL;
}