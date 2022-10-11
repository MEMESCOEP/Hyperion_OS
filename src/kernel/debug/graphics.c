#include <debug/graphics.h>

static inline void put_pixel(uint64_t x, uint64_t y, uint32_t color, struct limine_framebuffer *frm)
{
	/* Oneliner to plot a pixel on a buffer */
    *(uint32_t*)((uint64_t)(frm->address) + (x * 4) + (y * (frm->pitch / (frm->bpp / 8)) * 4)) = color;
}
static inline void put_window(uint64_t x1, uint64_t y1, uint64_t width, uint64_t height, uint32_t color, struct limine_framebuffer *frm)
{
    for (size_t x = x1; x < (width + x1); x++)
		for (size_t y = y1; y < (height + y1); y++)
			put_pixel(x, y, color, frm);
}
void graphics_add_window(struct canvas * c, uint64_t x, uint64_t y, uint64_t width, uint64_t height, uint32_t color)
{
	struct window * win = kmalloc(sizeof(struct window));
	win->x = x;
	win->y = y;
	win->width = width;
	win->height = height;
	win->color = color;

	vec_push(&c->windows, win);
}
void graphics_paint_window(struct canvas * c, struct window * w)
{
	put_window
	(
		w->x,
		w->y,
		w->width,
		w->height,
		w->color,
		c->backbuffer
	);
}
void graphics_paint_canvas(struct canvas * c)
{
	/* This for loop just clears the screen with the color white */
	for (size_t x = 0; x < c->backbuffer->width; x++)
		for (size_t y = 0; y < c->backbuffer->height; y++)
			put_pixel(x, y, c->color, c->backbuffer);

	for (size_t i = 0; i < c->windows.length; i++)
	{
		graphics_paint_window(c, c->windows.data[i]);
	}
	
}
void graphics_update(struct canvas * c)
{
	memcpy(c->frontbuffer->address, c->backbuffer->address, c->framebuffer_size);
}