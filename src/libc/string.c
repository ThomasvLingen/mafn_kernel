//
// Created by mafn on 2/4/17.
//

#include <string.h>

size_t strlen(const char* str)
{
    size_t length = 0;

    while (str[length] != 0) {
        length++;
    }

    return length;
}

void* memset(void* ptr, int ch, size_t n)
{
    char to_set = (char)ch;
    char* c_ptr = ptr;

    for (size_t i = 0; i < n; i++) {
        *c_ptr = to_set;
        c_ptr++;
    }

    return ptr;
}
