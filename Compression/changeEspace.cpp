#include "image_ppm.h"
#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace std;

void transforme(OCTET* in, OCTET* out, int lignes, int colonnes){
	for(int i=0;i<lignes*3;i++){
		for(int j=0;j<colonnes*3;j++){
				out[j*colonnes+i]=0.299*in[j*colonnes+i]+0.587*in[j*colonnes+i+1]+0.114*in[j*colonnes+i+2];// Y
				out[j*colonnes+i+1]=-0.1687*in[j*colonnes+i]-0.3313*in[j*colonnes+i+1]+0.5*in[j*colonnes+i+2]+128;// Cb
				out[j*colonnes+i+2]=0.5*in[j*colonnes+i]-0.4187*in[j*colonnes+i+1]-0.0813*in[j*colonnes+i+2]+128;// Cr

		}
	}
}

float psnr(OCTET* in, OCTET* in2, int lignes, int colonnes){
	float somme=0;
	for(int i = 0;i<lignes*3;i++){
		for(int j=0;j<colonnes*3;j++){
			for(int k=0;k<3;k++){
				somme += (in[j*colonnes+i+k]-in2[j*colonnes+i+k])*(in[j*colonnes+i+k]-in2[j*colonnes+i+k]);
			}
			
		}
	}
	float eqm = somme/lignes*colonnes*9;
	return 10*log10(255*255/eqm);
}

int main(int argc, char* argv[]){
	char cNomImgLue[250];
	char reduction[250] = "transformeYCbCr.jpg";
	char agr[250] = "agrandi.ppm";
	int lignes, colonnes, nTaille, S;
	if (argc != 2) {
		printf("Usage: ImageIn.ppm\n");
		exit (1) ;
	}
	sscanf (argv[1],"%s",cNomImgLue);
	OCTET *ImgIn, *ImgOut, *ImgOut2;
	lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &lignes, &colonnes);
	nTaille = lignes * colonnes;

	allocation_tableau(ImgIn, OCTET, nTaille*3);
	lire_image_ppm(cNomImgLue, ImgIn, lignes * colonnes);

	allocation_tableau(ImgOut, OCTET, nTaille*3);

	allocation_tableau(ImgOut2, OCTET, nTaille*3)

	transforme(ImgIn,ImgOut, lignes,colonnes);

	ecrire_image_ppm(reduction, ImgOut, lignes, colonnes);
	//ecrire_image_ppm(agr, ImgOut2, lignes, colonnes);
	free(ImgIn);
	return 1;
}