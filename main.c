#include "failsafe.h"

void dispose(void)
{}

int main(void)
{

    failsafe_throw("Testing throwing", &main, &dispose);
    failsafe_fatal("Testing fatals", &main);
    failsafe_assert(0, "Testing assertions");
    return 0;
}