#include "point.h"

Point::Point()
{
}

Point::Point(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Point::Point(Point *p)
{
    this->x = p->getX();
    this->y = p->getY();
    this->z = p->getZ();
}

float Point::getX()
{
    return this->x;
}

float Point::getY()
{
    return this->y;
}

float Point::getZ()
{
    return this->z;
}
