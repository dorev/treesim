#include "organismgraph.h"
#include "plantanatomy.h"

int main()
{
    OrganismGraph lsys;
    Environment env;
    lsys.Init<Kernel>(5.0f);
    lsys.Grow(env, 99);
}