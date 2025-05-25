/*
 * Screen management functions for the kernel
 * Handles VGA text mode output, colors, and screen clearing
 */

#include "kernel.h"

static char* vidptr = (char*)VIDEO_MEMORY;
static unsigned int cursor_pos = 0;
static unsigned int foreground_color = VGA_COLOR_WHITE;
static unsigned int background_color = VGA_COLOR_BLACK;

void kclear(void) {
    unsigned int i = 0;
    unsigned char attribute = (background_color << 4) | foreground_color;
    
    while (i < SCREEN_WIDTH * SCREEN_HEIGHT * 2) {
        vidptr[i] = ' ';
        vidptr[i + 1] = attribute;
        i += 2;
    }
    cursor_pos = 0;
}

void kputc(char c) {
    vidptr[cursor_pos] = c;
    vidptr[cursor_pos + 1] = (background_color << 4) | foreground_color;
    cursor_pos += 2;
    
    if (c == '\n') {
        cursor_pos = (cursor_pos / (SCREEN_WIDTH * 2)) * (SCREEN_WIDTH * 2) + SCREEN_WIDTH * 2;
    }

    if (cursor_pos >= SCREEN_WIDTH * SCREEN_HEIGHT * 2) {
        cursor_pos = 0;
    }
}

void kprint(const char* str) {
    while (*str != '\0') {
        kputc(*str++);
    }
}

void ksetcolor(unsigned char fg, unsigned char bg) {
    if (fg > 15 || bg > 15) {
        return;
    }
    foreground_color = fg;
    background_color = bg;
}

// Getter functions for color values (used by main kernel)
unsigned int get_foreground_color(void) {
    return foreground_color;
}

unsigned int get_background_color(void) {
    return background_color;
}

void set_foreground_color(unsigned int color) {
    if (color <= 15) {
        foreground_color = color;
    }
}

void set_background_color(unsigned int color) {
    if (color <= 15) {
        background_color = color;
    }
} 