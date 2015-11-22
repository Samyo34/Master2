#ifndef FACE_H
#define FACE_H

#include "point.h"

class Face
{
private:
    Point* a;
    Point* b;
    Point* c;

public:
    Face();
    Face(Point* a, Point* b, Point* c);
    Point* getPointA();
    Point* getPointB();
    Point* getPointC();
};

#endif // FACE_H
