#include <elf/elf.h>

elf_header_t * elf_get_header(void * address)
{
    return (elf_header_t *) address;
}
elf_section_header_t * elf_get_section_header(elf_header_t * header, void * address)
{
    return (elf_section_header_t *) (address + header->shoffset);
}