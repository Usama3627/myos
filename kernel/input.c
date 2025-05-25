/*
 * Keyboard input functions for the kernel
 * Handles keyboard scancode reading and conversion to ASCII
 */

#include "kernel.h"

static unsigned char last_scancode = 0;

char kgetc(void) {
    while (1) {
        unsigned char scancode;
        // Read from keyboard port
        asm volatile("inb %1, %0" : "=a"(scancode) : "Nd"(0x60));
        
        if (scancode < 0x80 && scancode != last_scancode) {
            last_scancode = scancode;
            
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