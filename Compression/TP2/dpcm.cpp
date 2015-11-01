#ifndef M_PI
   #define M_PI 3.14159265358979323846
#endif


#include "../image_ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "huffman.c"
#include <algorithm> 
#include <stack>


int getMax(int* tab, int taille){
	int max =0;
	for(int i=0;i<taille;i++){
		if(tab[i]>max){
			max = tab[i];
		}
	}
	return max;
}

int getMin(int* tab, int taille){
	int max =255;
	for(int i=0;i<taille;i++){
		if(tab[i]<max){
			max = tab[i];
		}
	}
	return max;
}


void init(int* tab, int taille){
	for(int i=0;i<taille;i++){
		tab[i]=0;
	}
}


void histo(int* tab,int taille){
	int ta = getMax(tab,taille);
	int* t = new int[ta];
	init(t,ta);
	for(int i=0;i<taille;i++){
		//t[tab[i]]++;
		std::cout<<tab[i]<<std::endl;
	}

	/*for(int i=0;i<ta;i++){
		std::cout<<i<<" "<<t[i]<<std::endl;
	}*/
}

/*float A(int a){
	if (a==0){
		return 1/sqrt(2);
	}else{
		return 1;
	}
}

int q(float x){
	bool fin = false;
	float val = x;
	int cpt =1;
	while(!fin){
		val = val/2;
		if(val < 1){
			fin = true;
		}
		cpt++;
	}
	return cpt;
}


void DCT(int* image, float* map,int x, int y,int lignes){
	for(int i=0;i<7;i++){
		for(int j=0;j<7;j++){
			map[x*lignes+y]=(A(x)*A(y)/4)+cos((2*i+1)*x*M_PI/16)*cos((2*j+1)*y*M_PI/16)*image[(x+i)*lignes+(y+j)];
		}
	}
}

void quanti(int* mapInt, float* mapFloat,int lignes){
	for(int i=0;i<lignes;i++){
		for(int j=0;j<lignes;j++){
			mapInt[i*lignes+j]=(int)mapFloat[i*lignes+j]/q(mapFloat[i*lignes+j]);
		}
	}
}*/

int* dpcm(OCTET* in, OCTET* out, int lignes, int colonnes){
	int* tab = new int[lignes*colonnes];
	int cpt =0;
	int moyenne;
	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			if(i==0 || j==0 /*|| i==0 && j ==1*/){
				out[i*lignes+j]=in[i*lignes+j];
			}else{
				//if(j==colonnes-1){
				//moyenne = ((in[i*lignes+(j-1)]+in[(i-1)*lignes+j])/2);
				out[i*lignes+j]=(in[i*lignes+j] - ((in[i*lignes+(j-1)]+in[(i-1)*lignes+j])/2))+128;
				//}else{
				//	tab[cpt++]=(in[i*lignes+j] - ((in[i*lignes+(j-1)] + in[i*lignes+(j+1)])/2))+208;
				//}
			}
		}
	}
	return tab;
}



/*int* dpcm(OCTET* in, int lignes, int colonnes){
	int* tab = new int[lignes*colonnes];
	int diff =0;
	int cpt = 0;
	for(int i = 0; i<lignes;i++){
		for(int j = 0;j<colonnes;j++){
			if(i == 0 && j == 0){
				tab[cpt]=in[i*lignes+j];
			}else{
				tab[cpt]=in[i*lignes+j]-in[i*lignes+(j-1)]+255;
			}
			cpt++;
		}
	}

	return tab;
}*/


char toChar(std::stack<bool> *vec) {
	char c = 0;
	for (int i = 0; i < 8; i++) {
		if(vec->top()) c += pow(2, 7 - i);
		vec->pop();
	}
	// vec->erase(vec->begin(), vec->begin() + 8);
	return c;
}


int main(int argc, char* argv[]){
	char cNomImgLue[250];
	char cNomImgLue2[250]="imageDPCM.pgm";
	int lignes, colonnes, nTaille, S;
	if (argc != 2) {
		printf("Usage: image.pgm\n");
		exit (1) ;
	}
	sscanf (argv[1],"%s",cNomImgLue);

	OCTET *ImgIn, *ImgOut, *ImgOut2,*ImgOut3;
	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &lignes, &colonnes);
	nTaille = lignes * colonnes;
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, lignes * colonnes);

	allocation_tableau(ImgOut, OCTET, nTaille);
	
	int* tab = dpcm(ImgIn,ImgOut, lignes, colonnes);
	int frequencies[UniqueSymbols] = {0};
	for (int i = 0; i < nTaille; i++) {
		frequencies[ImgOut[i]]++;
		//std::cout<<(int)ImgOut[i]<< " ";
	}
	INode* root = BuildTree(frequencies);

	HuffCodeMap codes;
	GenerateCodes(root, HuffCode(), codes);
	delete root;

	std::stack<bool> *vec = new std::stack<bool>();
	for (int i = 0; i < lignes; i++) {
		for (int j = 0; j < colonnes; j++) {
			HuffCode c = codes.find(tab[i*lignes+j])->second;
			std::for_each(c.begin(), c.end(), [=](bool b) {
				vec->push(b);
			});
			if(vec->size() > 8) {
				std::cout << toChar(vec);
			}
		}
	}


	//histo(tab,lignes*colonnes);
	

	//ecrire_image_pgm(cNomImgLue2, ImgOut, lignes, colonnes);*/


}