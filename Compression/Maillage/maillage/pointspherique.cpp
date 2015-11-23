#include "pointspherique.h"

PointSpherique::PointSpherique()
{

}

*PointSpherique::PointSpherique(float angleA, float angleB, float dist)
{
    this->angleA = angleA;
    this->angleB = angleB;
    this->dist = dist;
}

PointSpherique::PointSpherique(Point *p, Point *pointG)
{
    this->dist = sqrt(pow((p->getX() - pointG->getX()),2) + pow((p->getY()-pointG->getY()),2) + pow((p->getZ()-pointG->getZ()),2));

    this->angleA = atan2((p->getX()-pointG->getX()),(p->getY()-pointG->getY()));

    this->angleB = acos((p->getZ()-pointG->getZ())/this->dist);

}

Point *PointSpherique::convCart()
{
    return new Point(this->dist*sin(this->angleB)*sin(this->angleA),
                     this->dist*sin(this->angleB)*cos(this->angleA),
                     this->dist*cos(this->angleB));
}

PointSpherique::~PointSpherique()
{

}

float PointSpherique::getDist()
{
    return this->dist;
}

void PointSpherique::setDist(float dist)
{
    this->dist = dist;
}

