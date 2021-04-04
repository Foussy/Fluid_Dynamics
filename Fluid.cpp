#include <Fluid.h>

#define IX(i,j) ((i)+(N)*(j))                   // macro to access (i,j) position on the grid
#define SWAP(x0,x) {float* tmp=x0;x0=x;x=tmp;}  // macro thats swaps the two array pointers

Fluid::Fluid(float dt, float diff, float visc) 
{   
    this->dt = dt;
    this->diff = diff;
    this->visc = visc;
};

void Fluid::add_source(int N, float *x, float *s, float dt)
// this routine adds the source s[] to the density. 
// The source corresponds to the "inlet" of our fluid flow. 
// We will give s[] a certain value depending on our initial state.
{
    // x and s array must have pointers
    for (int i = 0; i < N * N; i++)
        x[i] += dt * s[i] ;  
}

void Fluid::set_bound(int N, int b, float *x)
{
    for (int i = 1; i < N; i++)
    {
        x[IX(0,i)] = b==1 ? -x[IX(1,i)] : x[IX(1,i)];       // left border
        x[IX(N,i)] = b==1 ? -x[IX(N-1,i)] : x[IX(N-1,i)];   // right border
        x[IX(i,0)] = b==2 ? -x[IX(i,1)] : x[IX(i,1)];       // top border
        x[IX(i,N)] = b==2 ? -x[IX(i,N-1)] : x[IX(i,N-1)];   // bottom border
    }
    x[IX(0,0)] = 0.5 * (x[IX(1,0)] + x[IX(0,1)]);           // upper-left corner
    x[IX(0,N)] = 0.5 * (x[IX(1,N)] + x[IX(0,N-1)]);         // lower-left corner
    x[IX(N,0)] = 0.5 * (x[IX(N-1,0)] + x[IX(N,1)]);         // upper-right corner
    x[IX(N,N)] = 0.5 * (x[IX(N-1,N)] + x[IX(N,N-1)]);       // lower-right corner
}

void Fluid::diffuse(int N, int b, float *x, float *x0, float diff, float dt)
{
    float a = dt * diff * N * N;
    for (int k = 0; k < 20; k++)
    {
        for (int i = 1; i < N; i++)
        {
            for (int j = 1; j < N; j++)
            {
                x[IX(i,j)] = (x0[IX(i,j)] + a *(x[IX(i-1,j)] + 
                                                x[IX(i+1,j)] +
                                                x[IX(i,j-1)] + 
                                                x[IX(i,j+1)]
                                                )
                                ) / (1 + 4 * a);
            }
        }
        set_bound(N, b, x);
    }
}

void Fluid::advect(int N, int b, float *d, float *d0, float *u, float *v, float dt)
{
    int i0, j0, i1, j1;
    float x, y, s0, t0, s1, t1, dt0;
    dt0 = dt * N;

    for (int i = 1; i < N; i++)
    {
        for (int j = 1; j < N; j++)
        {
            x = i - dt0 * u[IX(i,j)]; 
            y = j - dt0 * v[IX(i,j)];
            if (x < 0.5) x = 0.5; if (x > N + 0.5) x = N + 0.5; i0 = (int)x; i1 = i0 + 1;
            if (y < 0.5) y = 0.5; if (y > N + 0.5) y = N + 0.5; j0 = (int)y; j1 = j0 + 1;
            s1 = x - i0; 
            s0 = 1 - s1;
            t1 = y - j0;
            t0 = 1 - t1;
            d[IX(i,j)] =    s0 * (t0 * d0[IX(i0,j0)] + t1 *  d0[IX(i0,j1)]) +
                            s1 * (t0 * d0[IX(i1,j0)] + t1 *  d0[IX(i1,j1)]);
        }
    }
    set_bound(N, b, d);
}

void Fluid::dens_step(int N, float *x, float *x0, float *u, float *v, float diff, float dt)
{
    add_source(N, x, x0, dt);
    SWAP(x0, x); diffuse(N, 0, x, x0, diff, dt);
    SWAP(x0, x); advect(N, 0, x, x0, u, v, dt);
}

void Fluid::project(int N, float *u, float *v, float *p, float *div)
{
    float h;

    h = 1.0/N;
    for (int i = 1; i < N; i++)
    {
        for (int j = 1; j < N; j++)
        {
            div[IX(i,j)] = -0.5 * h * ( u[IX(i+1, j)] - u[IX(i-1,j)] + 
                                        v[IX(i, j+1)] - v[IX(i, j-1)]);
            p[IX(i,j)] = 0;
        }
    }
    set_bound(N, 0, p);

    for (int k = 0; k < 20; k++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                p [IX(i,j)] = (div[IX(i,j)] + p[IX(i-1,j)] + p[IX(i+1,j)]
                                            + p[IX(i,j-1)] + p[IX(i,j+1)])/4;
            }
        }
        set_bound(N, 0, p);
    }

    for (int i = 1; i < N; i++)
    {
        for (int j = 1; j < N; j++)
        {
            u[IX(i,j)] -= 0.5 * (p[IX(i+1,j)] - p[IX(i-1,j)])/h;
            v[IX(i,j)] -= 0.5 * (p[IX(i,j+1)] - p[IX(i,j-1)])/h;
        }
    }
    set_bound(N, 1 , u); set_bound(N, 2, v);
}

void Fluid::vel_step(int N, float *u, float *v, float *u0, float *v0, float visc, float dt)
{
    add_source (N, u, u0, dt); add_source (N, v, v0, dt);
    SWAP (u0, u); diffuse (N, 1, u, u0, visc, dt);
    SWAP (v0, v); diffuse (N, 2, v, v0, visc, dt);
    project (N, u, v, u0, v0);
    SWAP (u0, u); SWAP (v0 ,v);
    advect (N, 1, u, u0, u0, v0, dt); advect (N, 2, v, v0, u0, v0, dt);
    project (N, u, v, u0, v0);
}