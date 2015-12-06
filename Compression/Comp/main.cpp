#ifndef M_PI
#define M_PI 3.14159265358979323846
#define DEF assert
#endif


#include "image_ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "huffman.c"
#include <algorithm>
#include <stack>
#include <fstream>
#include <vector>
#include <assert.h>
#include <string>
#include <cmath>

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

float A(int a){
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

/*void DCT(OCTET* image, float* map,int x, int y,int lignes){
    float res = 0;
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            res += cos((2*(x+i)+1)*(x+i)*M_PI/16)*cos((2*(y+j)+1)*(y+j)*M_PI/16)*image[(x+i)*lignes+(y+j)];
        }
    }
    map[x*lignes+y]=res*((1/sqrt(2))*A(x)*A(y));
}

float* DCTF(OCTET* image,int lignes, int colonnes){
    float* tab = new float[lignes*colonnes*3];
    for(int i=0;i<lignes;i+=8){
        for(int j = 0;j<colonnes;j+=8){
            DCT(image,tab,i,j,lignes);
        }
    }
    return tab;
}

void DCTI(float* dct,int x, int y, int lignes, int colonnes){
    float res =0;
    for(int i = 0; i<7;i++){
        for(int j = 0;j<7;j++){
            res += A(i)*A(j)*dct[(x+i)*lignes+(y+j)]*cos((2*x));
        }
    }
}

void DCTIF(float* dct, OCTET* image, int lignes, int colonnes ){
    for(int i = 0; i<lignes;i+=8){
        for(int j = 0; j<colonnes;j++){
            image[i*lignes+j]=(1/sqrt(16))
        }
    }
}


/*
void quanti(int* mapInt, float* mapFloat,int lignes){
	for(int i=0;i<lignes;i++){
		for(int j=0;j<lignes;j++){
			mapInt[i*lignes+j]=(int)mapFloat[i*lignes+j]/q(mapFloat[i*lignes+j]);
		}
	}
}
*/
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

void writerChar(int in, std::vector<bool> &bits, int size){
    for(int i = 0;i<size;i++){
        bits.push_back(in%2);
        in /= 2;
    }

  /* //assert(in < pow(2, size));
    int cpt =0;
    while(in != 0){
        if(in < pow(2,size)){
            bits.push_back(in%2);
        }
        cpt++;
        in /= 2;

    }*/
}

/*

int* dpcm(OCTET* in, int lignes, int colonnes){
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
}

*/
void decore(OCTET* in, OCTET* out, int lignes){
    for(int i =0; i<lignes;i++){
        for(int j = 0;j<lignes*3;j+=3){
            out[i*lignes+j]= 0.299 * in[i*lignes+j] + 0.587 * in[i*lignes+j+1] + 0.144*in[i*lignes+j+2]; // Y
            out[i*lignes+j]= -0.1687 * in[i*lignes+j] - 0.3313 * in[i*lignes+j+1] + 0.5 * in[i*lignes*j+2]+ 128; // Cr
            out[i*lignes+j]= 0.5* in[i*lignes+j] - 0.4187 * in[i*lignes+j+1] - 0.0813 * in[i*lignes+j+2] + 128; // Cb
        }
    }
}

void corre(OCTET* in, OCTET* out, int lignes){
    for(int i =0; i<lignes;i++){
        for(int j = 0;j<lignes*3;j+=3){
            out[i*lignes+j]= in[i*lignes+j] + 1.402 * (in[i*lignes+j+1]- 128); // R
            out[i*lignes+j]= in[i*lignes+j] - 0.34414 * (in[i*lignes+j+2] - 128); // G
            out[i*lignes+j]= in[i*lignes+j]+1.772*(in[i*lignes+j+2]-128); // B
        }
    }
}


/*char toChar(std::stack<bool> *vec) {
    char c = 0;
    for (int i = 0; i < 8; i++) {
        if(vec->top()) c += pow(2, 7 - i);
        vec->pop();
    }
    // vec->erase(vec->begin(), vec->begin() + 8);
    return c;
}*/


int eqm(OCTET* in, OCTET* out,int lignes){
    int res=0;
    int val;
    for(int i =0; i<lignes;i++){
        for(int j=0;j<lignes;j++){
            val = (out[i*lignes+j]-in[i*lignes+j]);
            res +=(int) pow(val,2);
        }
    }
    std::cout<<"nb pixels :"<<lignes*lignes<<" "<<res<<" "<<res / (lignes*lignes)<<std::endl;
    return res / (lignes*lignes);
}

int psnr(OCTET* in, OCTET* out, int lignes){
    int e = eqm(in,out,lignes);
    std::cout<<e<<std::endl;
    int temp = 255/e;
    int log =log10(temp);
    std::cout<<log<<" "<<10*log<<std::endl;
    return  10 *log;
}

OCTET* getRed(OCTET* in, int lignes){
    OCTET* out;
    allocation_tableau(out, OCTET, pow(lignes,2));
    int cpt =0;
    for(int i =0;i<lignes;i++){
        for(int j = 0;j<lignes;j+=3){
            out[cpt] = in[i*lignes+j];
            cpt++;
        }

    }
    return out;
}

OCTET* getGreen(OCTET* in, int lignes){
    OCTET* out;
    allocation_tableau(out, OCTET, pow(lignes,2));
    int cpt=0;
    for(int i =0;i<lignes;i++){
        for(int j = 0;j<lignes;j+=3){
            out[cpt] = in[i*lignes+j+1];
            cpt++;
        }

    }
    return out;
}

OCTET* getBlue(OCTET* in, int lignes){
    OCTET* out;
    allocation_tableau(out, OCTET, pow(lignes,2));
    int cpt=0;
    for(int i =0;i<lignes;i++){
        for(int j = 0;j<lignes;j+=3){
            out[cpt] = in[i*lignes+j+3];
            cpt++;
        }

    }
    return out;
}




char toChar(std::vector<bool> bits, int pos){
    char c = 0;
    for(int i = pos;i<pos+8;i++){
        if(i<bits.size()){
            if(bits.at(i)) {
                c += pow(2, (i - pos));
            }
        }

    }
    return c;
}




int getSize(int nbColor){
    int i =1;
    int cpt = 0;
    while(true){

        if(i>= nbColor){
            std::cout<<"size : "<<cpt<<std::endl;
            return cpt;
        }
        i = i*2;
        cpt++;
    }
}

std::vector<int> repartit(int taux){
    std::vector<int> repartition;
    int val=0;
    int cpt = 0;

    for(int i =0;i<256;i++){
        if(cpt%taux == 0){
            val++;
        }
        repartition.push_back(val);
        cpt++;
    }
    std::cout<<repartition.at(repartition.size()-1)<<std::endl;
    return repartition;
}

std::vector<int> repartitInv(int taux){
    std::vector<int> repartition;
    for(int i =0;i<256/taux;i++){
           repartition.push_back(i*taux);
    }
    std::cout<<repartition.at(repartition.size()-1)<<std::endl;
    return repartition;


}

std::vector<bool> comp(OCTET* image, /*OCTET* out,*/int lignes, int colonnes, int taux){
    std::vector<bool> bits;
    std::vector<int>rep = repartit(taux);
    int size =  getSize(256/taux);
    for(int i = 0; i < lignes; i++){
        for(int j = 0; j <colonnes; j++){
           // for(int k = 0; k<2;k++){

                //out[i*lignes+j/*+k*/]=image[i*lignes+j/*+k*/]/taux;
                writerChar(rep.at((image[i*lignes+j])),bits,size);
            //}
        }
    }
    std::cout<<"nb bits comp :"<<bits.size()<<" "<<lignes*colonnes<<std::endl;
    return bits;
}

std::vector<bool> compCoul(OCTET* image, int lignes, int colonnes, int taux){

    OCTET* rouge = getRed(image, lignes);
    OCTET* vert = getGreen(image, lignes);
    OCTET* blue = getBlue(image, lignes);

    std::vector<bool> full;
    std::vector<bool> bitsR;
    bitsR = comp(rouge,lignes,lignes,taux);
    std::vector<bool> bitsG;
    bitsG = comp(vert,lignes,lignes,taux);
    std::vector<bool> bitsB;
    bitsG = comp(blue,lignes,lignes,taux);
    full = bitsR;
    for(int i =0;i<bitsG.size();i++){
        full.push_back(bitsG.at(i));
    }

    for(int i = 0;i<bitsB.size();i++){
        full.push_back(bitsB.at(i));
    }



    std::cout<<"nb bits comp :"<<full.size()<<" "<<lignes*colonnes<<std::endl;
    return full;
}

void decomp(int* image, OCTET* out, int lignes, int colonnes,int taux){
    for(int i=0;i<lignes; i++){
        for(int j = 0;j<colonnes;j++){
            //for(int k=0;k<2;k++){
                out[i*lignes+j/*+k*/]=image[i*lignes+j/*+k*/]*taux;
            //}
        }
    }
}

bool getiemebit(char c, int i)
{
    return ((c>>i) & 1);
}

std::vector<bool> toBool(std::vector<char> vals){
    std::vector<bool> bits;
    for(int i =0;i<vals.size();i++){
        for(int j = 0; j<8;j++){
            bits.push_back(getiemebit(vals.at(i),(7-j)));
        }
    }
    return bits;
}



void readADecomp(char* fileName, OCTET* ImgOut, int lignes){

    std::ifstream file;
    file.open(fileName, std::ios_base::binary | std::ios_base::in);
    std::vector<int> repartit;

    std::string c;
    getline(file,c);
    int taux = (int)c.at(0);
    int size = getSize(256/taux);

    repartit = repartitInv(taux);
    std::vector<char> temp;
    char cara;
    while(file.get(cara)){
        temp.push_back(cara);
    }
    /*while(getline(file,c)){
    for(int i = 0; i<c.size();i++){
        temp.push_back(c.at(i));
    }}*/

  //  char o = 0;
    int cpt=0;
    std::vector<bool> bits = toBool(temp);
    std::cout<<"nb bits decomp : "<<bits.size()<<" "<<lignes*lignes<<" "<<588320/262144<<std::endl;
    for(int i = 0;i<lignes;i++){
        for(int j=0;j<lignes;j++){
           char o = 0;
            //std::cout<<cpt<<std::endl;
            for(int k=0;k<size;k++){
                if(cpt<bits.size()){
                    if(bits.at(cpt)) {
                        o += pow(2, k);
                    }
                }

               // std::cout<<bits.at(cpt)<< ":"<<getiemebit(o,k)<<" ";
                //std::cout<<"la2"<<std::endl;
               cpt++;
            }
           // std::cout<<std::endl;
            //std::cout<<"la1 "<<(int)o<<std::endl;
            ImgOut[i*lignes+j] =(OCTET)repartit.at(o);
           // std::cout<<"la1 "<< (int)ImgOut[i*lignes+j]<<std::endl;
        }
    }
    file.close();

}

void readADecompCoul(char* fileName,OCTET* ImgOut,int lignes){
    std::ifstream file;
    file.open(fileName, std::ios_base::binary | std::ios_base::in);
    std::vector<int> repartit;

    std::string c;
    getline(file,c);
    int taux = (int)c.at(0);
    int size = getSize(256/taux);

    repartit = repartitInv(taux);
    std::vector<char> temp;
    char cara;
    while(file.get(cara)){
        temp.push_back(cara);
    }
    /*while(getline(file,c)){
    for(int i = 0; i<c.size();i++){
        temp.push_back(c.at(i));
    }}*/

    //  char o = 0;
    int cpt=0;
    std::vector<bool> bits = toBool(temp);
    std::cout<<"nb bits decomp : "<<bits.size()<<std::endl;
    for(int i = 0;i<lignes;i++){
        for(int j=0;j<lignes*3;j+=3){
            char oR = 0;
            char oG = 0;
            char oB = 0;
            //std::cout<<cpt<<std::endl;
            for(int k=0;k<size;k++){
                if(cpt<bits.size()){
                    if(bits.at(cpt)) {
                        oR += pow(2, k);
                    }
                    if(bits.at(2*cpt)){
                        oG += pow(2,k);
                    }
                    if(bits.at(3*cpt)){
                        oB += pow(2,k);
                    }
                }

                // std::cout<<bits.at(cpt)<< ":"<<getiemebit(o,k)<<" ";
                //std::cout<<"la2"<<std::endl;
                cpt++;
            }
            // std::cout<<std::endl;
            //std::cout<<"la1 "<<(int)o<<std::endl;
            ImgOut[i*lignes+j] = (OCTET)repartit.at(oR);
            ImgOut[i*lignes+j+1] = (OCTET)repartit.at(oG);
            ImgOut[i*lignes+j+2] = (OCTET)repartit.at(oB);
            // std::cout<<"la1 "<< (int)ImgOut[i*lignes+j]<<std::endl;
        }
    }
    file.close();
}




int main(int argc, char* argv[]){
    char cNomImgLue[250]="C:\\Travail\\M2\\Master2\\Compression\\Comp\\14_Medical.pgm";
    char cNomImgLue2[250]="C:/Travail/M2/Master2/Compression/Comp/imageComp.pgm";
    int lignes, colonnes, nTaille, S;
   /* if (argc != 2) {
        printf("Usage: image.pgm\n");
        exit (1) ;
    }
    sscanf (argv[1],"%s",cNomImgLue);*/

    bool pgm = true; // vrai si l'image est noir et blanc
    OCTET *ImgIn, *ImgOut, *ImgOut2,*ImgOut3;
    if(pgm){
        lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &lignes, &colonnes);
        nTaille = lignes * colonnes;
        allocation_tableau(ImgIn, OCTET, nTaille);
        lire_image_pgm(cNomImgLue, ImgIn, lignes * colonnes);
        allocation_tableau(ImgOut, OCTET, nTaille);
    }else{
        lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &lignes, &colonnes);
        nTaille = lignes * colonnes * 3;
        allocation_tableau(ImgIn, OCTET, nTaille);
        lire_image_ppm(cNomImgLue, ImgIn, lignes * colonnes);
        std::cout<<"la"<<std::endl;
        allocation_tableau(ImgOut, OCTET, nTaille);
    }






    std::cout<<"debut compression"<<std::endl;
    std::ofstream fichier;
    fichier.open("C:/Travail/M2/Master2/Compression/Comp/res.bin",std::ios::out | std::ios_base::binary);
    std::vector<bool> vals;
    int taux =2;
    if(pgm){
        vals  = comp(ImgIn,lignes,colonnes,taux );
    }else{
        vals = comp(ImgIn,lignes,colonnes,taux );
    }

    std::cout<<"fin compression"<<std::endl;
    char size = (char)getSize(256/taux);
    std::cout<<"ecriture fichier"<<std::endl;
    fichier<<(char)taux<<"\n";
    //std::cout<<(int)sizeof(size)<<std::endl;
    for(int i = 0; i<vals.size();i+=8){
        //std::cout<<vals.at(i);
        fichier<<toChar(vals,i);
    }
    //corre(ImgIn,ImgOut,lignes);
    //ecrit(ImgOut,lignes,2,fichier);
    //decomp(ima,ImgOut,lignes,colonnes,2);


   // int* tab = dpcm(ImgIn,ImgOut, lignes, colonnes);
    /*int frequencies[UniqueSymbols] = {0};
    for (int i = 0; i < nTaille; i++) {
        frequencies[ImgOut[i]]++;
        //std::cout<<(int)ImgOut[i]<< " ";
    }*/


    /* /!\ HUFFMAN /!\ */
  /*  INode* root = BuildTree(frequencies);
    //float* dct = DCTF(ImgIn,lignes,colonnes);
    HuffCodeMap codes;
    GenerateCodes(root, HuffCode(), codes);
    delete root;
    //fichier.open("C:/Travail/M2/Master2/Compression/Comp/res.bin",std::ios::out);
    std::stack<bool> *vec = new std::stack<bool>();
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            HuffCode c = codes.find(tab[i*lignes+j])->second;
            std::for_each(c.begin(), c.end(), [=](bool b) {
                vec->push(b);
            });
            if(vec->size() > 8) {
                fichier << toChar(vec);
                //std::cout << toChar(vec);
            }
        }
    }*/
    fichier.close();
    std::cout<<"fichier compressé : " << fichier.width()<<std::endl;

    std::cout<<"debut décompression"<<std::endl;
    if(pgm){
        readADecomp("C:/Travail/M2/Master2/Compression/Comp/res.bin",ImgOut, lignes);
    }else{
        readADecompCoul("C:/Travail/M2/Master2/Compression/Comp/res.bin",ImgOut, lignes);
    }

    //histo(tab,lignes*colonnes);
    std::cout << "fin decompresion"<<std::endl;

    std::cout<<psnr(ImgIn,ImgOut,lignes)<<std::endl;


    ecrire_image_pgm(cNomImgLue2, ImgOut, lignes, colonnes);



}