from Fluid import Fluid
import numpy as np


class Field():
    def __init__(self, size, fluid):

        self.size = size
        self.fluid = fluid
        self.iter = 5

        self.s = np.full(self.size * self.size, 0)
        self.density = np.full(self.size * self.size, 0)

        self.Vx = np.full(self.size * self.size, 0)
        self.Vy = np.full(self.size * self.size, 0)

        self.Vx0 = np.full(self.size * self.size, 0)
        self.Vy0 = np.full(self.size * self.size, 0)


    def IX(self,x,y):
        """returns a (x,y) grid position in a single value"""
        return int(x+(self.size)*y)


    def add_density(self, x, y, amount):
        """adds the dye inside the fluid particles"""
        self.density[self.IX(x,y)] = amount


    def add_velocity(self, x, y, amountX, amountY):
        """adds velocity to the fluid particles"""
        self.Vx[self.IX(x,y)] += amountX
        self.Vy[self.IX(x,y)] += amountY


    def diffuse(self, b, x, x0, diff, dt, iter, N):
        """
        the dye (density) is spreading out in the fluid.
        Each cell diffuses in the 4 nearest cells.
        Is also affects the velocity.
        Diffusion of the density consists in solving a 
        linear equations system using Gauss-Seidel algo.
        """
        a = dt * diff * (N-2) * (N-2) 
        for k in range(iter):
            for i in range(1,N-1):
                for j in range(1,N-1):
                    x[self.IX(i,j)] = (
                        x0[self.IX(i,j)] + a*(
                            x[self.IX(i-1,j)] +
                            x[self.IX(i+1,j)] +
                            x[self.IX(i,j-1)] +
                            x[self.IX(i,j+1)]))/(1+6*a)
            self.set_boundaries(N, b, x)
    

    def project(self, Vx, Vy, p, div, iter, N):
        """
        ensures mass conservation inside the fluid.
        The amount of fluid in each box is constant,
        so outflow = inflow.
        """
        h = 1.0/N
        for i in range(1,N-1):
            for j in range(1,N-1):
                div[self.IX(i,j)] = -0.5 * h * (
                    Vx[self.IX(i+1,j)] - Vx[self.IX(i-1,j)] +
                    Vy[self.IX(i,j+1)] - Vy[self.IX(i,j-1)])                
                p[self.IX(i,j)] = 0

        self.set_boundaries(N, 0, div)

        for k in range(iter):
            for i in range(1,N-1):
                for j in range(1,N-1):
                    p[self.IX(i,j)] = (
                        div[self.IX(i,j)] +
                        p[self.IX(i-1,j)] +
                        p[self.IX(i+1,j)] +
                        p[self.IX(i,j-1)] +
                        p[self.IX(i,j+1)])/4

        self.set_boundaries(N, 0, p)

        for i in range(1,N-1):
            for j in range(1,N-1):
                Vx[self.IX(i,j)] -= 0.5 * (p[self.IX(i+1,j)] - p[self.IX(i-1,j)])/h
                Vy[self.IX(i,j)] -= 0.5 * (p[self.IX(i,j+1)] - p[self.IX(i,j-1)])/h
        self.set_boundaries(N, 1, Vx)
        self.set_boundaries(N, 2, Vy)


    def advect(self, b, d, d0, Vx, Vy, dt, N):
        """
        advection comes from the velocity field.
        It affects both the velocity of each cell
        and its density.
        """
        dt0 = dt * N
        for i in range(1,N-1):
            for j in range (1,N-1):
                x = i - dt0 * Vx[self.IX(i,j)]
                y = j - dt0 * Vy[self.IX(i,j)]

                if x < 0.5:
                    x = 0.5
                elif x > N + 0.5:
                    x = N + 0.5
                i0 = np.floor(x)
                i1 = i0 + 1

                if y < 0.5:
                    y = 0.5
                elif y > N + 0.5:
                    y = N + 0.5
                j0 = np.floor(y)
                j1 = j0 + 1

                s1 = x - i0
                s0 = 1 - s1
                t1 = y - j0
                t0 = 1 - t1

                _i0, _i1, _j0, _j1 = int(i0), int(i1), int(j0), int(j1)

                d[self.IX(i,j)] = (
                    s0*(
                        t0*d0[self.IX(_i0,_j0)] + 
                        t1*d0[self.IX(_i0,_j1)])+ 
                    s1*(
                        t0*d0[self.IX(_i1,_j0)] +
                        t1*d0[self.IX(_i1,_j1)]))
        self.set_boundaries(N, b, d)


    def set_boundaries(self, N, b, x):
        """defines the boundaries of the fluid"""
        for i in range(1,N-1):
            if b == 1:
                x[self.IX(0,i)]     = -x[self.IX(1,i)]      # left
                x[self.IX(N-1,i)]   = -x[self.IX(N-2,i)]    # right
            elif b == 2:
                x[self.IX(i,0)]     = -x[self.IX(i,1)]      # top
                x[self.IX(i,N-1)]   = -x[self.IX(i,N-2)]    # bottom
            else:
                x[self.IX(0,i)]     = x[self.IX(1,i)]       # left
                x[self.IX(N-1,i)]   = x[self.IX(N-2,i)]     # right
                x[self.IX(i,0)]     = x[self.IX(i,1)]       # top
                x[self.IX(i,N-1)]   = x[self.IX(i,N-2)]     # bottom

        x[self.IX(0,0)]     = 0.5 * (x[self.IX(1,0)]    + x[self.IX(0,1)])         # upper-left
        x[self.IX(N-1,0)]   = 0.5 * (x[self.IX(N-2,0)]  + x[self.IX(N-1,1)])       # lower-left
        x[self.IX(0,N-1)]   = 0.5 * (x[self.IX(0,N-2)]  + x[self.IX(1,N-1)])       # upper-right
        x[self.IX(N-1,N-1)] = 0.5 * (x[self.IX(N-2,N-1)]+ x[self.IX(N-1,N-2)])     # lower-right

    
    def fluidstep(self):
        self.diffuse(1, self.Vx0, self.Vx, self.fluid.viscosity, self.fluid.dt, self.iter, self.size)
        self.diffuse(2, self.Vy0, self.Vy, self.fluid.viscosity, self.fluid.dt, self.iter, self.size)

        self.project(self.Vx0, self.Vy0, self.Vx, self.Vy, self.iter, self.size)

        self.advect(1, self.Vx, self.Vx0, self.Vx0, self.Vy0, self.fluid.dt, self.size)
        self.advect(2, self.Vy, self.Vy0, self.Vx0, self.Vy0, self.fluid.dt, self.size)

        self.project(self.Vx, self.Vy, self.Vx0, self.Vy0, self.iter, self.size)

        self.diffuse(0, self.s, self.density, self.fluid.diffusion, self.fluid.dt, self.iter, self.size)
        self.advect(0, self.density, self.s, self.Vx, self.Vy, self.fluid.dt, self.size)

