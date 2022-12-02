/*  KA, Konputagailuen Arkitektura - Informatika Ingeniaritza, 2. maila
    OpenMP laborategia

    banaketa.c (SERIE)

    Begizten iterazioak banatzeko estrategiak analizatzeko

    BERTSIO PARALELO ERAGINKORRENA SORTZEKO
    Hariak: 2, 4, 8, 16, 32, 64
    ADI:  konpilatzean, gehitu -lm bukaeran
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#define HANDIA 200
#define N1 1000
#define N2 1000000
#include <omp.h>
int    A[N1], B[N1], C[N1];
float  D[N2];


int kalkulatu (int kop)
{
  usleep (500*kop); // lan-karga simulatzen da: kop mikrosegundo
  return (1);
}


void main ()  
{
  int  i, k = 0, tid = 8;
  int  guztira = 0;
  
  struct timespec  t0, t1;
  double  tex;


  // hasiera-balioak, ez paralelizatu
  for (i=0; i<N1; i++) {
    A[i] = 1;
    if ((rand()%100 < 5) && (i>N1/2) && (i<N1*3/4)) {
      A[i] = HANDIA;
      k++;
    }
  }
  for (i=0; i<N2; i++)  D[i] = 1.0 + rand () % 10;


  // 1. begiztaren exekuzioa
  // =======================

  clock_gettime (CLOCK_REALTIME, &t0);
#pragma omp parallel shared(D)
{
#pragma omp for private(i, tex) 
  for (i=0; i<N2; i++)
    D[i] = (exp (D[i]) - exp (1/D[i])) / sin (D[i]);
}
  clock_gettime (CLOCK_REALTIME, &t1);
  tex = (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / (double)1e9;

  printf ("\n D[100] = %1.3f\n --  Tex_1 (ser.) = %1.3f ms\n", D[100], tex*1000);


  // 2. begiztaren exekuzioa
  // =======================
 
  clock_gettime (CLOCK_REALTIME, &t0);
#pragma omp parallel private (tid)
{
  tid = omp_get_thread_num();
#pragma omp for private(i)
  for (i=0; i<N1; i++) {
    B[i] = kalkulatu (A[i]);
    C[i] = tid; 
  }
}
  clock_gettime (CLOCK_REALTIME, &t1);
  tex = (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / (double)1e9;

  printf ("\n %d iterazio luze\n", k);
  for (i=0; i<N1; i++) if (A[i] == HANDIA) printf (" %d > %2d haria\n", i, C[i]);
  printf ("\n");
  for (i=0; i<N1; i++) guztira += B[i];
  printf (" Guztira = %d\n -- Tex_2 (ser.) = %1.3f ms\n\n", guztira, tex*1000);
}


