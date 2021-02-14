#ifndef FLUID_H
#define FLUID_H


class Fluid
        /*
         * this class describes the area in which the fluid is contained
         */
{
    private:
        int width;  // width of the rectangle
        int length; // length of the rectangle
        double dx;  // size of a fluid element
        double Vx0; // x velocity at t = 0
        double Vy0; // y velocity at t = 0

    public:
        Fluid(int const& _width, int const& _height, double const& Lwidth);

        void update(double const& dt);


};

#endif // FLUID_H
