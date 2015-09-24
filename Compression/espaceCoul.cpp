#include "image_ppm.h"
#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace std;


int getIndex(int x, int y, int imgW){
	return y * imgW + x;
}

void reduc(OCTET *in, OCTET *out, int lignes, int colonnes, int color1, int color2) {
	/*int index, index2;
	for(int i = 0; i < lignes; i++){
		for(int j = 0; j < colonnes; j++){
			index = getIndex(i * 3, j, lignes*3);
			for(int k = 0; k < 3; k++){
				if(k == color1 || k == color2){
					if(i <= lignes/2 && j <= colonnes/2){
						out[index+k] = in[getIndex(i * 3 * 2, j * 2, lignes*3)];
					}else{
						out[index+k] = 0;
					}
				}else{
					out[index+k] = in[index+k];
				}
			}
		}
	}*/
			int ii,jj;
	float iFl;
	float jFl;
	bool b = true;

		for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			for(int k=0;k<3;k++){
				//if(i<=lignes/2 && j<=colonnes/2){
				if(b){
					if(k == color1 || k == color2){
						iFl = (float)i/2.0f;
						jFl = (float)j/2.0f;
						ii = (int)std::floor(iFl);
						jj = (int)std::floor(jFl);
						out[jj*colonnes*3+(ii*3)+k] = in[j*colonnes*3+(i*3)+k];
						/*out[j*2*colonnes*3+(i*3*2)+k]=in[j*colonnes*3+(i*3)+k];
						out[j*2*colonnes*3+(i*3*2)+k+1]=in[j*colonnes*3+(i*3)+k];
						out[(j+1)*colonnes*3+(i*3)+k]=in[j*colonnes*3+(i*3)+k];
						out[(j+1)*colonnes*3+(i*3)+k+1]=in[j*colonnes*3+(i*3)+k];*/
					}else{
						out[j*colonnes*3+(i*3)+k]=in[j*colonnes*3+(i*3)+k];
					}
					b = false;
				}else{
					b=true;
				}

						
				//}else{
					//out[j*colonnes*3+(i*3)+k]=255;
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
				//if(i<=lignes/2 && j<=colonnes/2){
					if(k == color1 || k == color2){
						iFl = (float)i/4.0f;
						jFl = (float)j/4.0f;
						ii = (int)std::floor(iFl);
						jj = (int)std::floor(jFl);
						out[j*colonnes*3+(i*3)+k] = in[jj*colonnes*3+(ii*3)+k];
						/*out[j*2*colonnes*3+(i*3*2)+k]=in[j*colonnes*3+(i*3)+k];
						out[j*2*colonnes*3+(i*3*2)+k+1]=in[j*colonnes*3+(i*3)+k];
						out[(j+1)*colonnes*3+(i*3)+k]=in[j*colonnes*3+(i*3)+k];
						out[(j+1)*colonnes*3+(i*3)+k+1]=in[j*colonnes*3+(i*3)+k];*/
					}else{
						out[j*colonnes*3+(i*3)+k]=in[j*colonnes*3+(i*3)+k];
					}

						
				//}else{
					//out[j*colonnes*3+(i*3)+k]=255;
				//}
			}
			
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
	char reduction[250] = "reduite.ppm";
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

	reduc(ImgIn,ImgOut,lignes,colonnes,0,2);
	agrandir(ImgOut,ImgOut2,lignes,colonnes,0,2);

	cout<<"PSNR : "<<psnr(ImgIn,ImgOut2,lignes,colonnes)<<endl;

	ecrire_image_ppm(reduction, ImgOut, lignes, colonnes);
	ecrire_image_ppm(agr, ImgOut2, lignes, colonnes);
	free(ImgIn);
	return 1;
}