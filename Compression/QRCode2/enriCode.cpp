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


	matrix(int width, int height){
		m = new int*[width];
		for(int i =0;i<width;i++){
			m[i] = new int[height];
		}
		this->width = width;
		this->height = height;
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
	if(this->getHeight() != vect->getWidth() || this->getWidth() != vect->getHeight()){
		return NULL;
	}else{
		matrix* res = new matrix(this->getWidth(), vect->getHeight());
		int tot = 0;
		for(int i=0; i<res->getWidth();i++){
			for(int j=0;j<res->getHeight();j++){
				res->set(i,j,res->getFact(this,vect,i,j));
			}	
		}
		generatMatrice();
		return res;
	}
	
}

void generatMatrice(){
	this->gene[0][0]=1;
	this->gene[0][1]=1;
	this->gene[0][2]=0;
	this->gene[0][3]=1;

	this->gene[1][0]=1;
	this->gene[1][1]=0;
	this->gene[1][2]=1;
	this->gene[1][3]=1;

	this->gene[2][0]=1;
	this->gene[2][1]=0;
	this->gene[2][2]=0;
	this->gene[2][3]=0;

	this->gene[3][0]=0;
	this->gene[3][1]=1;
	this->gene[3][2]=1;
	this->gene[3][3]=1;

	this->gene[4][0]=0;
	this->gene[4][1]=1;
	this->gene[4][2]=0;
	this->gene[4][3]=0;

	this->gene[5][0]=0;
	this->gene[5][1]=0;
	this->gene[5][2]=1;
	this->gene[5][3]=0;

	this->gene[6][0]=0;
	this->gene[6][1]=0;
	this->gene[6][2]=0;
	this->gene[6][3]=1;

	this->veri[0][0]=0;
	this->veri[0][1]=0;
	this->veri[0][2]=0;
	this->veri[0][3]=1;
	this->veri[0][4]=1;
	this->veri[0][5]=1;
	this->veri[0][6]=1;

	this->veri[1][0]=0;
	this->veri[1][1]=1;
	this->veri[1][2]=1;
	this->veri[1][3]=0;
	this->veri[1][4]=0;
	this->veri[1][5]=1;
	this->veri[1][6]=1;

	this->veri[2][0]=1;
	this->veri[2][1]=0;
	this->veri[2][2]=1;
	this->veri[2][3]=0;
	this->veri[2][4]=1;
	this->veri[2][5]=0;
	this->veri[2][6]=1;
}

matrix* hamming(matrix*  message){
	return this->
}
private:
	int** m;
	int width, height;

	int gene[7][4];
	int veri[3][7];


	int getFact(matrix* m1, matrix* m2,int ligne, int colonne){
		int somme=0;
		for(int i=0;i<m1->getHeight();i++){
			somme += m1->at(ligne,i) * m2->at(i,colonne);
		}
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
	matrix* principale = new matrix(2,3);

	for(int i=0;i<2;i++){
		for(int j=0;j<3;j++){
			principale->set(i,j,i+j);
		}
	}

	matrix* vect = new matrix(3,2);
	for(int i=0;i<3;i++){
		for(int j=0; j<2;j++){
			vect->set(i,j,10-(i+j));
		}
	}
	principale->printMat();
	matrix* res = principale->mult(vect);
	std::cout<<std::endl;
	res->printMat();

	/*ecrire_image_pgm(bin, ImgOut, lignes, colonnes);
	ecrire_image_pgm(bin2, ImgOut2, lignes, colonnes);
	ecrire_image_pgm(bin3,ImgOut3,lignes,colonnes);*/
	//free(ImgIn);
	return 1;
}