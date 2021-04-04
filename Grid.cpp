#include <Grid.h>



#define IX(i,j) ((i)+(size)*(j)) // macro to access (i,j) position on the grid

Grid::Grid(int size)
{
    this->size = size;
}

void Grid::addDye(Fluid *fluid, int x, int y, float amount)
{
    int index = IX(x,y);
    fluid[IX(x,y)].density += amount;
}

