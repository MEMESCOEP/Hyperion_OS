/**
 * @file terminal.h
 * @author xyve
 * 
 * Didn't use anything surprisingly
 * 
 */
#ifndef TERM_H
#define TERM_H

#include <libc/string.h>
#include <utils/nlog.h>
#include <kernel.h>
#include <cpu/spinlock/spinlock.h>

void term_write_char(const char ch);
void term_write_str(const char* str, size_t len);
void term_init();

#endif