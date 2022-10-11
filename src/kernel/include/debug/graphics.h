/**
 * @file graphics.h
 * @author xyve
 * 
 * Neptunium Kernel Graphics Engine
 * 
 */
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <libc/string.h>
#include <libc/stdio.h>
#include <kernel.h>
#include <utils/vec.h>

struct window
{
	uint64_t x;
	uint64_t y;
	uint64_t width;
	uint64_t height;
	uint32_t color;
};

typedef vec_t(struct window *) window_vec_t;

struct canvas
{
	struct limine_framebuffer * backbuffer;
	struct limine_framebuffer * frontbuffer;
	uint64_t framebuffer_size;
	uint32_t color;
	window_vec_t windows;
};

void graphics_paint_window(struct canvas * c, struct window * w);
void graphics_paint_canvas(struct canvas * c);
void graphics_update(struct canvas * c);
void graphics_add_window(struct canvas * c, uint64_t x, uint64_t y, uint64_t width, uint64_t height, uint32_t color);

#endif
