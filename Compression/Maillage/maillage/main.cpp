#include <iostream>
#include "maillage.h"

using namespace std;

int main()
{
    Maillage* m = new Maillage();
    m->lireMaillage(":/bunny.off");
    QVector<bool> message;
    message.push_back(false);
    message.push_back(true);
    message.push_back(true);
    message.push_back(false);
    m->write(message);
    m->ecrireMaillage("res.off");
    return 0;
}

