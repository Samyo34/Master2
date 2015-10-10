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



int main(int argc, char* argv[]){
	char cNomImgLue[250];
	int* p;
	char bin[250] = "binarisation.pgm";
	char bin2[250] = "binarisationByVote.pgm";
	char bin3[250] = "binarisationLocal.pgm";
	int lignes, colonnes, nTaille, S;
	/*if (argc != 3) {
		printf("Usage: ImageIn.pgm taille_module\n");
		exit (1) ;
	}

	sscanf (argv[1],"%s",cNomImgLue);
	//sscanf (argv[2],"%d",p);
	OCTET *ImgIn, *ImgOut, *ImgOut2,*ImgOut3;
	//lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &lignes, &colonnes);
	nTaille = lignes * colonnes;

	//allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, lignes * colonnes);

	/*allocation_tableau(ImgOut, OCTET, nTaille);
	allocation_tableau(ImgOut2, OCTET, nTaille);
	allocation_tableau(ImgOut3,OCTET, nTaille);*/
	/*matrix* principale = new matrix(2,3,false);

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
	principale->printMat();
	matrix* res = principale->mult(vect);
	std::cout<<std::endl;
	res->printMat();*/

	matrix* message = new matrix(4,1,true);
	matrix* code;
	message->set(0,0,1);
	message->set(1,0,0);
	message->set(2,0,1);
	message->set(3,0,1);

	code = message->hamming();
	code->printMat();
	/*ecrire_image_pgm(bin, ImgOut, lignes, colonnes);
	ecrire_image_pgm(bin2, ImgOut2, lignes, colonnes);
	ecrire_image_pgm(bin3,ImgOut3,lignes,colonnes);*/
	//free(ImgIn);
	return 1;
}