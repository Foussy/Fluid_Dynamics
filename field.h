#ifndef FIELD_H
#define FIELD_H

#include <vector>

#include <boundary.h>

template<typename T>

class Field
{
private:
    std::vector<T> c;
    int col;
    int row;
    double dx;

public:
    Field();
};

#endif // FIELD_H
