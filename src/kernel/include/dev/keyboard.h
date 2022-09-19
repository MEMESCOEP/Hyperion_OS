/**
 * @file keyboard.h
 * @author xyve
 * 
 * Credit to the following project(s):
 *      https://github.com/0Nera/SynapseOS
 * Resources used:
 *      https://wiki.osdev.org/PS/2_Keyboard
 * 
 */
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <cpu/isr/isr.h>
#include <stdint.h>
#include <stdbool.h>
#include <cpu/cpu.h>
#include <libc/stdio.h>
#include <utils/nlog.h>

void keyboard_handler(struct registers * r);
int getch();
int getstr(char * buffer);
int getline(char * buffer);
int getch_nb();
int getscancode();
#endif