#include "image_ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>


class matrix{
public:
	matrix(int width, int height){
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




	matrix* mult(matrix* vect){
		if(this->getHeight() != vect->getWidth() || this->getWidth() != vect->getHeight()) return -1;
		matrix* res = new matrix(this->getHeight(), vect->getWidth());
		int tot = 0;
		/*  /!\ Ceci est l'ago :  ca ne peux pas fonctionner comme ça (m est private) /!\ */
		for(int i=0; i<res->getHeight();i++){
			for(int j=0;j<res->getWidth();j++){
				for(int x = 0;x<this->getHeight();x++){
					for(int y=0;y<this->getWidth();y++){
						res->m[i][j]+=this->m[x][y]*vect->m[y][x];
					}
				}
			}
		}
	}
private:
	int** m;
	int width, height;
};



int main(int argc, char* argv[]){
	char cNomImgLue[250];
	int* p;
	char bin[250] = "binarisation.pgm";
	char bin2[250] = "binarisationByVote.pgm";
	char bin3[250] = "binarisationLocal.pgm";
	int lignes, colonnes, nTaille, S;
	if (argc != 3) {
		printf("Usage: ImageIn.pgm taille_module\n");
		exit (1) ;
	}

	sscanf (argv[1],"%s",cNomImgLue);
	//sscanf (argv[2],"%d",p);
	OCTET *ImgIn, *ImgOut, *ImgOut2,*ImgOut3;
	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &lignes, &colonnes);
	nTaille = lignes * colonnes;

	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, lignes * colonnes);

	/*allocation_tableau(ImgOut, OCTET, nTaille);
	allocation_tableau(ImgOut2, OCTET, nTaille);
	allocation_tableau(ImgOut3,OCTET, nTaille);*/
	matrix* principale = new matrix(2,3);
	matrix* vect = new matrix(3,2);


	/*ecrire_image_pgm(bin, ImgOut, lignes, colonnes);
	ecrire_image_pgm(bin2, ImgOut2, lignes, colonnes);
	ecrire_image_pgm(bin3,ImgOut3,lignes,colonnes);*/
	free(ImgIn);
	return 1;
}