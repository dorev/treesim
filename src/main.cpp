#include <iostream>

#include "lsystem.h"
#include "kernel.h"

int main()
{
    LSystem lsys;
    Environment env;
    lsys.Init<Kernel>(5.0f);
    lsys.Grow(99, &env);
}