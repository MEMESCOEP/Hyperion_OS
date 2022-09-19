#include <dev/mouse.h>

uint8_t mouse_cycle=0;
int8_t mouse_byte[3];
int8_t mouse_x=0;
int8_t mouse_y=0;

//Mouse functions
void mouse_handler(struct registers *r)
{
	switch(mouse_cycle)
	{
	case 0:
		mouse_byte[0] = inb(0x60);
		mouse_cycle++;
		break;
	case 1:
		mouse_byte[1] = inb(0x60);
		mouse_cycle++;
		break;
	case 2:
		mouse_byte[2] = inb(0x60);
		mouse_x = mouse_byte[1];
		mouse_y = mouse_byte[2];
		mouse_cycle = 0;
		break;
	}
	serial_printf("x = %d | y = %d\n", mouse_x, mouse_y);
	//printf("x = %d | y = %d\n", mouse_x, mouse_y);
}

inline void mouse_wait(uint8_t a_type) //unsigned char
{
	uint32_t _time_out=100000; //unsigned int
	if(a_type==0)
	{
		while(_time_out--) //Data
		{
			if((inb(0x64) & 1)==1)
			{
				return;
			}
		}
		return;
	}
	else
	{
		while(_time_out--) //Signal
		{
			if((inb(0x64) & 2)==0)
			{
				return;
			}
		}
		return;
	}
}

inline void mouse_write(uint8_t a_write) //unsigned char
{
	//Wait to be able to send a command
	mouse_wait(1);
	//Tell the mouse we are sending a command
	outb(0x64, 0xD4);
	//Wait for the final part
	mouse_wait(1);
	//Finally write
	outb(0x60, a_write);
}

uint8_t mouse_read()
{
	//Get's response from mouse
	mouse_wait(0);
	return inb(0x60);
}

void mouse_init()
{
	uint8_t _status;  //unsigned char

	//Enable the auxiliary mouse device
	mouse_wait(1);
	outb(0x64, 0xA8);

	//Enable the interrupts
	mouse_wait(1);
	outb(0x64, 0x20);
	mouse_wait(0);
	_status=(inb(0x60) | 2);
	mouse_wait(1);
	outb(0x64, 0x60);
	mouse_wait(1);
	outb(0x60, _status);

	//Tell the mouse to use default settings
	mouse_write(0xF6);
	mouse_read();  //Acknowledge

	//Enable the mouse
	mouse_write(0xF4);
	mouse_read();  //Acknowledge
}

int8_t mouse_get_x()
{
	return mouse_x;
}
int8_t mouse_get_y()
{
	return mouse_y;
}