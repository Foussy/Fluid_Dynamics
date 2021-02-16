#include "fluid.h"


Fluid::Fluid(int const& _width, int const& _height, double const& Lwidt)
{
    width = _width;
    height = _height;
    dx = Lwidt / (double)width;

    p = Field<double>(width, height, 0, dx);
    d = Field<double>(width, height, 0, dx);
    w = Field<double>(width, height, 0, dx);
    divv = Field<double>(width, height, 0, dx);

    vel0 = 0.3;
}
