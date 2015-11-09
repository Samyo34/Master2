#include "maillage.h"

Maillage::Maillage()
{

}

Maillage::Maillage(std::vector<Face *> maille)
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
    int nbSommet, nbTriangles;
        std::ifstream fichier(fileName, std::ios::in);
        std::string ligne;


        if(fichier){

            getline(fichier,ligne);// Lecture OFF
            getline(fichier,ligne);// nombre de sommet, triangles...
            double* vals = getVal(split(ligne));
            nbSommet = (int)vals[0];
            nbTriangles = (int)vals[1];
            Point *points[nbSommet];
            this->nbPoint = nbSommet;
            // Lecture Sommets
            for(int i = 0;i<nbSommet;i++){
                getline(fichier, ligne);
                vals = getVal(split(ligne));
                points[i]= new Point(vals[0],vals[1],vals[2]);
            }

            // Lecture triangles
            for(int i=0;i<nbTriangles;i++){
                getline(fichier,ligne);
                vals = getVal(split(ligne));
                maille.push_back(new Face(new Point(points[(int)vals[1]]),
                                        new Point(points[(int)vals[2]]),
                                        new Point(points[(int)vals[3]])));
            }
            //nbTri = nbTriangles;
        }else{
            std::cerr<<"erreur lors de la lectur du fichier"<<std::endl;
        }
}

void Maillage::ecrireMaillage(char *fileName)
{
    // TODO : a voir quand on en a besoin
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
