/*
 * Utility functions for the kernel
 * String manipulation, conversion functions, etc.
 */

#include "kernel.h"

void empty_buffer(char* buffer, unsigned int max_length) {
    for (int i = 0; i < max_length; i++) {
        buffer[i] = '\0';
    }
}

int get_length_of_string(char* buffer, unsigned int max_length) {
    int length = 0;
    while (buffer[length] != '\0' && length < max_length) {
        length++;
    }
    return length;
}

int string_to_int(char* str) {
    int result = 0;
    int valid_input = 1;
    
    // Process each character in the string
    for (int i = 0; str[i] != '\0' && i < 3; i++) { // Limit to 3 digits for safety
        // Stop at newline
        if (str[i] == '\n') {
            break;
        }
        
        // Check if character is a digit
        if (str[i] < '0' || str[i] > '9') {
            valid_input = 0;
            break;
        }
        
        // Convert character to digit and add to result
        result = result * 10 + (str[i] - '0');
    }
    
    // Return -1 if invalid input, otherwise return the converted number
    return valid_input ? result : -1;
}

// Helper function to convert integer to string (for debugging)
void int_to_string(int num, char* str) {
    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    
    int i = 0;
    int is_negative = 0;
    
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    
    // Convert digits in reverse order
    while (num > 0) {
        str[i++] = (num % 10) + '0';
        num /= 10;
    }
    
    if (is_negative) {
        str[i++] = '-';
    }
    
    str[i] = '\0';
    
    // Reverse the string
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
} 