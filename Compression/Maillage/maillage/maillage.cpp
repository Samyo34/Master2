#include "maillage.h"

Maillage::Maillage()
{

}

Maillage::Maillage(QVector<Face *> maille)
{
    this->maille = maille;

}

void Maillage::add(Face *face)
{
    this->maille.push_back(face);
}


double* Maillage::getVal(std::vector<std::string> ligne){
    double* tab= new double[4];
    for(int i =0;i<ligne.size();i++){
        tab[i]=atof(ligne[i].c_str());
    }
    return tab;
}

QVector<float> Maillage::getValS(QStringList ligne)
{
    QVector<float> tab;
    for(int i = 0; i<ligne.size();i++){
        tab.push_back(ligne.at(i).toDouble());
    }
    return tab;

}



std::vector<std::string> Maillage::split(std::string ligne){
    std::istringstream iss(ligne);
    std::vector<std::string> res;
    std::string mot;
    while(getline(iss,mot,' ')){
        res.push_back(mot);
    }
    return res;
}


void Maillage::lireMaillage(char *fileName)
{

    QFile file(fileName);
     int nbSommet, nbTriangles;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

  //  while (!file.atEnd()) {

        QString line = file.readLine();// Lecture OFF
        line = file.readLine();// lecture nb points, nb triangles
        QVector<float> vals = getValS(line.split(" "));
        nbSommet = (int)vals.at(0);

        nbTriangles = (int)vals.at(1);

        this->nbPoint = nbSommet;
        // Lecture Sommets
        for(int i = 0;i<nbSommet;i++){
            line = file.readLine();
            vals = getValS(line.split(" "));
            //points[i] = new Point(vals[0],vals[1],vals[2]);
            this->points.push_back(new Point(vals.at(0),vals.at(1),vals.at(2)));
        }
        std::cout<<"fin lecture sommets"<<std::endl;
        // Lecture Faces
        for(int i = 0;i<nbTriangles;i++){

            line = file.readLine();
            vals = getValS(line.split(" "));
            maille.push_back(new Face(new Point(points.at((int)vals.at(1))),
                                    new Point(points.at((int)vals.at(2))),
                                    new Point(points.at((int)vals.at(3)))));
            maillePos.push_back(vals.at(1));
            maillePos.push_back(vals.at(2));
            maillePos.push_back(vals.at(3));
        }
        std::cout<<"fin lecture faces"<<std::endl;



   // }

}

void Maillage::ecrireMaillage(char *fileName)
{
    // TODO : a voir quand on en a besoin
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&file);
        out << "OFF"<< "\n";
        out << sphere.size() << " "<< maille.size()<< " 0"<<"\n";
        for(int i = 0 ;i<sphere.size();i++){
            Point* p = sphere.at(i)->convCart();
            out<< p->getX() << " " << p->getY()<< " " << p->getZ() << "\n";
        }

        for(int i = 0 ;i<maille.size();i++){
            out<< "3" << " " <<maillePos.at(3*i) << " " << maillePos.at(3*i+1) << " "<<maillePos.at(3*i+2)<< "\n";
        }
        file.close();
/*
    ofstream fichier(fileName, ios::out | ios::trunc);

    if(fichier){
        // Ecriture OFF
        fichier << "OFF"<<std::endl;
        // Ecriture nbPoint, nbFaces
        fichier<<nbPoint<<" "<<maille.size()<<" "<< "0"<< std::endl;

        //

    }else{
        cerr << "Erreur à l'ouverture !" << endl;
    }
*/
}

Point *Maillage::calculG()
{
    float x = 0;
    float y = 0;
    float z = 0;
    for(int i = 0; i<this->points.size();i++){
        x += points.at(i)->getX();

        y += points.at(i)->getY();

        z += points.at(i)->getZ();;
    }

    Point* p = new Point(x/points.size(), y/points.size(), z/points.size());
    return p;

}

void Maillage::MakeBins(int size)
{
    findBins(size);
    for(int i=0;i<sphere.size();i++){
        for(int j = 0;j<bins.size();j++){
            if(bins.at(j)->appartient(sphere.at(i))){
                bins.at(j)->addPoint(sphere.at(i));
            }
        }
    }

}

void Maillage::write(QVector<bool> mess)
{
    MakeBins(mess.size());
    for(int i = 0;i<bins.size();i++){
        bins.at(i)->write(mess.at(i));
    }
    std::cout<<"fin ecriture"<<std::endl;

}

void Maillage::toSphere()
{
    Point* p = calculG();

    for(int i = 0;i<points.size();i++){
        this->sphere.push_back(new PointSpherique(points.at(i),p));
    }
}

QVector<float> Maillage::getMinMax()
{
    float min = sphere.at(0)->getDist();
    float max = min;
    for(int i=1;i<sphere.size();i++){
        if(sphere.at(i)->getDist()>max){
            max = sphere.at(i)->getDist();
        }

        if(sphere.at(i)->getDist()<min){
            min = sphere.at(i)->getDist();
        }
    }
    QVector<float> res;
    res.push_back(min);
    res.push_back(max);
    return res;
}

void Maillage::findBins(int sizeM)
{
    toSphere();
    QVector<float> minMax = getMinMax();
    float min = minMax.at(0);
    float max = minMax.at(1);
    int sizeBin = (max - min)/sizeM;

    for(int i = 0;i<sizeM-1;i++){
        bins.push_back(new Bin(min+i*sizeBin,
                               (min+(i+1)*sizeBin-0.0001)));
    }


}

QVector<Bin *> Maillage::getBins()
{
    return this->bins;
}
