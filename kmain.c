/*
This is a simple kernel in C that allows you to type and see the text you type on the screen.
It uses the BIOS keyboard interrupt to read input from the keyboard.
It is a simple kernel that does not do anything else.

Author: @Usama3627
Date: 2025-05-22
*/

#define VIDEO_MEMORY 0xb8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define WHITE_ON_BLACK 0x07
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



static char* vidptr = (char*)VIDEO_MEMORY;
static unsigned int cursor_pos = 0;
static unsigned char last_scancode = 0;
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
    kprint("Setting color to ");
    kprint(fg);
    kprint(",");
    kprint(bg);
    foreground_color = fg;
    background_color = bg;
}

char kgetc(void) {
    while (1) {
        unsigned char scancode;
        // Read from keyboard port
        asm volatile("inb %1, %0" : "=a"(scancode) : "Nd"(0x60));
        
        // Check for key press
        if (scancode < 0x80 && scancode != last_scancode) {
            last_scancode = scancode;
            
            // Convert scancode to ASCII (US QWERTY layout)
            char ascii = 0;
            switch (scancode) {
                // First row (QWERTY)
                case 0x10: ascii = 'q'; break;
                case 0x11: ascii = 'w'; break;
                case 0x12: ascii = 'e'; break;
                case 0x13: ascii = 'r'; break;
                case 0x14: ascii = 't'; break;
                case 0x15: ascii = 'y'; break;
                case 0x16: ascii = 'u'; break;
                case 0x17: ascii = 'i'; break;
                case 0x18: ascii = 'o'; break;
                case 0x19: ascii = 'p'; break;
                
                // Second row (ASDFG)
                case 0x1E: ascii = 'a'; break;
                case 0x1F: ascii = 's'; break;
                case 0x20: ascii = 'd'; break;
                case 0x21: ascii = 'f'; break;
                case 0x22: ascii = 'g'; break;
                case 0x23: ascii = 'h'; break;
                case 0x24: ascii = 'j'; break;
                case 0x25: ascii = 'k'; break;
                case 0x26: ascii = 'l'; break;
                
                // Third row (ZXCVB)
                case 0x2C: ascii = 'z'; break;
                case 0x2D: ascii = 'x'; break;
                case 0x2E: ascii = 'c'; break;
                case 0x2F: ascii = 'v'; break;
                case 0x30: ascii = 'b'; break;
                case 0x31: ascii = 'n'; break;
                case 0x32: ascii = 'm'; break;
                
                // Numbers
                case 0x02: ascii = '1'; break;
                case 0x03: ascii = '2'; break;
                case 0x04: ascii = '3'; break;
                case 0x05: ascii = '4'; break;
                case 0x06: ascii = '5'; break;
                case 0x07: ascii = '6'; break;
                case 0x08: ascii = '7'; break;
                case 0x09: ascii = '8'; break;
                case 0x0A: ascii = '9'; break;
                case 0x0B: ascii = '0'; break;
                
                // Special characters
                case 0x1C: ascii = '\n'; break;  // Enter
                case 0x39: ascii = ' '; break;   // Space
                case 0x0E: ascii = '\b'; break;  // Backspace
                case 0x33: ascii = ','; break;   // Comma
                case 0x34: ascii = '.'; break;   // Period
                case 0x35: ascii = '/'; break;   // Forward slash
                case 0x0C: ascii = '-'; break;   // Minus
                case 0x0D: ascii = '='; break;   // Equals
                case 0x1A: ascii = '['; break;   // Left bracket
                case 0x1B: ascii = ']'; break;   // Right bracket
                case 0x27: ascii = ';'; break;   // Semicolon
                case 0x28: ascii = '\''; break;  // Single quote
                case 0x29: ascii = '`'; break;   // Backtick
                case 0x2B: ascii = '\\'; break;  // Backslash
            }

            if (ascii != 0) {
                return ascii;
            }
        } else if (scancode >= 0x80) {
            // Key release
            last_scancode = 0;
        }
    }
}

void kgets(char* buffer, unsigned int max_length) {
    unsigned int i = 0;
    while (i < max_length - 1) {
        char c = kgetc();
        if (c != 0) {
            buffer[i++] = c;
            kputc(c);
        }
        if (c == '\n') {
            break;
        }
    }
    buffer[i] = '\0'; 
}

void kmain(void) {
    kclear();
    
    kprint("Hello from C kernel!\n");
    
    char input_buffer[80];
    
    while (1) {
        // Ask for both foreground and background color
        kprint("Enter foreground color (0-15): ");
        kgets(input_buffer, 80);
        int length = 0;
        while (input_buffer[length] != '\0') {
            length++;
        }
        // Convert the input to an integer
        foreground_color = input_buffer[0] - '0';
        kprint("Enter background color (0-15): ");
        // Empty the input buffer
        for (int i = 0; i < 80; i++) {
            input_buffer[i] = '\0';
        }
        kgets(input_buffer, 80);
        length = 0;
        while (input_buffer[length] != '\0') {
            length++;
        }
        // Convert the input to an integer
        background_color = input_buffer[0] - '0';

        
        // Clear the screen
        kclear();

        // Ask to enter a text
        kprint("Enter a text: ");
        // Empty the input buffer
        for (int i = 0; i < 80; i++) {
            input_buffer[i] = '\0';
        }
        kgets(input_buffer, 80);

        kprint("\nYou typed: ");
        kprint(input_buffer);
    }
}
