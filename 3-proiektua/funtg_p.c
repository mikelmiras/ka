/*  KA, Konputagailuen Arkitektura - Informatika Ingeniaritza, 2. maila
    OpenMP laborategia - PROIEKTUA

    funtg_s.c
    taldegen_s.c programan erabiltzen diren errutinak

    OSATZEKO
******************************************************************************************/

#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <stdio.h>
#include "definetg.h"		// konstante eta datu-egituren definizioak
#include <omp.h>
// comment

/* 1 - Bi elementuren arteko distantzia genetikoa kalkulatzeko funtzioa
       (distantzia euklidearra)

       Sarrera:  ALDAKOP aldagaiko bi elementu (erreferentziaz)
       Irteera:  distantzia (double)
******************************************************************************************/

double distantzia_genetikoa (float elem1[], float elem2[])
{
  int i = 0;
double batuketa = 0;
  // EGITEKO
  //   // kalkulatu bi elementuren arteko distantzia (euklidearra)
     
	for (i = 0; i < ALDAKOP; i++){
	batuketa += (elem1[i]-elem2[i])*(elem1[i]-elem2[i]);
}
return sqrt(batuketa);
}




/* 2 - Talde gertuena kalkulatzeko funtzioa (zentroide gertuena)

       Sarrera:  elekop   elementu kopurua, int
                 elem     EMAX x ALDAKOP tamainako matrizea
                 zent     taldekop x ALDAKOP tamainako matrizea
       Irteera:  sailka   EMAX tamainako bektorea, elementu bakoitzari dagokion taldea
******************************************************************************************/

void talde_gertuena (int elekop, float elem[][ALDAKOP], float zent[][ALDAKOP], int *sailka)
{
  // EGITEKO
  //  sailka: elementu bakoitzaren zentroide hurbilena, haren "taldea"
  int i =0;
  int j =0;
  double unekoa = 0; 
double dist = 0;
double posizioa = 0;
double taldea = 0;
  // EGITEKO
  //  sailka: elementu bakoitzaren zentroide hurbilena, haren "taldea" 
  for (i = 0; i < elekop; i++){
       #pragma omp parallel private(taldea, i, unekoa) shared(minimoa) {
	double minimoa = 9999;
        #pragma omp parallel for private(j, unekoa)
	for (j = 0; j < taldekop; j ++){
	unekoa = distantzia_genetikoa(&elem[i][0], &zent[j][0]);
	 #pragma omp critical
	if (unekoa < minimoa){
	minimoa = unekoa;
	taldea = j;
	}
	}
}
sailka[i] = taldea; 
}
 }
}
/* 3 - Egindako sailkapenaren balidazioa: taldeen trinkotasuna eta zentroideen trinkotasuna
       CVI indizea kalkulatzen da

       Sarrera:  elem     fitxategiko elementuak (EMAX x ALDAKOP tamainako matrizea)
                 kideak   taldekideen zerrenda (taldekop tamainako struct-bektore bat: elem eta kop)
                 zent     taldeen zentroideak (taldekop x ALDAKOP)
       Irteera:  cvi indizea
                 talde_trinko taldeen trinkotasuna
******************************************************************************************/
#pragma omp parallel schedule(runtime)
double balidazioa (float elem[][ALDAKOP], struct taldeinfo *kideak, float zent[][ALDAKOP], float *talde_trinko)
{

  // EGITEKO
	int n = 0;
	double batuketa = 0;
float batuketa_totala = 0.0f;
float kop;
  // Kalkulatu taldeen trinkotasuna: kideen arteko distantzien batezbestekoa
  // =======================================================================
  #pragma omp parallel for private(kop, batuketa) shared(batuketa_totala) reduction(+:batuketa_totala) nowait
  for ( int i = 0; i < taldekop; i++) {
	batuketa_totala = 0;
	kop = kideak[i].kop;
	if (kideak[i].kop > 1){
	for (int j = 0; j < kideak[i].kop; j++){
	batuketa = 0;
		for (int k = 0; k < kideak[i].kop; k++){
		int elem1_ind  = kideak[i].osagaiak[j];
		int elem2_ind = kideak[i].osagaiak[k];
		batuketa = batuketa + distantzia_genetikoa(&elem[elem1_ind][0], &elem[elem2_ind][0]);
		
}
	batuketa_totala = batuketa_totala + (batuketa / kop);
}
	
	talde_trinko[i] = batuketa_totala / kop;
}else{
	talde_trinko[i] = 0;
}
}  

// Kalkulatu zentroideen trinkotasuna: zentroideen arteko distantzien batezbestekoa
  // ================================================================================
int i = 0;
double zentroide_trink [taldekop];
int j = 0;
float zentroideen_batuketa = 0;
#pragma omp parallel for reduction(+:zentroideen_batuketa)
for (i = 0; i < taldekop; i++){
zentroideen_batuketa = 0;

	for (j = 0; j < taldekop; j++){

	zentroideen_batuketa += distantzia_genetikoa(&zent[i][0], &zent[j][0]);

}
zentroide_trink[i] = zentroideen_batuketa / (taldekop-1);

}
/*
Kalkulatu CVI indizea
 =================
  */
double cvi = 0;
double batuketa_cvi = 0;
double max = 0;
#pragma omp parallel for reduction(+:batuketa_cvi) shared(max)
for (int i = 0; i < taldekop; i++){

if (talde_trinko[i] > zentroide_trink[i]){
max = talde_trinko[i];
}else
{
max = zentroide_trink[i];
}
batuketa_cvi += (zentroide_trink[i] - talde_trinko[i])/ max;

}

double zatiketa = (float) 1 / (float) taldekop;
 
cvi = zatiketa * batuketa_cvi;
return cvi;
}

/* 4 - Eritasunak analizatzeko funtzioa 

       Sarrera:  kideak  taldekideen zerrenda (taldekop tamainako struct-bektore bat: elem eta kop)
                 eri     eritasunei buruzko informazioa (EMAX x ERIMOTA)
       Irteera:  eripro  eritasunen analisia: medianen maximoa/minimoa, eta taldeak
******************************************************************************************/

void eritasunen_analisia (struct taldeinfo *kideak, float eri[][ERIMOTA], struct analisia *eripro)
{

  // EGITEKO
  // Prozesatu eritasunei buruzko informazioa talde bakoitzean,
  // medianen maximoa/minimoa eta taldea lortzeko
	float eritasun_probabilitatea[EMAX];
	double minimoa = 999;
	double maximoa = 0;
	int ind_1;
	int med = 0;
	float aurreko;
	int maximo_totala = 0;
	for (int i = 0; i<ERIMOTA; i++){
	for (int j = 0; j < taldekop; j ++){
		for (int k = 0; k < kideak[j].kop; k++){
			ind_1 = kideak[j].osagaiak[k];
			eritasun_probabilitatea[k] = eri[ind_1][i];
		}
		if (kideak[j].kop > 1){
			for (int l = 0; l < kideak[j].kop - 1; l++){
				for (int m = l + 1; m < kideak[j].kop; m++){
					if (eritasun_probabilitatea[l]>eritasun_probabilitatea[m]){
					aurreko = eritasun_probabilitatea[l];
					eritasun_probabilitatea[l] = eritasun_probabilitatea[m];
					eritasun_probabilitatea[m] = aurreko;					
					}
				}
				
			}
			
			
		}
	
	
	if (kideak[j].kop > 0){
	med = kideak[j].kop / 2;
	if (maximoa < eritasun_probabilitatea[med]){
		maximoa = eritasun_probabilitatea[med];
		maximo_totala = j;
	}
	
}
}
}


}

// PROGRAMA NAGUSIKO BESTE BI FUNTZIO
// ==================================


/* 5 - Zentroideen hasierako balioak
**************************************************************/

void hasierako_zentroideak (float zent[][ALDAKOP])
{
  int  i, j; 


  srand (147);

  for (i=0; i<taldekop; i++)
  for (j=0; j<ALDAKOP/2; j++)
  {
    zent[i][j] = (rand() % 10000) / 100.0;
    zent[i][j+ALDAKOP/2] = zent[i][j];
  }
}


/* 6 - Zentroide berriak; erabaki bukatu behar den edo ez
**************************************************************/

int zentroide_berriak (float elem[][ALDAKOP], float zent[][ALDAKOP], int *sailka, int elekop)
{
  int     i, j, bukatu;
  float   zentberri[taldekop][ALDAKOP];
  double  diszent;
  double  baturak[taldekop][ALDAKOP+1];


  // zentroide berriak: kideen dimentsio bakoitzeko aldagaien batezbestekoak

  // baturak: taldekideen aldagaien balioak akumulatzeko; azkena kopurua da.
  
  for (i=0; i<taldekop; i++)
  for (j=0; j<ALDAKOP+1; j++)
    baturak[i][j] = 0.0;

  for (i=0; i<elekop; i++)
  {
    for (j=0; j<ALDAKOP; j++)
      baturak[sailka[i]][j] += elem[i][j];

    baturak[sailka[i]][ALDAKOP] ++;	      // azken osagaia (ALDAKOP) kopuruak gordetzeko
  }


  // kalkulatu taldeetako zentroide berriak, eta erabaki bukatu behar den (DELTA1)
  
  bukatu = 1;
  for (i=0; i<taldekop; i++)
  {
    if (baturak[i][ALDAKOP] > 0)              // taldea ez dago hutsik
    {
      for (j=0; j<ALDAKOP; j++)
        zentberri[i][j] = baturak[i][j] / baturak[i][ALDAKOP];

      // erabaki bukatu behar den
      diszent = distantzia_genetikoa (&zentberri[i][0], &zent[i][0]);
      if (diszent > DELTA1)  bukatu = 0;      // dimentsio batean aldaketa dago; segi simulazioarekin
 
      // kopiatu zentroide berriak
      for (j=0; j<ALDAKOP; j++)
        zent[i][j] = zentberri[i][j];
    }
  }

  return (bukatu);
}

double max (double a, double b){
if (a > b) {
return a;
}else{
return b;
}


}
