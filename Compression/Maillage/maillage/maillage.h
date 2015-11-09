#ifndef MAILLAGE_H
#define MAILLAGE_H

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include "face.h"

class Maillage
{
private:
    std::vector<Face*> maille;
    int nbPoint;
public:
    Maillage();
    Maillage(std::vector<Face*> maille);
    void add(Face* face);
    void lireMaillage(char* fileName);
    void ecrireMaillage(char* fileName);

    std::vector<std::string> split(std::string ligne);
    double* getVal(std::vector<std::string> ligne);
};

#endif // MAILLAGE_H
