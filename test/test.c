#include "external/greatest.h"

extern SUITE(octaspire_easing_suite);

GREATEST_MAIN_DEFS();

int main(int argc, char **argv)
{
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(octaspire_easing_suite);
    GREATEST_MAIN_END();
}

