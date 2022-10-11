#include <dev/serial.h>

lock_t serial_lock;

/**
 * Initializes the serial port
 * Copied code from the OSDEV wiki
 */
int32_t serial_init()
{
	nlog_info("[SERIAL] >> Initializing serial...\n");
	spinlock_lock(serial_lock);
	outb(PORT + 1, 0x00);	 // Disable all interrupts
	outb(PORT + 3, 0x80);	 // Enable DLAB (set baud rate divisor)
	outb(PORT + 0, 0x03);	 // Set divisor to 3 (lo byte) 38400 baud
	outb(PORT + 1, 0x00);	 //	(hi byte)
	outb(PORT + 3, 0x03);	 // 8 bits, no parity, one stop bit
	outb(PORT + 2, 0xC7);	 // Enable FIFO, clear them, with 14-byte threshold
	outb(PORT + 4, 0x0B);	 // IRQs enabled, RTS/DSR set
	outb(PORT + 4, 0x1E);	 // Set in loopback mode, test the serial chip
	outb(PORT + 0, 0xAE);	 // Test serial chip (send byte 0xAE and check if serial returns same byte)

	// Check if serial is faulty (i.e: not same byte as sent)
	if(inb(PORT + 0) != 0xAE) {
		return 1;
	}

	// If serial is not faulty set it in normal operation mode
	// (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
	outb(PORT + 4, 0x0F);

	nlog_info("[SERIAL] >> Serial Initialized\n");
	spinlock_unlock(serial_lock);
	return 0;
}

/**
 * Checks if data has been received from the serial port
 */
int32_t serial_received() {
	return inb(PORT + 5) & 1;
}
 /**
 * Reads a character from the serial port
 */
char serial_read() {
	while (serial_received() == 0);
 
	return inb(PORT);
}
/**
 * No clue what this does
 */
int32_t is_transmit_empty() {
	return inb(PORT + 5) & 0x20;
}
/**
 * Prints character to serial
 *
 * @param ch Character to print
 */
int serial_putchar(const char ch)
{
	spinlock_lock(serial_lock);
    while (is_transmit_empty() == 0);
	outb(PORT,ch);
	spinlock_unlock(serial_lock);
}
/**
 * Prints string to serial port
 *
 * @param str String to print
 */
int serial_puts(const char * str)
{
    while (*str != '\0')
		serial_putchar(*str++);
}
/**
 * Used by the serial_printf implementation
 * 
 * @param ch Character to print
 */
void serial_putchar_(const char ch, void * extra)
{
	(void) extra;
    serial_putchar(ch);
}

/**
 * Prints formatted string to serial
 *
 * @param format Format
 * @param ...    Variables
 */
int serial_printf(const char* format, ...)
{
    va_list list;
	va_start(list, format);
	vfctprintf(&serial_putchar_, NULL, format, list);
	va_end(list);
    return 0;
}