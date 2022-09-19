#include <dev/keyboard.h>

/* Keyboard buffer where all the keys are stored */
volatile uint8_t keyboard_buffer[256];
volatile uint16_t keyboard_buffer_counter = 0;

unsigned char kbdus[128] =
{
	0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
	'\t', /* Tab */
	'q', 'w', 'e', 'r',	't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
	'*',
	0,	/* Alt */
	' ',	/* Space bar */
	0,	/* Caps lock */
	0,	/* 59 - F1 key ... > */
	0,   0,   0,   0,   0,   0,   0,   0,
	0,	/* < ... F10 */
	0,	/* 69 - Num lock*/
	0,	/* Scroll Lock */
	0,	/* Home key */
	0,	/* Up Arrow */
	0,	/* Page Up */
	'-',
	0,	/* Left Arrow */
	0,
	0,	/* Right Arrow */
	'+',
	0,	/* 79 - End key*/
	0,	/* Down Arrow */
	0,	/* Page Down */
	0,	/* Insert Key */
	0,	/* Delete Key */
	0,   0,   0,
	0,	/* F11 Key */
	0,	/* F12 Key */
	0,	/* All other keys are undefined */
};

unsigned char kbdus_s[128] =
{
	0,  27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
	'\t', /* Tab */
	'Q', 'W', 'E', 'R',	'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', 0,
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
	'*',
	0,	/* Alt */
	' ',	/* Space bar */
	0,	/* Caps lock */
	0,	/* 59 - F1 key ... > */
	0,   0,   0,   0,   0,   0,   0,   0,
	0,	/* < ... F10 */
	0,	/* 69 - Num lock*/
	0,	/* Scroll Lock */
	0,	/* Home key */
	0,	/* Up Arrow */
	0,	/* Page Up */
	'-',
	0,	/* Left Arrow */
	0,
	0,	/* Right Arrow */
	'+',
	0,	/* 79 - End key*/
	0,	/* Down Arrow */
	0,	/* Page Down */
	0,	/* Insert Key */
	0,	/* Delete Key */
	0,   0,   0,
	0,	/* F11 Key */
	0,	/* F12 Key */
	0,	/* All other keys are undefined */
};

uint8_t shift = 0;

int getscancode(){
	uint8_t status = inb(0x64);
	uint8_t scancode = inb(0x60);
	return scancode;

	if (status & 0x01)
	{
		uint8_t scancode = inb(0x60);
		return scancode;

		if (scancode & 0x80)
		{
			return scancode;
		}
	}
	return 0;
}

/**
 * Keyboard handler, shouldn't be called on its own, only by the interrupt handler
 *
 * @param r The registers pushed by the interrupt
 */
void keyboard_handler(struct registers * r)
{
	uint8_t status = inb(0x64);

	if (status & 0x01)
	{
		uint8_t scancode = inb(0x60);

		if (scancode & 0x80)
		{
			switch (scancode)
			{
			case 0xAA:
			case 0xB6:
				shift = 1 - shift;
				return;
			}
		}
		else 
		{
			switch (scancode)
			{
			case 0x2A:
			case 0x36:
				shift = 1 - shift;
				return;

			}
			if (shift)
			{
				if (keyboard_buffer_counter == 256)
				{
					memcpy(keyboard_buffer, keyboard_buffer + 1, 255);
				}
				keyboard_buffer[keyboard_buffer_counter] = kbdus_s[scancode];
				keyboard_buffer_counter++;
				return;
			}
			else 
			{
				if (keyboard_buffer_counter == 256)
				{
					memcpy(keyboard_buffer, keyboard_buffer + 1, 255);
				}
				keyboard_buffer[keyboard_buffer_counter] = kbdus[scancode];
				keyboard_buffer_counter++;
				return;
			}
		}
	}
}
/**
 * Gets a character from the keyboard buffer
 */
int getch()
{
	uint16_t count = keyboard_buffer_counter;
	while(count == keyboard_buffer_counter)
	{
		
	}
	return keyboard_buffer[keyboard_buffer_counter - 1];
}

int getch_nb()
{
	return keyboard_buffer[keyboard_buffer_counter - 1];
}