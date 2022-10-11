#include <printf.h>
#include <string.h>
#include <fs/ATA.h>
#include <libc/stdio.h>
#include <libc/string.h>
#include <fs/fs.h>

#ifndef DISK_H_INCLUDED
#include <fs/ATA.h>
#define DISK_H_INCLUDED
#endif

bool ata_wait_until_not_busy(uint32_t timeout_ms)
{
   /*uint8_t status = inb(0x1F7);
   uint32_t startTick = 0; //get_tick_count();
   while(status & 0x88) //BSY and DRQ must be clear
   {
      if(get_tick_count() > startTick + timeout_ms)
         return false;
      status = inb(0x1F7);
   }
   return true;*/
}

void ata_send_command(unsigned char command)
{
   outb(0x1F7, command);
}

void ata_select_drive(uint8_t drive)
{
   uint8_t buf = inb(0x1F6);
   if(drive)
      buf |= 0x10; //set bit 4
   
   buf = 0;
   
   outb(0x1F6, buf);
   nlog_info("Selected drive: %d\n", drive);
}

int ata_get_drive_count(){
   uint8_t buf = inb(0x1F6);
   //if(drive)
   //   buf |= 0x10; //set bit 4
   
   //buf = 0;

   return buf;
}

void ata_interrupt_enable(bool enable)
{
   uint8_t buf = 0;
   if(enable)
      buf |= 2;
   
   outb(0x3F6, buf);
}

bool ata_read_lba28(uint32_t LBA, uint8_t sectorCount, void* dest)
{
   /*if(!ata_wait_until_not_busy(1000))
      return false;
   */
  
   outb(0x1F2, sectorCount); //sector count
   outb(0x1F3, LBA & 0xFF); //LBA low byte
   outb(0x1F4, (LBA >> 8) & 0xFF); //LBA mid byte
   outb(0x1F5, (LBA >> 16) & 0xFF); //LBA high byte
   outb(0x1F6, (LBA >> 24) & 0x0F); //bits 24-28 of LBA
   ata_select_drive(0);
   ata_interrupt_enable(false);
   ata_send_command(0x20); //read sectors with retry
   
   uint8_t status = 0;
   
   for(unsigned int i=0;i<4;i++)
   {
      status = inb(0x1F7);
      if(!(status & 0x80)) //BSY bit clear
      {
         if(status & 0x8) //DRQ bit set
            goto data_ready;
      }
   }
   
   while(1)
   {
      status = inb(0x1F7);
      if(status & 0x80) //BSY set
         continue;
      else
         break;
      
      if(status & 0x1) //ERR set
         return false;
      
      if(status & 0x20) //DF set
         return false;
   }
   
   
data_ready: ;
   
   uint16_t* p = (uint16_t*)dest;
   
   for(unsigned int i=0;i<sectorCount;i++)
   {
      for(unsigned int i=0;i<256;i++)
      {
         *p = inw(0x1F0);
         p++;
      }
      
      inb(0x1F7);
      inb(0x1F7);
      inb(0x1F7);
      inb(0x1F7);//400ns delay
      
      while(1)
      {
         status = inb(0x1F7);
         if(status & 0x80) //BSY set
            continue;
         else
            break;
         
         if(status & 0x1) //ERR set
            return false;
         
         if(status & 0x20) //DF set
            return false;
      }
   }
   
   return true;
}