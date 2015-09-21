#include "image_ppm.h"
#include <stdio.h>

using namespace std;


int getIndex(int x, int y, int imgW){
	return y * imgW + x;
}

void reduc(OCTET *in, OCTET *out, int lignes, int colonnes, int color1, int color2) {
	int i, j, k, index, index2;
	for(i = 0; i < lignes; i++){
		for(j = 0; j < colonnes; j++){
			index = getIndex(i * 3, j, lignes*3);
			for(k = 0; k < 3; k++){
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
	}
}




int main(int argc, char* argv[]){
	char cNomImgLue[250];
	char reduction[250] = "reduite.ppm";
	int lignes, colonnes, nTaille, S;
	if (argc != 2) {
		printf("Usage: ImageIn.ppm\n");
		exit (1) ;
	}
	sscanf (argv[1],"%s",cNomImgLue);
	OCTET *ImgIn, *ImgOut;
	lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &lignes, &colonnes);
	nTaille = lignes * colonnes;

	allocation_tableau(ImgIn, OCTET, nTaille*3);
	lire_image_ppm(cNomImgLue, ImgIn, lignes * colonnes);

	allocation_tableau(ImgOut, OCTET, nTaille*3);

	reduc(ImgIn,ImgOut,lignes,colonnes,0,2);

	ecrire_image_ppm(reduction, ImgOut, lignes, colonnes);
	free(ImgIn);
	return 1;
}