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

// comment

/* 1 - Bi elementuren arteko distantzia genetikoa kalkulatzeko funtzioa
       (distantzia euklidearra)

       Sarrera:  ALDAKOP aldagaiko bi elementu (erreferentziaz)
       Irteera:  distantzia (double)
******************************************************************************************/

double distantzia_genetikoa (float elem1[], float elem2[])
{
  int i = 0;
int batuketa = 0;
  // EGITEKO
  //   // kalkulatu bi elementuren arteko distantzia (euklidearra)
     
	for (i = 0; i < 40; i++){
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
	double minimoa = 9999;
	for (j = 0; j < taldekop; j ++){
	unekoa = distantzia_genetikoa(&elem[i][0], &zent[j][0]);
	if (unekoa < minimoa){
	minimoa = unekoa;
	taldea = j;
	}
}
sailka[i] = taldea; 
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

double balidazioa (float elem[][ALDAKOP], struct taldeinfo *kideak, float zent[][ALDAKOP], float *talde_trinko)
{

  // EGITEKO
	int n = 0;
	double batuketa = 0;
double batuketa_totala = 0;
  // Kalkulatu taldeen trinkotasuna: kideen arteko distantzien batezbestekoa
  // =======================================================================
  for ( int i = 0; i < taldekop; i++) {
	batuketa_totala = 0;
	for (int j = 0; j < kideak[i].kop; j++){
	batuketa = 0;
		for (int k = 0; k < kideak[i].kop; k++){
		int elem1_ind  = kideak[i].osagaiak[j];
		int elem2_ind = kideak[i].osagaiak[k];
		batuketa = batuketa + distantzia_genetikoa(&elem[elem1_ind][0], &elem[elem2_ind][0]);
		
}
	batuketa_totala = batuketa_totala + (batuketa / kideak[i].kop);
}
	if (kideak[i].kop > 0){
	talde_trinko[i] = batuketa_totala / kideak[i].kop;
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
for (i = 0; i < taldekop; i++){
zentroideen_batuketa = 0;
	for (j = 0; j < taldekop; j++){

	zentroideen_batuketa += distantzia_genetikoa(&zent[i][0], &zent[j][0]);
}
zentroide_trink[i] = zentroideen_batuketa / taldekop;

}
/*
Kalkulatu CVI indizea
 =================
  */


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
