#ifndef MAILLAGE_H
#define MAILLAGE_H

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QVector>
#include <QCoreApplication>
#include <QtDebug>

#include "face.h"
#include "bin.h"

class Maillage
{
private:
    QVector<Face*> maille;
    QVector<int> maillePos;
    std::vector<Point*> points;

    QVector<Bin* > bins;
    int nbPoint;

    void toSphere();
    QVector<float> getMinMax();
    void findBins(int sizeM);

public:
    Maillage();
    Maillage(QVector<Face*> maille);
    void add(Face* face);
    void lireMaillage(char* fileName);
    void ecrireMaillage(char* fileName);
    Point* calculG();
    void MakeBins(int size);
    void write(QVector<bool> mess);

    QVector<Bin*> getBins();


    std::vector<std::string> split(std::string ligne);
    double* getVal(std::vector<std::string> ligne);
    QVector<float> getValS(QStringList ligne);
    QVector<PointSpherique*> sphere;
};

#endif // MAILLAGE_H
