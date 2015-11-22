#include "face.h"

Face::Face()
{
}

Face::Face(Point *a, Point *b, Point *c)
{
    this->a=a;
    this->b=b;
    this->c=c;
}

Point *Face::getPointA()
{
    return this->a;
}

Point *Face::getPointB()
{
    return this->b;
}

Point *Face::getPointC()
{
    return this->c;
}
