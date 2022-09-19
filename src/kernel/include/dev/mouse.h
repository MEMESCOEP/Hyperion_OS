/**
 * @file mouse.h
 * @author xyve
 * 
 * Credit to the following project(s):
 *      
 * Resources used:
 *      https://wiki.osdev.org/Mouse_Input
 * 		https://wiki.osdev.org/PS/2_Mouse
 * 
 */
#ifndef MOUSE_H
#define MOUSE_H

#include <cpu/isr/isr.h>
#include <stdint.h>
#include <stdbool.h>
#include <cpu/cpu.h>
#include <libc/stdio.h>
#include <utils/nlog.h>

void mouse_init();
void mouse_handler(struct registers * r);
int8_t mouse_get_x();
int8_t mouse_get_y();

#endif