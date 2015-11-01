#include "../image_ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <stack>
#include "huffman.c"

void toNdg(OCTET* in,OCTET* out, int lignes, int colonnes){
	int cpt =0;
	for(int i=0; i<lignes*3;i+=3){
		for(int j=0;j<colonnes*3;j+=3){
			out[cpt++] = (int)(in[i*lignes+j]*0.29+in[i*lignes+j+1]*0.59+in[i*lignes+j+2]*0.12);
		}
	}
}

void init(int* tab, int size){
	for(int i=0;i<size;i++){
		tab[i]=0;
	}
}

int* histo(OCTET* in, int lignes, int colonnes){
	int* histo = new int[256];
	init(histo,256);
	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			histo[in[i*lignes+j]]++;
		}
	}
	return histo;
}

void afficheTab(int* tab, int size){
	for(int i=0;i<size;i++){
		std::cout<<i<<" "<<tab[i]<<";";
	}
	std::cout<<std::endl;
}

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
	char cNomImgLue2[250]="image.pgm";


	int lignes, colonnes, nTaille, S;
	if (argc != 2) {
		printf("Usage: image.ppm\n");
		exit (1) ;
	}
	sscanf (argv[1],"%s",cNomImgLue);

	OCTET *ImgIn, *ImgOut, *ImgOut2,*ImgOut3;
	lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &lignes, &colonnes);
	nTaille = lignes * colonnes;
	allocation_tableau(ImgIn, OCTET, nTaille*3);
	lire_image_ppm(cNomImgLue, ImgIn, lignes * colonnes);
	allocation_tableau(ImgOut, OCTET, nTaille);

	toNdg(ImgIn,ImgOut, lignes, colonnes);
	int* histogramme;
	histogramme = histo(ImgOut,lignes,colonnes);
	//afficheTab(histogramme,256);

	int frequencies[UniqueSymbols] = {0};

	for (int i = 0; i < lignes; i++) {
		for (int j = 0; j < colonnes; j++) {
			frequencies[ImgOut[i*lignes+j]]++;
		}
	}
	INode* root = BuildTree(frequencies);

	HuffCodeMap codes;
	GenerateCodes(root, HuffCode(), codes);
	delete root;

	std::stack<bool> *vec = new std::stack<bool>();
	for (int i = 0; i < lignes; i++) {
		for (int j = 0; j < colonnes; j++) {
			HuffCode c = codes.find(ImgOut[i*lignes+j])->second;
			std::for_each(c.begin(), c.end(), [=](bool b) {
				vec->push(b);
			});
			if(vec->size() > 8) {
				std::cout << toChar(vec);
			}
		}
	}

	ecrire_image_pgm(cNomImgLue2, ImgOut, lignes, colonnes);


}