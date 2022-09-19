/**
 * @file ustar.h
 * @author xyve
 * 
 * ELF file.
 * 
 */

#ifndef USTAR_H
#define USTAR_H

#include <stdint.h>
#include <stddef.h>
#include <libc/string.h>

enum ustar_type
{
	normal_file = 0x30,
	hard_link = 0x31,
	sym_link = 0x32,
	char_dev = 0x33,
	block_dev = 0x34,
	directory = 0x35,
	fifo = 0x36
};

typedef struct ustar_header
{
	uint8_t file_name[100];
	uint8_t file_mode[8];
	uint8_t owner_num_user_id[8];
	uint8_t group_num_user_id[8];
	uint8_t file_size[12];
	uint8_t last_mod_time[12];
	uint8_t checksum[8];
	uint8_t type;
	uint8_t linked_file_name[100];
	uint8_t ustar[6];
	uint8_t ustar_version[2];
	uint8_t owner_user_name[32];
	uint8_t owner_group_name[32];
	uint8_t device_major_number[8];
	uint8_t device_minor_number[8];
	uint8_t file_name_prefix[155];
	uint8_t padding[12];

} __attribute__((packed)) ustar_header_t;

size_t ustar_octal_to_int(const unsigned char* octal_str, uint8_t size);

#endif