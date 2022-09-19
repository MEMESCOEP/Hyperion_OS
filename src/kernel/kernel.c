#include <stdint.h>
#include <stddef.h>
#include <limine.h>
#include <term/term.h>
#include <libc/stdio.h>
#include <libc/string.h>
#include <cpu/cpu.h>
#include <neptunium/neptunium.h>
#include <utils/nlog.h>
#include <cpu/mm/pmm.h>
#include <cpu/mm/vmm.h>
#include <kernel.h>
#include <libc/stdlib.h>
#include <utils/vec.h>
#include <cpu/pci/pci.h>
#include <cpu/syscall/syscall.h>
#include <cpu/smp/smp.h>
#include <elf/elf.h>
#include <cpu/sched/sched.h>
#include <dev/mouse.h>
#include <fs/ustar.h>
#include <fs/ATA.h>
#include <include/checksum.h>

const char * notes = "Hyperion Notes:\n\tTAR Support\n";
char *username = "root";
char *cwd = "NoFS";

char *amoguslol = "   ______\n  /  ___ \\ \n |  [___] |__\n |        |  |\n |   __   |__|\n |  |  |  |\n |__|  |__|\n";

volatile struct limine_kernel_address_request kernel_address_request = {
    .id = LIMINE_KERNEL_ADDRESS_REQUEST,
    .revision = 0
};
volatile struct limine_hhdm_request hhdm_request = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0
};
volatile struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};

volatile struct limine_rsdp_request rsdp_request = {
    .id = LIMINE_RSDP_REQUEST,
    .revision = 0
};

volatile struct limine_smp_request smp_request = {
    .id = LIMINE_SMP_REQUEST,
    .revision = 0
};

volatile struct limine_module_request module_request = {
    .id = LIMINE_MODULE_REQUEST,
    .revision = 0
};

volatile struct limine_stack_size_request stack_size_request = {
    .id = LIMINE_STACK_SIZE_REQUEST,
    .revision = 0
};
volatile struct limine_framebuffer_request framebuffer_request = {
	.id = LIMINE_FRAMEBUFFER_REQUEST,
	.revision = 0
};
void kshell(void)
{
    char * input = NULL;
    size_t i = 0;
    int ch = 0;

    vec_str_t v;
    vec_init(&v);

    while(true)
    {
        printf("\e[0;32m[%s]\e[0m %s~$ ", username, cwd);
        while ((ch = getch()) != '\n')
        {
            if (ch == '\b')
            {
                if (i > 0)
                {
                    input = krealloc(input, i - 1);
                    putchar(ch);
                    i--;
                }
            }
            else 
            {
                input = krealloc(input, i + 1);
                input[i] = ch;
                putchar(ch);
                i++;
            }
        }
        input = krealloc(input, i + 1);
        input[i] = '\0';
        putchar(ch);
        i = 0;

        if (strcmp(input, "help") == 0)
        {
            printf("exit     - Exits the kernel shell\n");
            printf("echo     - Echos arguments passed\n");
            printf("crash    - Crashes the computer\n");
            printf("bruh     - Crashes the computer, but it's funni lol\n");
            printf("panic    - Panics the system\n");
            printf("lspci    - Lists all PCI devices\n");
            printf("history  - Shows the history of the commands\n");
            printf("clear    - Clears the screen\n");
            printf("version  - Prints the version\n");
            printf("notes    - Prints the notes\n");
			printf("smp      - SMP Info\n");
			printf("gui      - GUI Test\n");
			printf("ls       - Lists tar contents\n");
			printf("date     - Prints the date\n");
			printf("time     - Prints the time\n");
			printf("datetime - Prints the date and time\n");
            printf("read     - Reads file in tar\n");
            printf("uname    - Change your username\n");
            printf("pmminfo  - View PMM information\n");
            printf("license  - View the license\n");
            printf("abt      - View operating system information\n");
            printf("pong     - Play a game of pong!\n");
        }
        else if(strcmp(input, "amogus") == 0){
            printf("%s\n", amoguslol);
        }
        else if(strcmp(input, "reboot") == 0)
        {
            nlog_info("Rebooting...\n");
            reboot();
        }
        else if(strcmp(input, "shutdown") == 0)
        {
            nlog_info("Shutting down...\n");
            struct limine_rsdp_request limine_rsdp;
            //shutdown(limine_rsdp);
            
            poweroff();
        }
        else if (strcmp(input, "exit") == 0)
        {
            nlog_info("Exiting kernel shell...");
            break;
        }
        else if(strcmp(input, "dskr") == 0){
            uint64_t* target;
            int i = 0;
            //read_sectors_ATA_PIO(target, 0x0, 1);
            if(ata_get_drive_count() > 0 && ata_get_drive_count() < 255){
                //ata_select_drive(255 - ata_get_drive_count());
                //ata_read_lba28(1, 128, target);
                /*while(i < 128)
                {
                    printf("%x ", target[i] & 0xFF);
                    printf("%x ", (target[i] >> 8) & 0xFF);
                    i++;
                }*/

                if(ata_read_lba28(0, 1, (void*)0x00140000))
                    printf("success");
            }else{
                printf("There are no disks installed.\n");
            }
            
        }
        else if(strcmp(input, "dsks") == 0){
            if(ata_get_drive_count() > 0 && ata_get_drive_count() < 255){
                printf("%d\n", 255 - ata_get_drive_count());
            }else{
                printf("There are no disks installed.\n");
            }
        }
        else if(strncmp(input, "uname", 5) == 0)
        {
            char *un;
            if(strlen(input) < 7)
            {
                nlog_error("No arguments passed\n");
            }
            else 
            {
                un = input + 6;
                printf("Usename changed to \"%s\" from \"%s\"\n", un, username);
                username = un;
            }
        }
        else if(strcmp(input, "abt") == 0){
            printf("Hyperion Operating System (%s-%s-%s)\n", VERSION, BUILD, STATUS);
            printf("Made by Andrew Maney; Hyperion OS is based on xyve7's neptunium OS.\n");
            printf("You are free to use, modify, copy, and share any portion of this code as long as this license is kept visible in the about\nsection of ALL builds created with part or all of this code.\n");
        }
        else if(strcmp(input, "license") == 0){
            printf("You are free to use, modify, copy, and share any portion of this code as long as this license is kept visible in the about\nsection of ALL builds created with part or all of this code.\n");
            printf("This is free and unencumbered software released into the public domain.\nAnyone is free to copy, modify, publish, use, compile, sell, or distribute this software,\neither in source code form or as a compiled binary, for any purpose, commercial or non-commercial, and by any means.\nIn jurisdictions that recognize copyright laws, the author or authors of this software dedicate any and all copyright interest\nin the software to the public domain. We make this dedication for the benefit of the public at large and to the detriment of ourheirs and successors. We intend this dedication to be an overt act of relinquishment in perpetuity of all present and future\nrights to this software under copyright law. THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.\nIN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR\nOTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.\nFor more information, please refer to http://unlicense.org/\n");
        }
        else if(strcmp(input, "bruh") == 0){
            for(int i = 0; i < 69; i++){                
                printf("AMOGUS LMFAOOOOOOOOOOOOOO [iter: %d]\n%s\n", i+1, amoguslol);
            }
            int crash_num = 10 / 0;
            printf("%d\n", crash_num);
        }
        else if (strcmp(input, "notes") == 0)
        {
            printf(notes);
        }
        else if(strcmp(input, "pmminfo") == 0){
            pmm_info();
        }
        else if (strcmp(input, "pwd") == 0){
            printf("%s\n", cwd);
        }
        else if(strncmp(input, "echo", 4) == 0)
        {
            if(strlen(input) < 6)
            {
                nlog_error("No arguments passed\n");
            }
            else 
            {
                printf("%s\n", input + 5);
            }
        }
        else if(strcmp(input, "mousepos") == 0){
            mouse_init();
            mouse_handler(0xEB);
            while(1){
                printf("%d, %d\n", mouse_get_x(), mouse_get_y());
            }
        }
        else if(strcmp(input, "crash") == 0)
        {
            int crash_num = 10 / 0;
            printf("%d\n", crash_num);
        }
        else if(strcmp(input, "datetime") == 0)
        {
            printf("%s %s %02x %02x%02x %02x:%02x:%02x\n", rtc_get_weekday_str(), rtc_get_month_str(), rtc_get_day(), rtc_get_century(), rtc_get_year(), rtc_get_hours(), rtc_get_minutes(), rtc_get_seconds());
        }
        else if(strcmp(input, "time") == 0)
        {
            printf("%02x:%02x:%02x\n", rtc_get_hours(), rtc_get_minutes(), rtc_get_seconds(), rtc_get_century(), rtc_get_year());
        }
        else if(strcmp(input, "date") == 0)
        {
            printf("%s %s %02x %02x%02x\n", rtc_get_weekday_str(), rtc_get_month_str(), rtc_get_day(), rtc_get_century(), rtc_get_year());
        }
        else if(strcmp(input, "smp") == 0)
        {
            printf("SMP Debug\n");
            printf("CPU Count: %lu\n", smp_request.response->cpu_count);
            printf("BSP LAPIC ID: %lu\n", smp_request.response->bsp_lapic_id);

            for (uint64_t i = 0; i < smp_request.response->cpu_count; i++)
            {
                printf("CPU: %lu\n", i);
                printf("    Processor ID: %lu\n", smp_request.response->cpus[i]->processor_id);
                printf("    LAPIC ID: %lu\n", smp_request.response->cpus[i]->lapic_id);
                printf("    Go To Address: %lX\n", smp_request.response->cpus[i]->goto_address);
                printf("    Extra Argument: %lu\n", smp_request.response->cpus[i]->extra_argument);
            }            
        }
        else if(strcmp(input, "version") == 0)
        {
            printf("Hyperion %s-%s-%s\n", VERSION, BUILD, STATUS);
        }
		else if(strcmp(input, "gui") == 0)
        {
            gui();
        }
        else if(strcmp(input, "pong") == 0)
        {
            pong();
        }
        else if(strcmp(input, "pongcon") == 0)
        {
            PongConsoleTest();
        }
        else if(strcmp(input, "panic") == 0)
        {
            panic("User requested a kernel panic!");
        }
		else if(strcmp(input, "ls") == 0)
        {
			void* ptr = module_request.response->modules[0]->address;
			ustar_header_t * header = (ustar_header_t *)ptr;

			while(memcmp(header->ustar, "ustar", 5) == 0)
			{
				printf("%s %lu\n", header->file_name, ustar_octal_to_int(header->file_size, 11), header);
				ptr += ((((ustar_octal_to_int(header->file_size, 11) + 511) / 512) + 1) * 512);
				header = (ustar_header_t *)ptr;
			}
        }
        else if(strcmp(input, "getsc") == 0){
            while(1){
                printf("%x\n", getscancode());
            }
        }
		else if(strncmp(input, "read ", 5) == 0)
        {
            if(strlen(input) > 5)
			{
				void* ptr = module_request.response->modules[0]->address;
				ustar_header_t * header = (ustar_header_t *)ptr;

				while(memcmp(header->ustar, "ustar", 5) == 0)
				{
					if (memcmp(header->file_name, input + 5, strlen(input + 5) + 1) == 0)
					{
						size_t size = ustar_octal_to_int(header->file_size, 11);
						unsigned char* data = kmalloc(size);
						memcpy(data, (ptr + 512), size);
						data[size] = 0;
						printf("%s\n", data);
					}
					ptr += ((((ustar_octal_to_int(header->file_size, 11) + 511) / 512) + 1) * 512);
					header = (ustar_header_t *)ptr;
				}
			}
			else
			{
				nlog_error("No arguments passed\n");
			}			
        }
        else if(strcmp(input, "lspci") == 0)
        {
            int i;
            for (size_t i = 0; i < pci_devices.length; i++)
            {
                printf("%02x:%02x:%02x %s: %s %s\n", pci_devices.data[i]->bus, pci_devices.data[i]->device, pci_devices.data[i]->function, pci_devices.data[i]->subclass, pci_devices.data[i]->vendor, pci_devices.data[i]->class);
            }
        }
        else if(strcmp(input, "history") == 0)
        {
            int i;
            char* cmd;
            vec_foreach(&v, cmd, i)
            {
                printf("[%d] %s\n", i, cmd);
            }
        }
        else if(strcmp(input, "clear") == 0)
        {
            printf("\x1b[2J\x1b[H");
        }
        else if(strcmp(input, "halt") == 0){
                hlt();
        }
        else if(strcmp(input, "meminfo") == 0){
            pmm_info();
        }
        else
        {
            if(input[0] != '\0')
            {
                nlog_error("Invalid command '%s'\n", input);
            }
        }
        char* hist = kmalloc(strlen(input) + 1);
        if(strlen(input) > 0)
            strcpy(hist, input);
        vec_push(&v, hist);
    }

    serial_printf("Command entered: %s\n", input);
    vec_deinit(&v);
    kfree(input);
}
void putpix(uint64_t x, uint64_t y, uint32_t color, struct limine_framebuffer *frm)
{
    /* Oneliner to plot a pixel on a buffer */
    *(uint32_t*)((uint64_t)(frm->address) + (x * 4) + (y * (frm->pitch / (frm->bpp / 8)) * 4)) = color;
}
void putwindow(uint64_t x1, uint64_t y1, uint64_t width, uint64_t height, uint32_t color, struct limine_framebuffer *frm)
{
    for (size_t x = x1; x < (width + x1); x++)
    {
        for (size_t y = y1; y < (height + y1); y++)
        {
            putpix(x, y, color, frm);
        }    
    }
}
void gui()
{    
    struct limine_framebuffer backbuffer;
	backbuffer = *framebuffer_request.response->framebuffers[0];

	/* Allocate a new location for the backbuffer to reside in, they can't point to the same location or else there would be no point lol */
	backbuffer.address = kmalloc(framebuffer_request.response->framebuffers[0]->height * framebuffer_request.response->framebuffers[0]->pitch);
    uint64_t xs = 25;
    uint64_t ys = 25;
    int x = 346, y = 520, cc = 25;
    /* This for loop just clears the screen with the color white */
    for (size_t x = 0; x < backbuffer.width; x++)
    {
        for (size_t y = 0; y < backbuffer.height; y++)
        {
            putpix(x, y, 0xFFFFFFFF, &backbuffer);
        }
    }

    while(1){    
        /* Make a box */
        /* Remember, I am passing the address of the backbuffer structure */
        putwindow(100, 100, 200, 100, 0x00000000, &backbuffer);

        /* Check if the box is going out of bounds */
        if(x + 21 >= backbuffer.width - 1 || x <= 0){
            xs = -xs;
        }
        if(y + 21 >= backbuffer.height - 1 || y <= 0){
            ys = -ys;
        }

        /* Apply movement to the 2nd box and clear te previous pixels*/
        putwindow(x, y, 21, 21, 0xFFFFFFFF, &backbuffer);
        x += xs;
        y += ys;
        //xs++;
        //ys++;

        /* Make a bouncing box*/
        putwindow(x, y, 21, 21, 0xFFFF0000, &backbuffer);        //(color_r<<16+color_g<<8+color_b) * 65535


        /* This copies the content of the backbuffer, which resides in the address, over to the frontbuffer, so you know, you can actually see it */
		memcpy(framebuffer_request.response->framebuffers[0]->address, backbuffer.address, backbuffer.height * backbuffer.pitch);
    }
}
void pong()
{
    printf("\x1b[2J\x1b[H"); 
    printf("Starting pong...\n");   
    struct limine_framebuffer backbuffer;
    struct limine_framebuffer consolebuf;
	backbuffer = *framebuffer_request.response->framebuffers[0];
    consolebuf = *framebuffer_request.response->framebuffers[0];

	/* Allocate a new location for the backbuffer to reside in, they can't point to the same location or else there would be no point lol */
	backbuffer.address = kmalloc(framebuffer_request.response->framebuffers[0]->height * framebuffer_request.response->framebuffers[0]->pitch);
    consolebuf.address = kmalloc(framebuffer_request.response->framebuffers[0]->height * framebuffer_request.response->framebuffers[0]->pitch);

    memcpy(consolebuf.address, framebuffer_request.response->framebuffers[0]->address, framebuffer_request.response->framebuffers[0]->height * framebuffer_request.response->framebuffers[0]->pitch);
    
    uint64_t xs = 25;
    uint64_t ys = 25;
    uint64_t wx = 25;
    uint64_t wy = 25;
    uint64_t x = backbuffer.width - xs, y = 520, cc = 25;

    /* This for loop just clears the screen with the color white */
    for (size_t x = 0; x < backbuffer.width; x++)
    {
        for (size_t y = 0; y < backbuffer.height; y++)
        {
            putpix(x, y, 0xFFFFFFFF, &backbuffer);
        }
    }

    while(1){    
        if(getscancode() == 0x48){
            putwindow(wx, wy, 10, 100, 0xFFFFFFFF, &backbuffer);
            if(wy >= 1){                
                if((wy - 25) >= 25){
                    wy -= 25; 
                }else{
                    wy = 25;
                }         
            }else{
                wy = 25;
            }
        }

        if(getscancode() == 0x50){
            putwindow(wx, wy, 10, 100, 0xFFFFFFFF, &backbuffer);
            if(wy <= backbuffer.height){
                if((wy + 110) <= backbuffer.height - 1){                    
                    wy += 25;
                }else{
                    wy = backbuffer.height - 110;
                }
            }else{
                wy = backbuffer.height - 110;
            }
        }
        /* Make a box */
        /* Remember, I am passing the address of the backbuffer structure */
        putwindow(wx, wy, 10, 100, 0x00000000, &backbuffer);

        /* Check if the box is going out of bounds or it is bounced off the paddle */
        if(x + 21 >= backbuffer.width - 1 || ((y >= wy && y <= wy + 100) && x <= wx + 30)){
            xs = -xs;
        }
        if(y + 21 >= backbuffer.height - 1 || y <= 0){
            ys = -ys;
        }

        if(x <= 30){
            break;
        }

        /* Apply movement to the 2nd box and clear te previous pixels */
        putwindow(x, y, 21, 21, 0xFFFFFFFF, &backbuffer);
        x += xs;
        y += ys;

        /* Make a bouncing box */
        putwindow(x, y, 21, 21, 0xFFFF0000, &backbuffer);        //(color_r<<16+color_g<<8+color_b) * 65535


        /* This copies the content of the backbuffer, which resides in the address, over to the frontbuffer, so you know, you can actually see it */
		memcpy(framebuffer_request.response->framebuffers[0]->address, backbuffer.address, backbuffer.height * backbuffer.pitch);
        
        /* halt the CPU for one clock tick */
        hlt();
    }

    for (size_t x = 0; x < backbuffer.width; x++)
    {
        for (size_t y = 0; y < backbuffer.height; y++)
        {
            putpix(x, y, 0x00000000, &backbuffer);
        }
    }
    //putwindow(0, 0, backbuffer.width, backbuffer.height, 0x00000000, &backbuffer);

    /* This copies the content of the backbuffer, which resides in the address, over to the frontbuffer, so you know, you can actually see it */
	memcpy(framebuffer_request.response->framebuffers[0]->address, consolebuf.address, framebuffer_request.response->framebuffers[0]->height * framebuffer_request.response->framebuffers[0]->pitch);
        
    printf("Game over!\n");
}

void PongConsoleTest(){
    struct limine_framebuffer backbuffer;
	backbuffer = *framebuffer_request.response->framebuffers[0];

	/* Allocate a new location for the backbuffer to reside in, they can't point to the same location or else there would be no point lol */
	backbuffer.address = kmalloc(framebuffer_request.response->framebuffers[0]->height * framebuffer_request.response->framebuffers[0]->pitch);
    uint64_t xs = 25;
    uint64_t ys = 25;

    uint64_t wx = 25;
    uint64_t wy = 25;
    int x = 346, y = 520, cc = 25;
    /* This for loop just clears the screen with the color white */
    for (size_t x = 0; x < backbuffer.width; x++)
    {
        for (size_t y = 0; y < backbuffer.height; y++)
        {
            //putpix(x, y, 0xFFFFFFFF, &backbuffer);
        }
    }

    while(1){    
        if(getscancode() == 0x48){
            //putwindow(wx, wy, 10, 100, 0xFFFFFFFF, &backbuffer);
            if(wy >= 1){                
                if((wy - 25) >= 25){
                    wy -= 25; 
                }else{
                    wy = 25;
                }         
            }else{
                wy = 25;
            }
        }

        if(getscancode() == 0x50){
            //putwindow(wx, wy, 10, 100, 0xFFFFFFFF, &backbuffer);
            if(wy <= backbuffer.height){
                if((wy + 110) <= backbuffer.height - 1){                    
                    wy += 25;
                }else{
                    wy = backbuffer.height - 110;
                }
            }else{
                wy = backbuffer.height - 110;
            }
        }
        /* Make a box */
        /* Remember, I am passing the address of the backbuffer structure */
        //putwindow(wx, wy, 10, 100, 0x00000000, &backbuffer);

        /* Check if the box is going out of bounds */
        if(x + 21 >= backbuffer.width - 1 || x <= 0){
            xs = -xs;
        }
        if(y + 21 >= backbuffer.height - 1 || y <= 0){
            ys = -ys;
        }

        /* Apply movement to the 2nd box and clear te previous pixels*/
        //putwindow(x, y, 21, 21, 0xFFFFFFFF, &backbuffer);
        x += xs;
        y += ys;
        //xs++;
        //ys++;

        printf("%d\n", wy);

        /* Make a bouncing box*/
        //putwindow(x, y, 21, 21, 0xFFFF0000, &backbuffer);        //(color_r<<16+color_g<<8+color_b) * 65535


        /* This copies the content of the backbuffer, which resides in the address, over to the frontbuffer, so you know, you can actually see it */
		//memcpy(framebuffer_request.response->framebuffers[0]->address, backbuffer.address, backbuffer.height * backbuffer.pitch);
        
        /* halt the os for one clock tick */
        hlt();
    }
}

void test()
{
	syscall_write_test("Task 1\n");
}

void _start(void)
{
    struct limine_rsdp_request limine_rsdp;

    term_init();
    serial_init();
    gdt_init();
    idt_init();
    isr_init();
    irq_init();
    rtc_init();
    pmm_init();
    vmm_init();
    acpi_init();
    //acpi_find_sdt(limine_rsdp.response);
    madt_init();
    pci_init();
    syscall_init();
	//mouse_init();
    sched_init();
    smp_init();
    //apic_init();

    nlog_info("[KERNEL] >> Hyperion Kernel Loaded!\n");
    nlog_info("[KERNEL] >> Launching kernel shell...\n");
    nlog_info("[KERNEL] >> KERNEL MEMORY ADDRESS: 0x%x\n", _start);
    nlog_info("[KERNEL] >> RSDP RESPONSE: 0x%x\n", limine_rsdp.response);
    nlog_info("[KERNEL] >> RSDP ID: 0x%x\n", limine_rsdp.id);

	sti();

    //printf("\x1b[2J\x1b[H");
    printf("\nWelcome to the Hyperion Operating System! (%s-%s-%s)\n", VERSION, BUILD, STATUS);
	kshell();

    for (;;)
    {
        hlt();
    }
}

unsigned short lfsr = 0xACE1u;
unsigned bit;

void reboot()
{
    uint8_t good = 0x02;
    while (good & 0x02)
        good = inb(0x64);
    outb(0x64, 0xFE);
    panic("REBOOT FAILED");
}

void shutdown(struct limine_rsdp_request pwid){
    // BOCHS / QEMU SHUTDOWN (Versions older tha 2.0!)
    nlog_info("Attemting BOCHS / QEMU shutdown...\n");
    outb(0xB004, 0x2000);
    nlog_error("BOCHS / QEMU shutdown failed!\n");

    // QEMU SHUTDOWN (Newer versions of QEMU)
    nlog_info("Attemting QEMU shutdown...\n");
    outb(0x604, 0x2000);
    nlog_error("QEMU shutdown failed!\n");

    // VBOX SHUTDOWN
    nlog_info("Attemting Virtualbox shutdown...\n");
    outb(0x4004, 0x3400);
    nlog_error("Virtualbox shutdown failed!\n");
    
    nlog_info("Attemting ACPI shutdown...\n");
    acpiPowerOff(pwid);
    nlog_error("ACPI shutdown failed!\n");

    panic("SHUTDOWN FAILED");
}

#define SLP_EN  (1 << 13)
void poweroff() // by Napalm and Falkman
{
    unsigned int i, j, len, count, found, *ptr, *rsdp = 0, *rsdt = 0, *facp = 0, *dsdt = 0;
    unsigned char *data, slp_typ[2];
     
    // find acpi RSDP table pointer
    for(ptr = (unsigned int *)0x000E0000; ptr < (unsigned int *)0x000FFFFF; ptr++){
        if(*ptr == ' DSR' && *(ptr + 1) == ' RTP'){ // "RSD PTR "
            if(crc_8((unsigned char *)ptr, 20)) continue;
            rsdp = ptr;
            break;
        }
    }
    if(!rsdp) goto haltonly;
     
    // find RSDT table pointer
    ptr = (unsigned int *)*(ptr + 4);
    if(crc_8((unsigned char *)ptr, *(ptr + 1))){
        printf("Error: RSDT checksum mismatch.\n");
        goto haltonly;
    }
    rsdt  = ptr;
    count = (*(ptr + 1) - 36) / 4;
     
    // find FACP table pointer
    ptr += 9; // skip RSDT entries
    for(i = 0; i < count; i++){
        for(j = 0; j < 24; j++){
            if(*(unsigned int *)*ptr == 'PCAF'){ // "FACP"
                facp = (unsigned int *)*ptr;
                i = count;
                break;
            }
        }
    }
    if(!facp){
        printf("Error: Could not find FACP table.\n");
        goto haltonly;
    }
    if(crc_8((unsigned char *)facp, *(facp + 1))){
        printf("Error: FACP checksum mismatch.\n");
        goto haltonly;
    }
     
    // find DSDT table pointer
    ptr = (unsigned int *)*(facp+10); // DSDT address
    if(*ptr != 'TDSD'){ // "DSDT"
        printf("Error: Could not find DSDT table.\n");
        goto haltonly;
    }
    if(crc_8((unsigned char *)ptr, *(ptr + 1))){
        printf("Error: DSDT checksum mistmatch.\n");
        goto haltonly;
    }
    dsdt = ptr;
     
    // Search DSDT byte-code for ACPI _S5 signature
    found = 0;
    len   = *(dsdt + 1) - 36;
    data  = (unsigned char *)(dsdt + 36);
    while(len--){
        if((*(unsigned int *)data & 0x00FFFFFF) == 0x0035535F){ // "_S5"
            data += 4;
            if(*data == 0x12){ // 0x012 = package opcode
                data += 3; // 0x0A = 8bit integer opcode
                slp_typ[0] = (*data == 0x0A) ? *++data : *data;
                data++;
                slp_typ[1] = (*data == 0x0A) ? *++data : *data;
                found = 1;
            }
            break;
        }
        data++;
    }
    if(!found) goto haltonly;
     
    // execute the actual shutdown and power-off
    outb(*(facp + 16), slp_typ[0] | SLP_EN);     // FACP[64] = PM1a_CNT_BLK
    if(*(facp + 17))
        outb(*(facp + 17), slp_typ[1] | SLP_EN); // FACP[68] = PM1b_CNT_BLK
    printf("Shutting down...\n");
    for(;;){
        hlt(); 
    }
        
     
haltonly:
    printf("It is now safe to turn off your computer.\n");
    for(;;)
        hlt();     
    
    panic("SHUTDOWN FAILED! Please manually shut down your computer.");
}


static uint8_t sht75_crc_table[] = {

	0,   49,  98,  83,  196, 245, 166, 151, 185, 136, 219, 234, 125, 76,  31,  46,
	67,  114, 33,  16,  135, 182, 229, 212, 250, 203, 152, 169, 62,  15,  92,  109,
	134, 183, 228, 213, 66,  115, 32,  17,  63,  14,  93,  108, 251, 202, 153, 168,
	197, 244, 167, 150, 1,   48,  99,  82,  124, 77,  30,  47,  184, 137, 218, 235,
	61,  12,  95,  110, 249, 200, 155, 170, 132, 181, 230, 215, 64,  113, 34,  19,
	126, 79,  28,  45,  186, 139, 216, 233, 199, 246, 165, 148, 3,   50,  97,  80,
	187, 138, 217, 232, 127, 78,  29,  44,  2,   51,  96,  81,  198, 247, 164, 149,
	248, 201, 154, 171, 60,  13,  94,  111, 65,  112, 35,  18,  133, 180, 231, 214,
	122, 75,  24,  41,  190, 143, 220, 237, 195, 242, 161, 144, 7,   54,  101, 84,
	57,  8,   91,  106, 253, 204, 159, 174, 128, 177, 226, 211, 68,  117, 38,  23,
	252, 205, 158, 175, 56,  9,   90,  107, 69,  116, 39,  22,  129, 176, 227, 210,
	191, 142, 221, 236, 123, 74,  25,  40,  6,   55,  100, 85,  194, 243, 160, 145,
	71,  118, 37,  20,  131, 178, 225, 208, 254, 207, 156, 173, 58,  11,  88,  105,
	4,   53,  102, 87,  192, 241, 162, 147, 189, 140, 223, 238, 121, 72,  27,  42,
	193, 240, 163, 146, 5,   52,  103, 86,  120, 73,  26,  43,  188, 141, 222, 239,
	130, 179, 224, 209, 70,  119, 36,  21,  59,  10,  89,  104, 255, 206, 157, 172
};

/*
 * uint8_t crc_8( const unsigned char *input_str, size_t num_bytes );
 *
 * The function crc_8() calculates the 8 bit wide CRC of an input string of a
 * given length.
 */

uint8_t crc_8( const unsigned char *input_str, size_t num_bytes ) {

	size_t a;
	uint8_t crc;
	const unsigned char *ptr;

	crc = 8; CRC_START_8;
	ptr = input_str;

	if ( ptr != NULL ) for (a=0; a<num_bytes; a++) {

		crc = sht75_crc_table[(*ptr++) ^ crc];
	}

	return crc;

}  /* crc_8 */

/*
 * uint8_t update_crc_8( unsigned char crc, unsigned char val );
 *
 * Given a databyte and the previous value of the CRC value, the function
 * update_crc_8() calculates and returns the new actual CRC value of the data
 * comming in.
 */

uint8_t update_crc_8( unsigned char crc, unsigned char val ) {

	return sht75_crc_table[val ^ crc];

}  /* update_crc_8 */