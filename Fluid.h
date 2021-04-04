#ifndef FLUID_H
#define FLUID_H

class Fluid
{
    public:
        float dt;
        float diff;
        float visc;
        
        float density;

        float Vx;
        float Vy;
        float Vx0;
        float Vy0;  

        Fluid(float dt, float diff, float visc) {} // constructor
        void add_source(int N, float *x, float *s, float dt);
        void set_bound(int N, int b, float *x);
        void diffuse(int N, int b, float *x, float *x0, float diff, float dt);
        void advect(int N, int b, float *d, float *d0, float *u, float *v, float dt);
        void dens_step(int N, float *x, float *x0, float *u, float *v, float diff, float dt);
        void project(int N, float *u, float *v, float *p, float *div);
        void vel_step(int N, float *u, float *v, float *u0, float *v0, float visc, float dt);
};

#endif