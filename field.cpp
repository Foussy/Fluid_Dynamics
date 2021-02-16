#include "field.h"

template<typename T>
Field<T>::Field()
{
    col = 0;
    row = 0;
    c.clear();
    dx = 1;
}

template<typename T>
Field<T>::Field(int const& _col, int const& _row, T const& val0, double const &_dx)
{
    col = _col;
    row = _row;
    resize(col, row, val0);
    dx = _dx;
}

template<typename T>
void Field<T>::resize(int const& _col, int const& _row, T const& val0)
{
    col = _col;
    row = _row;
    c.resize(col*row,val0);
}

template<typename T>
int Field<T>::getRow() const
{
    return row;
}

template<typename T>
int Field<T>::getCol() const
{
    return col;
}

template<typename T>
void Field<T>::setDx(double const& _dx)
{
    dx = _dx;
}

template<typename T>
double Field<T>::getDx() const
{
    return dx;
}

//

template <typename T>
void rot(Field<T> &rotF, Field<sf::Vector2f> const& F)
{
    for (int i(1); i < F.getCol() - 1; i++)
        for (int j(1); j < F.getRow() - 1; j++)
            rotF(i, j) = (F(i + 1, j).y - F(i - 1, j).y - F(i, j + 1).x + F(i, j - 1).x) / (2 * F.getDx());
}
