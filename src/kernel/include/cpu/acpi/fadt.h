/**
 * @file fadt.h
 * @author xyve
 * 
 * Resources used:
 *      https://wiki.osdev.org/FADT
 * 
 */
#ifndef FADT_H
#define FADT_H

#include <cpu/acpi/acpi.h>

typedef struct generic_addr_struct
{
    uint8_t addr_space;
    uint8_t bit_width;
    uint8_t bit_offset;
    uint8_t access_size;
    uint64_t addr;
} __attribute__((packed)) generic_addr_struct_t;

typedef struct fadt
{
    sdt_header_t header;
    uint32_t header_ctrl;
    uint32_t dsdt;
    uint8_t reserved;
    uint8_t preferred_power_management_profile;
    uint16_t sci_int;
    uint32_t smi_cmd_port;
    uint8_t acpi_enable;
    uint8_t acpi_disable;
    uint8_t s4_bios_req;
    uint8_t pstate_ctrl;
    uint32_t pm1a_event_block;
    uint32_t pm1b_event_block;
    uint32_t pm1a_ctrl_block;
    uint32_t pm1b_ctrl_block;
    uint32_t pm2_ctrl_block;
    uint32_t pm_timer_block;
    uint32_t gpe0_block;
    uint32_t gpe1_block;
    uint8_t pm1_event_length;
    uint8_t pm1_ctrl_length;
    uint8_t pm2_ctrl_length;
    uint8_t pm_timer_length;
    uint8_t gpe0_length;
    uint8_t gpe1_length;
    uint8_t gpe1_base;
    uint8_t cstate_ctrl;
    uint16_t worst_c2_latency;
    uint16_t worst_c3_latency;
    uint16_t flush_size;
    uint16_t flush_stride;
    uint8_t duty_offset;
    uint8_t duty_width;
    uint8_t day_alarm;
    uint8_t month_alarm;
    uint8_t century;
    uint16_t boot_arch_flags;
    uint8_t reserved2;
    uint32_t flags;
    generic_addr_struct_t reset_reg;
    uint8_t reset_val;
    uint8_t reserved3[3];
    uint64_t x_firmware_ctrl;
    uint64_t x_dsdt;
    generic_addr_struct_t x_pm1a_event_block;
    generic_addr_struct_t x_pm1b_event_block;
    generic_addr_struct_t x_pm1a_ctrl_block;
    generic_addr_struct_t x_pm1b_ctrl_block;
    generic_addr_struct_t x_pm2_ctrl_block;
    generic_addr_struct_t x_pm_timer_block;
    generic_addr_struct_t x_gpe0_block;
    generic_addr_struct_t x_gpe1_block;
}__attribute__((packed)) fadt_t;

#endif