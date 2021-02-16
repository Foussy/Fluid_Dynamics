#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

#include <SFML/Graphics.hpp>

#include <boundary.h>

template<typename T>

class Field
        /*
         * this class describes the area composed with fluid elements
         */
{
private:
    std::vector<T> c;
    int col;
    int row;
    double dx;

public:
    Field();
    Field(int const& _col, int const& _row, T const& val0, double const &_dx);

    void resize(int const& _col, int const& _row, T const& _val0);

    int getRow() const;
    int getCol() const;
    void setDx(double const& _scale);
    double getDx() const;
};

template<typename T>
void rot(Field<T> &rotF, Field<sf::Vector2f> const& F);

template<typename T>
void rot(Field<T> &rotF, Field<sf::Vector2f> const& F);

template<typename T>
void grad(Field<sf::Vector2f> &gradF, Field<T> const& F);

template<typename T>
void div(Field<T> &divF, Field<sf::Vector2f> const& F);

template<typename T>
void gradT(Field<sf::Vector2f> &gradF, Field<T> const& F);


template<typename T>
T bilerp(Field<T> const& F, sf::Vector2f const& X);

template<typename T>
void advect(Field<sf::Vector2f> &v, Field<T> &d, Field<boundary> const& bound, double const& dt);

template<typename T>
void relaxation(Field<T> &x, Field<T> const& b, Field<boundary> const& bound, double const& alpha, double const& beta, int const& kmax);


#endif // FIELD_H
