#include "image_ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

struct generatrice{
	int gene[7][4];
};

class matrix{
public:


	matrix(int width, int height, bool bin){
		m = new int*[width];
		for(int i =0;i<width;i++){
			m[i] = new int[height];
		}
		this->width = width;
		this->height = height;
		this->isBin = bin;
	}

	int getWidth(){
		return this->width;
	}

	int getHeight(){
		return this->height;
	}

	int at(int i, int j){
		return this->m[i][j];
	}

	void set(int i, int j, int val){
		this->m[i][j]= val;
		//std::cout<<i<<" "<<j<<" "<<val<<std::endl;
	}

	void printMat(){
		for(int i=0;i<this->getWidth();i++){
			for(int j=0;j<this->getHeight();j++){
				std::cout<<this->at(i,j)<<" ";
			}
			std::cout<<std::endl;
		}

	}



matrix* mult(matrix* vect){
	if(this->getHeight() != vect->getWidth() /*|| this->getWidth() != vect->getHeight()*/){
		return NULL;
	}else{
		matrix* res = new matrix(this->getWidth(), vect->getHeight(),this->isBinaire());
		int tot = 0;
		for(int i=0; i<res->getWidth();i++){
			for(int j=0;j<res->getHeight();j++){
				res->set(i,j,res->getFact(this,vect,i,j));
			}	
		}
		return res;
	}
	
}

void generatMatrice(){
	this->gene = new matrix(7,4,true);
	this->veri = new matrix(3,7,true);

	this->gene->set(0,0,1);
	this->gene->set(0,1,1);
	this->gene->set(0,2,0);
	this->gene->set(0,3,1);

	this->gene->set(1,0,1);
	this->gene->set(1,1,0);
	this->gene->set(1,2,1);
	this->gene->set(1,3,1);

	this->gene->set(2,0,1);
	this->gene->set(2,1,0);
	this->gene->set(2,2,0);
	this->gene->set(2,3,0);

	this->gene->set(3,0,0);
	this->gene->set(3,1,1);
	this->gene->set(3,2,1);
	this->gene->set(3,3,1);

	this->gene->set(4,0,0);
	this->gene->set(4,1,1);
	this->gene->set(4,2,0);
	this->gene->set(4,3,0);

	this->gene->set(5,0,0);
	this->gene->set(5,1,0);
	this->gene->set(5,2,1);
	this->gene->set(5,3,0);

	this->gene->set(6,0,0);
	this->gene->set(6,1,0);
	this->gene->set(6,2,0);
	this->gene->set(6,3,1);

	this->veri->set(0,0,0);
	this->veri->set(0,1,0);
	this->veri->set(0,2,0);
	this->veri->set(0,3,1);
	this->veri->set(0,4,1);
	this->veri->set(0,5,1);
	this->veri->set(0,6,1);

	this->veri->set(1,0,0);
	this->veri->set(1,1,1);
	this->veri->set(1,2,1);
	this->veri->set(1,3,0);
	this->veri->set(1,4,0);
	this->veri->set(1,5,1);
	this->veri->set(1,6,1);

	this->veri->set(2,0,1);
	this->veri->set(2,1,0);
	this->veri->set(2,2,1);
	this->veri->set(2,3,0);
	this->veri->set(2,4,1);
	this->veri->set(2,5,0);
	this->veri->set(2,6,1);
}

bool isBinaire(){
	return this->isBin;
}

matrix* getGene(){
	return this->gene;
}

matrix* getveri(){
	return this->gene;
}



matrix* hamming(){
	generatMatrice();
	if (this->isBinaire()) return this->getGene()->mult(this);
}
private:
	int** m;
	int width, height;
	bool isBin; // vrai si la matrice est une matrice binaire

	matrix* gene;
	matrix* veri;


	int getFact(matrix* m1, matrix* m2,int ligne, int colonne){
		int somme=0;
		bool valSomme = true;
		if(!m1->isBinaire()){}
		for(int i=0;i<m1->getHeight();i++){
			if(!m1->isBinaire()){
				somme += m1->at(ligne,i) * m2->at(i,colonne);
			}else{
				if( m1->at(ligne,i) == 0 && m2->at(i,colonne) == 0){
					valSomme = false;
				}
			}
			
		}
		if (!valSomme && m1->isBinaire()) somme = 1;
		return somme;
	}
	
};

matrix* createMatModule(int taille){
	matrix* newMod = new matrix(taille,taille,true);
	int nbPixNoir =(int) (3*(taille*taille/4));
	int nbBlanc = taille*taille-nbPixNoir;
	int cptNoir =0;
	int cptBlanc = 0;
	int val;
	for(int i=0;i<taille;i++){
		for(int j=0;j<taille;j++){
			val = rand()%2;
			if(val ==0){
				cptNoir++;
			}else{
				cptBlanc++;
			}
			if(cptNoir>nbPixNoir){
				val = 1;
				cptBlanc++;
			}else if (cptBlanc > nbBlanc){
				val = 0;
				cptNoir++;
			}
			newMod->set(i,j,val);
		}
	}
	return newMod;
}

void addModule(OCTET* out, int lignes,int x, int y, int tailleModule){
	matrix* mod = createMatModule(tailleModule);
	int cptX=0;
	int cptY=0;
	for(int i=x;i<x+tailleModule;i++){
		cptY=0;
		for(int j =y;j<y+tailleModule;j++){
			if(mod->at(cptX,cptY)==0){
				out[i*lignes+j]=0;
			}else{
				out[i*lignes+j]=255;
			}
			
			cptY++;
		}
		cptX++;
	}
	//std::cout<<"la"<<std::endl;
}

int addNivStock(OCTET* qrCode, OCTET* out, matrix* code, int lignes, int colonnes, int taille){
	int cpt=0;
	std::cout<<code->getWidth()<<std::endl;
	for(int i=0;i<lignes;i+=taille){
		for(int j=0;j<colonnes;j+=taille){
			if((int)qrCode[i*lignes+j] == 0){

				std::cout<<i<<" "<<j<<" "<<(int)qrCode[i*lignes+j]<<" "<<cpt<<" "<<code->at(cpt,0)<<std::endl;
				if(code->at(cpt,0) == 1){
					addModule(out,lignes,i,j,taille);
					//std::cout<<cpt<<std::endl;
					
				}

				if(cpt < code->getWidth()-1){
					cpt++;
				}else{
					return 1;
				}
				
			}
		}

	}
}

void toNdg(OCTET* in,OCTET* out, int lignes, int colonnes){
	int cpt =0;
	float res;
	for(int i=0; i<lignes*3;i+=3){
		for(int j=0;j<colonnes*3;j+=3){
			//res = (in[i*lignes+j]*0.29+in[i*lignes+j+1]*0.59+in[i*lignes+j+2]*0.12);
			//std::cout<<(int)in[i*lignes+j]<<" "<<(int)in[i*lignes+j+1]<<" "<<(int)in[i*lignes+j+2]<<std::endl;
			out[cpt++] = (int)(in[i*lignes+j]*0.29+in[i*lignes+j+1]*0.59+in[i*lignes+j+2]*0.12);
		}
	}
}

int max(int val1, int val2){
	if(val1>=val2){
		return val1;
	}else{
		return val2;
	}
}

int min(int val1, int val2){
	if(val1<=val2){
		return val1;
	}else{
		return val2;
	}
}

void assemblage(OCTET* code, OCTET* image, OCTET* out, int lignes, int colonnes){
	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
				out[i*lignes+j]=max(image[i*lignes+j],code[i*lignes+j]);
				//out[i*lignes+j]=sqrt(code[i*lignes+j]*code[i*lignes+j]+image[i*lignes+j]*image[i*lignes+j]);				
		}
	}
}

void recopie(OCTET* in, OCTET* out, int lignes, int colonnes){
	for(int i=0;i<lignes;i++){
		for(int j=0; j<colonnes; j++){
			out[i*lignes+j]=in[i*colonnes+j];
		}
	}
}

int main(int argc, char* argv[]){
	char cNomImgLue[250];// logo
	char cNomImgLue2[250]="Code.pgm";// QRCode
	int* p;
	char ndg[250] = "ndg.pgm";
	char bin2[250] = "assemblage.pgm";
	char bin3[250] = "nivStock.pgm";
	int lignes, colonnes, nTaille, S;
	if (argc != 2) {
		printf("Usage: Logo.ppm code.pgm\n");
		exit (1) ;
	}
	sscanf (argv[1],"%s",cNomImgLue);
	//sscanf (argv[2],"%s",cNomImgLue2);
	OCTET *ImgIn, *ImgOut, *ImgOut2,*ImgOut3;
	lire_nb_lignes_colonnes_image_pgm(cNomImgLue2, &lignes, &colonnes);
	nTaille = lignes * colonnes;
	allocation_tableau(ImgIn, OCTET, nTaille);// logo
	lire_image_pgm(cNomImgLue2, ImgIn, lignes * colonnes);

	allocation_tableau(ImgOut, OCTET, nTaille);// QRcode
	//lire_image_pgm(cNomImgLue2,ImgOut,lignes*colonnes); // on suppose que les deux image on la même taille

	allocation_tableau(ImgOut2, OCTET, nTaille);// image de sortie
	allocation_tableau(ImgOut3,OCTET, nTaille);// ImgOut3 va stocker ImgIn en ndg*/

	/* Question 1.1 
	matrix* principale = new matrix(2,3,false);

	for(int i=0;i<2;i++){
		for(int j=0;j<3;j++){
			principale->set(i,j,i+j);
		}
	}

	matrix* vect = new matrix(3,2,false);
	for(int i=0;i<3;i++){
		for(int j=0; j<2;j++){
			vect->set(i,j,10-(i+j));
		}
	}
	std::cout<<"Matrice principale :"<<std::endl;
	principale->printMat();
	std::cout<<"Vecteur :"<<std::endl;
	vect->printMat();
	matrix* res = principale->mult(vect);
	std::cout<<std::endl;
	std::cout<<"Resultat de la multiplication :"<<std::endl;
	res->printMat();*/
	/* Question 1.2 */
	matrix* message = new matrix(7,1,true);
	matrix* code;
	message->set(0,0,1);
	message->set(1,0,0);
	message->set(2,0,1);
	message->set(3,0,1);
	message->set(4,0,0);
	message->set(5,0,0);
	message->set(6,0,1);
	/*std::cout<<"Message a encoder :"<<std::endl;
	message->printMat();

	code = message->hamming();
	std::cout<<"\nResultat de l'encodage"<<std::endl;
	code->printMat();*/

	/*Question 2.1 */
	recopie(ImgIn, ImgOut, lignes, colonnes);
	addNivStock(ImgIn,ImgOut,message,lignes,colonnes,7);
	 /* Question 3
	toNdg(ImgIn,ImgOut3, lignes,colonnes);
	assemblage(ImgOut,ImgOut3,ImgOut2,lignes,colonnes);*/


	ecrire_image_pgm(bin3, ImgOut, lignes, colonnes);
	//ecrire_image_pgm(bin2, ImgOut2, lignes, colonnes);
	/*ecrire_image_pgm(bin3,ImgOut3,lignes,colonnes);*/
	//free(ImgIn);
	return 1;
}