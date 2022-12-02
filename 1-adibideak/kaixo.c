/*  KA, Konputagailuen Arkitektura - Informatika Ingeniaritza, 2. maila
    OpenMP laborategia

    kaixo.c	-- OSATZEKO

    Hariak sortu: (1) ingurune-aldagaia; (2) funtzioa; (3) klausula
***********************************************************************/

#include <stdio.h>
#include <omp.h>

#define N 64
#define N2 10


void main ()
{
  int  tid, nth; 	// hariaren identifikadorea eta hari kopurua
  int  i, A[N], B[N], C[N];


  for (i=0; i<N; i++)
  {
    A[i] = -1;
    B[i] = -1;
    C[i] = -1;
  }


  // 1. atal paraleloa: hari kopurua ingurune-aldagaiaren bidez kontrolatzen da
  // export OMP_NUM_THREADS=xx

  #pragma omp parallel private (tid, nth)
  {
    tid = omp_get_thread_num ();
    nth = omp_get_num_threads ();
    printf ("%d (%d) haria exekuzioan\n", tid, nth);

    A[tid] = tid + 10;
    printf ("         %d haria bukatuta\n", tid);
  }

  for (i=0; i<N2; i++) printf ("A(%d) = %d", i, A[i]);
  printf("\n\n >> Lehen atal paraleloaren amaiera\n\n");



  // 2. atal paraleloa: hari kopurua funtzio baten bidez kontrolatzen da
  // omp_set_num_threads


  // "deskomentatu" kode atal hau eta osatu kodea
  // konpilatu, exekutatu eta egiaztatu emaitza

  printf ("\n\n Hari kopurua  --->  ");
  scanf  ("%d", &nth);
omp_set_num_threads(nth);
 
  // gehitu funtzioa hari kopurua ezartzeko


  #pragma omp parallel private (tid, nth)
  {
    tid = omp_get_thread_num ();
    nth = omp_get_num_threads ();
    printf ("%d (%d) haria exekuzioan\n", tid, nth);

    B[tid] = tid + 100;
    printf ("          %d haria bukatuta\n", tid);
  }

  for (i=0; i<N2; i++) printf ("B(%d) = %d", i, B[i]);
  printf ("\n\n >> Bigarren atal paraleloaren amaiera \n\n");



  
  // 3. atal paraleloa: hari kopurua klausula baten bidez kontrolatzen da
  // pragma parallel-ean, num_threads ()

  // "deskomentatu" kode atal hau eta osatu kodea
  // konpilatu, exekutatu eta egiaztatu emaitza
/*
  #pragma omp parallel private (tid, nth)
  {
    tid = omp_get_thread_num ();
    nth = omp_get_num_threads ();
    printf ("%d (%d) haria exekuzioan\n", tid, nth);

    C[tid] = tid + 1000;
    printf ("           %d haria bukatuta\n", tid);
  }

  for (i=0; i<N2; i++) printf ("C(%d) = %d", i, C[i]);
  printf ("\n\n >> Hirugarren atal paraleloaren amaiera \n\n");
*/
}


