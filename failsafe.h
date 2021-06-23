#ifndef LIB_FAILSAFE_H
#define LIB_FAILSAFE_H

/*
    The Failsafe exception library for C.
    Written in ANSI C.
    
    On Windows, Failsafe generates fancy message boxes.
    Author: EscapeCharacter
*/

/* Checks if boolean is true. If it isn't, generates a fatal error. */
void failsafe_assert(int boolean, const char *message);

/*
    Used to indicate a fatal error. callee is the address of the function
    calling failsafe_fatal().
*/
void failsafe_fatal(const char *message, void *callee);

/*
    Used to indicate a non-fatal error. calle is the address of the function
    calling failsafe_throw(). The user can choose to end the program.
    dispose() is called if the user wants to close the program.
*/
void failsafe_throw(const char *message, void *callee, void (*dispose)());

#endif 