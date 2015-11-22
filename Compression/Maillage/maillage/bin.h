#ifndef BIN_H
#define BIN_H

#include <QVector>
#include "point.h"
#include "pointspherique.h"

class Bin
{
public:
    Bin();
    Bin(float rMin, float rMax);
    ~Bin();

    void addPoint(PointSpherique *point);
    void write(bool bin);
    float mean();
    void normalize();
    void normalizeInv();
    bool appartient(PointSpherique* p);
    void calcMid();

private:

    void inc(float inc);
    void dec(float inc);

    QVector<PointSpherique* > tab;
    float rMin, rMax;
    float moyenne;
    float mid;
};

#endif // BIN_H
