/*
 * Main kernel entry point
 * Simple kernel that allows typing and color customization
 * 
 * Author: @Usama3627
 * Date: 2025-05-22
 */

#include "kernel.h"

// External functions from screen.c for color management
extern void set_foreground_color(unsigned int color);
extern void set_background_color(unsigned int color);

void kmain(void) {
    kclear();
    
    kprint("Welcome to MyOS - Simple Kernel v1.0\n");
    kprint("=====================================\n\n");
    
    char input_buffer[80];
    
    while (1) {
        // Ask for foreground color
        kprint("Enter foreground color (0-15): ");
        kgets(input_buffer, 80);
        
        int fg_color = string_to_int(input_buffer);
        if (fg_color >= 0 && fg_color <= 15) {
            set_foreground_color(fg_color);
        } else {
            kprint("Invalid color. Please enter a number between 0 and 15.\n");
            continue;
        }

        // Ask for background color
        kprint("Enter background color (0-15): ");
        empty_buffer(input_buffer, 80);
        kgets(input_buffer, 80);
        
        int bg_color = string_to_int(input_buffer);
        if (bg_color >= 0 && bg_color <= 15) {
            set_background_color(bg_color);
        } else {
            kprint("Invalid color. Please enter a number between 0 and 15.\n");
            continue;
        }

        // Clear the screen with new colors
        kclear();

        // Ask for text input
        kprint("Enter text to display: ");
        empty_buffer(input_buffer, 80);
        kgets(input_buffer, 80);

        kprint("\nYou typed: ");
        kprint(input_buffer);
        kprint("\n\nPress any key to continue...\n");
        
        // Wait for any key press
        kgetc();
    }
} 