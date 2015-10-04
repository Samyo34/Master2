#include "image_ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

using namespace std;

int getMax(OCTET* in, int lignes, int colonnes){
	int max=0;
	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			if(in[i*lignes+j]>max){
				max = in[i*lignes+j];
			}
		}
	}
	return max;
}

int getMin(OCTET* in,int lignes, int colonnes){
	int min = 255;
	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			if(in[i*lignes+j]<min){
				min = in[i*lignes+j];
			}
		}
	}

	return min;
}


void binarisation(OCTET* in, OCTET* out, int lignes, int colonnes, int min, int max){
	int th = (max-min)/2;

	for(int i=0;i<lignes;i++){
		for(int j = 0;j<colonnes;j++){
			if(in[i*lignes+j]>th){
				out[i*lignes+j]=255;
			}else{
				out[i*lignes+j]=0;
			}
		}
	}
}

int vote(OCTET* ImgIn,int posI,int posJ, int lignes, int colonnes,int p, int th){
	int nbSup =0;
	int nbInf=0;
	for(int i=posI;i<posI+p;i++){
		for(int j=posJ;j<posJ+p;j++){
			if(ImgIn[i*lignes+j]>th){
				nbSup++;
			}else{
				nbInf++;
			}
		}
	}

	if(nbSup>nbInf){
		return 255;
	}else{
		return 0;
	}
}

void binarisationByVote(OCTET* in, OCTET* out, int lignes, int colonnes, int min, int max, int p){
	int th = (max-min)/2;
	int res;

	for(int i=0;i<lignes;i+=p){
		for(int j = 0;j<colonnes;j+=p){
				res = vote(in,i,j,lignes,colonnes,p,th);
				for(int x=0;x<p;x++){
					for(int y=0;y<p;y++){
						if(res>0){
							out[(i+x)*lignes+(j+y)]=255;
						}else{
							out[(i+x)*lignes+(j+y)]=0;
						}
					}
				}
			
		}
	}
}
/*
 *Retourne un tableau contenant la moyenne des ndg et l'ecart type de la fenetre centré en x,y
 */
float* getLocal(OCTET* in, int lignes, int colonnes, int tailleFenetre, int x, int y){
	int taille = (tailleFenetre-1)/2;
	int debX = x-taille;
	int debY = y-taille;
	int finX = x+taille;
	int finY = y+taille;
	float* tab = new float[2];
	float somme =0;
	int cpt =0;
	if(debX<=0){
		debX=x;
	}

	if(debY<=0){
		debY=y;
	}

	if(finX>=lignes){
		finX = lignes;
	}

	if(finY>=colonnes){
		finY = colonnes;
	}
	for(int i=debX;i<finX;i++){
		for(int j=debY;j<finY;j++){
			somme += in[(i*lignes+j)];
			cpt++;
		}
	}
	tab[0]=somme/(float)cpt;

	for(int i=debX;i<finX;i++){
		for(int j=debY;j<finY;j++){
			somme += pow(in[(i*lignes+j)]-tab[0],2);
		}
	}
	tab[1]=somme/(float)cpt;
	return tab;
}

void binarisationLocal(OCTET* in, OCTET* out, int lignes, int colonnes, int tailleFenetre){
	float* tab;
	float seuil;
	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			tab = getLocal(in, lignes, colonnes,tailleFenetre,i,j);

			seuil = tab[0] + 0.2 * tab[1];
			std::cout<<seuil<<std::endl;
			if(in[i*lignes+j]>seuil){
				out[i*lignes+j]=255;
			}else{
				out[i*lignes+j]=0;
			}
		}
	}
}

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

	allocation_tableau(ImgOut, OCTET, nTaille);
	allocation_tableau(ImgOut2, OCTET, nTaille);
	allocation_tableau(ImgOut3,OCTET, nTaille);

	int min = getMin(ImgIn,lignes,colonnes);
	int max = getMax(ImgIn,lignes,colonnes);

	binarisation(ImgIn,ImgOut,lignes,colonnes,min,max);
	binarisationByVote(ImgIn,ImgOut2,lignes,colonnes,min,max,9);
	binarisationLocal(ImgIn, ImgOut3,lignes,colonnes,7);

	ecrire_image_pgm(bin, ImgOut, lignes, colonnes);
	ecrire_image_pgm(bin2, ImgOut2, lignes, colonnes);
	ecrire_image_pgm(bin3,ImgOut3,lignes,colonnes);
	free(ImgIn);
	return 1;
}