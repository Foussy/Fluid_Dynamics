#ifndef GRID_H
#define GRID_H

#include <Fluid.h>



class Grid
{
    private:
        int size;
    public:
        Grid(int size){};
        void addDye(Fluid *fluid, int x, int y, float amount);
        void addVel(Fluid *fluid, int x, int y, float amountX, float amountY);


};

#endif