#include "image_ppm.h"
#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace std;


void reduc(OCTET *in, OCTET *out, int lignes, int colonnes, int color1, int color2) {

	int ii,jj;
	float iFl;
	float jFl;
	bool b=true;

		for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			for(int k=0;k<3;k++){
				//if(b){
					if(k == color1 || k == color2){
						iFl = (float)i/2.0f;
						jFl = (float)j/2.0f;
						ii = (int)std::floor(iFl);
						jj = (int)std::floor(jFl);
						out[jj*colonnes*3+(ii*3)+k] = in[j*colonnes*3+(i*3)+k];
					}else{
						out[j*colonnes*3+(i*3)+k]=in[j*colonnes*3+(i*3)+k];
					}
				//	b=false;
				//}else{
					b=true;
				//}
			}
			
		}
	}
}


void agrandir(OCTET* in, OCTET *out, int lignes, int colonnes, int color1, int color2){
	int ii,jj;
	float iFl;
	float jFl;
	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			for(int k=0;k<3;k++){
					if(k == color1 || k == color2){
						iFl = (float)i/2.0f;
						jFl = (float)j/2.0f;
						ii = (int)std::floor(iFl);
						jj = (int)std::floor(jFl);
						out[j*colonnes*3+(i*3)+k] = in[jj*colonnes*3+(ii*3)+k];
					}else{
						out[j*colonnes*3+(i*3)+k]=in[j*colonnes*3+(i*3)+k];
					}
			}
			
		}
	}
}

void transforme(OCTET* in, OCTET* out, int lignes, int colonnes){
	for(int i=0;i<lignes*3;i++){
		for(int j=0;j<colonnes*3;j+=3){
				out[j*colonnes+i*3]=0.299*in[j*colonnes+i*3]+0.587*in[j*colonnes+i*3+1]+0.114*in[j*colonnes+i*3+2];// Y
				out[j*colonnes+i*3+1]=-0.1687*in[j*colonnes+i*3]-0.3313*in[j*colonnes+i*3+1]+0.5*in[j*colonnes+i*3+2]+128;// Cb
				out[j*colonnes+i*3+2]=0.5*in[j*colonnes+i*3]-0.4187*in[j*colonnes+i*3+1]-0.0813*in[j*colonnes+i*3+2]+128;// Cr

		}
	}
}

void toRGB(OCTET* in, OCTET* out, int lignes, int colonnes){
	for(int i=0;i<lignes*3;i++){
		for(int j=0;j<colonnes*3;j+=3){
			out[j*colonnes+i*3]=in[j*colonnes+i*3]+1.402*(in[j*colonnes+i*3+2]-128);// R
			out[j*colonnes+i*3+1]=in[j*colonnes+i*3]-0.34414*(in[j*colonnes+i*3+1]+0.5-128)-0.71414*(in[j*colonnes+i*3+2]-128);// G
			out[j*colonnes+i*3+2]=in[j*colonnes+i*3]+1.772*(in[j*colonnes+i*3+1]-128);// B
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
	char reduction[250] = "transformeYCbCr.ppm";
	char agr[250] = "agrandiYCbCr.ppm";
	int lignes, colonnes, nTaille, S;
	if (argc != 2) {
		printf("Usage: ImageIn.ppm\n");
		exit (1) ;
	}
	sscanf (argv[1],"%s",cNomImgLue);
	OCTET *ImgIn, *ImgOut, *ImgOut2, *ImgOut3, *ImgOut4;
	lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &lignes, &colonnes);
	nTaille = lignes * colonnes;

	allocation_tableau(ImgIn, OCTET, nTaille*3);
	lire_image_ppm(cNomImgLue, ImgIn, lignes * colonnes);

	allocation_tableau(ImgOut, OCTET, nTaille*3);

	allocation_tableau(ImgOut2, OCTET, nTaille*3);

	allocation_tableau(ImgOut3, OCTET, nTaille*3);

	allocation_tableau(ImgOut4, OCTET, nTaille*3);

	transforme(ImgIn,ImgOut, lignes,colonnes);
	reduc(ImgOut,ImgOut2,lignes,colonnes,1,2);
	agrandir(ImgOut2,ImgOut3,lignes,colonnes,1,2);
	toRGB(ImgOut3,ImgOut4,lignes,colonnes);

	ecrire_image_ppm(reduction, ImgOut2, lignes, colonnes);
	ecrire_image_ppm(agr, ImgOut4, lignes, colonnes);
	free(ImgIn);
	return 1;
}