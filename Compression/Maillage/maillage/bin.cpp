#include "bin.h"

Bin::Bin()
{

}

Bin::Bin(float rMin, float rMax)
{
    this->rMin = rMin;
    this->rMax = rMax;
    calcMid();
}

Bin::~Bin()
{

}

void Bin::addPoint(PointSpherique *point)
{
    //PointSpherique* point = new PointSpherique(p,pointG);
    this->tab.push_back(point);
}

void Bin::write(bool bin)
{
    normalize();
    if(bin){
        if(this->mean() < this->mid){
            float val = this->mid - this->moyenne;
            inc(val+ 0.001);
        }
    }else{
        if(this->mean() > this->mid){
            float val = this->moyenne - this->mid;
            dec(val-0.001);
        }
    }
    normalizeInv();
}

float Bin::mean()
{
    float mean = 0;
    for(int i=0;i<tab.size();i++){
        mean += tab.at(i)->getDist();
    }
    mean = mean/tab.size();
    this->moyenne = mean;

    return mean;

}

void Bin::normalize()
{
    float norme = rMax - rMin;
    for(int i = 0; i<tab.size();i++) {
        float r = (tab.at(i)->getDist() - rMin) / norme;
        tab.at(i)->setDist(r);
    }
}

void Bin::normalizeInv()
{
    float norme = rMax - rMin;
    for(int i = 0; i<tab.size();i++) {
       float r = tab.at(i)->getDist() * norme + rMin;
       tab.at(i)->setDist(r);
    }
}

bool Bin::appartient(PointSpherique *p)
{
    return (p->getDist() > this->rMin && p->getDist()<this->rMin);
}

void Bin::calcMid()
{
   this->mid = this->rMin + (this->rMax - this->rMin);
}

void Bin::inc(float inc)
{
    float val = inc/tab.size();
    for(int i = 0; i<tab.size();i++){
        tab.at(i)->setDist(tab.at(i)->getDist()+val);
    }
}

void Bin::dec(float inc)
{
    float val = inc/tab.size();
    for(int i = 0; i<tab.size();i++){
        tab.at(i)->setDist(tab.at(i)->getDist()-val);
    }
}

