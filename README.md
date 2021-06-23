# Failsafe
A public domain minimalistic C error handling "file" (header and source).
## How to use
Copy the two files `failsafe.c` and `failsafe.h`. On Windows, you will have
to link `user32.lib`.
## Functions
```c
/* Assertions */
void failsafe_assert(int boolean, const char *message);

/* Fatal */
void failsafe_fatal(const char *message, void *callee);

/* Exception (non-catchable) */
void failsafe_throw(const char *message, void *callee, void (8dispose)());
```