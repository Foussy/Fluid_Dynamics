#include <Fluid.h>

#define IX(i,j) ((i)+(N+2)*(j))                  // macro to access (i,j) position on the grid
#define SWAP(x0,x) {float* tmp=x0;x0=x;x=tmp;}   // macro thats swaps the two array pointers

Fluid::Fluid(){}

Fluid::dens_step(int N, float* x, float* x0, float* u, float* v, float diff, float dt)
{
    add_source(N, x, x0, dt);
    SWAP(x0, x); diffuse(N, 0, x, x0, diff, dt);
    SWAP(x0, x); advect(N, 0, x, x0, u, v, dt);
}