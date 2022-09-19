#include <printf.h>
#include <string.h>
#include <libc/stdio.h>
#include <libc/string.h>

//void read_sectors_ATA_PIO(uint64_t target_address, uint64_t LBA, uint64_t sector_count);
//void write_sectors_ATA_PIO(uint64_t LBA, uint64_t sector_count, uint64_t* bytes);

bool ata_wait_until_not_busy(uint32_t timeout_ms);
void ata_send_command(unsigned char command);
void ata_select_drive(uint8_t drive);
void ata_interrupt_enable(bool enable);
bool ata_read_lba28(uint32_t LBA, uint8_t sectorCount, void* dest);
int ata_get_drive_count();