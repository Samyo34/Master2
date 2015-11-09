#ifndef POINT_H
#define POINT_H

class Point
{

private:
    float x,y,z;
public:
    Point();
    Point(float x, float y, float z);
    Point(Point* p);
    float getX();
    float getY();
    float getZ();
};

#endif // POINT_H
