#include "coordonnee.h"

float coordonnee::getY() const
{
    return y;
}

void coordonnee::setY(float value)
{
    y = value;
}

float coordonnee::getX() const
{
    return x;
}

void coordonnee::setX(float value)
{
    x = value;
}

coordonnee::coordonnee()
{

}

coordonnee::coordonnee(float _x, float _y){
    x = _x;
    y = _y;
}

