#ifndef KERNEL_H
#define KERNEL_H

// VGA and screen constants
#define VIDEO_MEMORY 0xb8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define WHITE_ON_BLACK 0x07

// VGA color constants
#define VGA_COLOR_BLACK 0
#define VGA_COLOR_BLUE 1
#define VGA_COLOR_GREEN 2
#define VGA_COLOR_CYAN 3
#define VGA_COLOR_RED 4
#define VGA_COLOR_MAGENTA 5
#define VGA_COLOR_BROWN 6
#define VGA_COLOR_LIGHT_GREY 7
#define VGA_COLOR_DARK_GREY 8
#define VGA_COLOR_LIGHT_BLUE 9
#define VGA_COLOR_LIGHT_GREEN 10
#define VGA_COLOR_LIGHT_CYAN 11
#define VGA_COLOR_LIGHT_RED 12
#define VGA_COLOR_LIGHT_MAGENTA 13
#define VGA_COLOR_LIGHT_BROWN 14
#define VGA_COLOR_WHITE 15

// Screen functions
void kclear(void);
void kputc(char c);
void kprint(const char* str);
void ksetcolor(unsigned char fg, unsigned char bg);

// Color management functions
unsigned int get_foreground_color(void);
unsigned int get_background_color(void);
void set_foreground_color(unsigned int color);
void set_background_color(unsigned int color);

// Input functions
char kgetc(void);
void kgets(char* buffer, unsigned int max_length);

// Utility functions
void empty_buffer(char* buffer, unsigned int max_length);
int get_length_of_string(char* buffer, unsigned int max_length);
int string_to_int(char* str);
void int_to_string(int num, char* str);

// Main kernel function
void kmain(void);

#endif 