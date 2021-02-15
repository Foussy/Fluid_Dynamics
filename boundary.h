#ifndef BOUNDARY_H
#define BOUNDARY_H

#include <iostream>

enum bnd { fluid, in, out};
enum loc { center, edge, corner, err = 20};

template <typename T>
class Wall
{
public:
    Wall() : bnd(fluid), N(0), S(0), E(0), W(0), neighbour(0), loc(center) {}

    bnd bnd;
    loc loc;
    int N, S, E, W;
    int neighbour;

    void updateLoc()
    // update the location depending on the number of neighbours
    {
        neighbour = N + S + E + W;

        switch (neighbour)
        {
        case 2:
            if(N*S == 1 || E*W == 1)
                loc = edge;
            else
                loc = corner;
            break;

        case 3:
            loc = edge;
            break;

        case 4:
            loc = center;
            break;

        default:
            loc = err;
            break;
        }
    }
};


#endif // BOUNDARY_H
