#ifndef POINTSPHERIQUE_H
#define POINTSPHERIQUE_H

#include "point.h"
#include <math.h>
#include <QCoreApplication>
#include <QtDebug>

class PointSpherique
{

private:
    float angleA;
    float angleB;
    float dist;

public:
    PointSpherique();*
    PointSpherique(float angleA, float angleB, float dist);
    PointSpherique(Point* p, Point* pointG);
    Point* convCart();
    ~PointSpherique();
    float getDist();
    void setDist(float dist);
};

#endif // POINTSPHERIQUE_H
