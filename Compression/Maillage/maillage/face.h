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
};

#endif // FACE_H
