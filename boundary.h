#ifndef BOUNDARY_H
#define BOUNDARY_H

enum bnd { fluid, in, out};
enum loc { center, edge, corner, err = 20};


class boundary
        /*
         * this class describes the boundaries of a fluid element
         */
{
public:
    boundary() : bnd(fluid), loc(center), N(0), S(0), E(0), W(0), neighbour(0){}

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
