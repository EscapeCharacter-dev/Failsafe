#ifdef _WIN32
#include <Windows.h>
#else
#include <stdio.h>
#endif

#include "failsafe.h"
#include <stdlib.h>
#include <string.h>

void failsafe_assert(int boolean, const char *message) {
    if (!boolean) {
        char *first, *newbuf;
        first = "Assertion failed - Failsafe\n";
        newbuf = calloc(strlen(first) + strlen(message), 1);
        
        strcpy(newbuf, first);
        strcat(newbuf, message);
#ifdef _WIN32
        MessageBoxA(0, newbuf, "Assertion - Failsafe", MB_OK | MB_ICONERROR);
#else
        fprintf(stderr, "%s\n", newbuf);
#endif
        free(newbuf);
        exit(0);
        return;
    }
    return;
}

/*
    by "Charlie Burns", on stack overflow
    edits to be C89 compliant
*/
static char* _lltoa(long long val, int base){

    static char buf[64];
    memset(&buf, 0, 64);

    int i;
    int sign;
    
    i = 64;
    sign = val < 0;
    if (sign) val = -val;

    if(val == 0) return "0";

    for(; val && i ; --i, val /= base) {
        buf[i] = "0123456789ABCDEF"[val % base];
    }

    if(sign) {
        buf[i--] = '-';
    }
    return &buf[i+1];

}

void failsafe_fatal(const char *message, void *callee) {
    char *first, *newbuf, *numbuf;
    first = "Fatal error from 0x";
    newbuf = calloc(strlen(first) + strlen(message) + 20, 1);

#ifdef __x86_64__
    numbuf = _lltoa((unsigned long long)callee, 16);
#else
    numbuf = _lltoa((unsigned long)callee, 16);
#endif
    strcpy(newbuf, first);
    strcat(newbuf, numbuf);
    strcat(newbuf, "\n");
    strcat(newbuf, message);
#ifdef _WIN32
    MessageBoxA(0, newbuf, "Fatal Error - Failsafe", MB_OK | MB_ICONERROR);
#else
    fprintf(stderr, "%s\n", newbuf);
#endif
    
    free(newbuf);
    exit(0);
    return;
}

void failsafe_throw(const char *message, void *callee, void (*dispose)()) {
    char *first, *newbuf, *numbuf;
    first = "Exception from 0x";
    newbuf = calloc(strlen(first) + strlen(message) + 20, 1);

#ifdef __x86_64__
    numbuf = _lltoa((unsigned long long)callee, 16);
#else
    numbuf = _lltoa((unsigned long)callee, 16);
#endif
    strcpy(newbuf, first);
    strcat(newbuf, numbuf);
    strcat(newbuf, "\n");
    strcat(newbuf, message);
    
    int result = 0;
#ifdef _WIN32
    if (MessageBoxA(0, newbuf, "Exception - Failsafe", MB_OKCANCEL
    | MB_ICONERROR) == IDCANCEL)
        result = 1;
#else
    fprintf(stderr, "%s\n", newbuf);
    fprintf(stderr, "Type in 'quit' or 'q' to end process.\n");
    static char arr[5];
    fgets(arr, 5, stdin);
    if (!strcmp(arr, "quit") || !strcmp(arr, "q"))
        result = 1;
#endif

    if (result) {
        free(newbuf);
        dispose();
        exit(0);
    }
    
    free(newbuf);
    return;
}