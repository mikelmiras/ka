/*  KA, Konputagailuen Arkitektura - Informatika Ingeniaritza, 2. maila
    OpenMP laborategia

    sinkro.c (SERIE)

    Bektore baten osagaien batezbestekoa; max., min. eta haien posizioak  
    SORTU BERTSIO PARALELOA
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define N 50000
#define BMAX N/10

float  A[N];


void main ()  
{
  int    i, a, b;
  int    minpos, maxpos;
  float  min = BMAX, max = 0.0;
  float  batura = 0.0, bb;


  // Hasierako balioak - ez paralelizatu
  for (i=0; i<N; i++)
    A[i] =  (rand () % BMAX - rand () %  BMAX/4) / 10;

  printf ("\n Hasieran  A[%d] = %1.2f\n", N/2, A[N/2]);


  // paraleloan exekutatzeko kodea
  // =============================

  for (i=0; i<N; i++)
  {
    batura += A[i];
    if (A[i] > max)  { max = A[i]; maxpos = i; }
    if (A[i] < min)  { min = A[i]; minpos = i; }
  }

  if (minpos < maxpos) { a = minpos; b = maxpos; }
  else                 { a = maxpos; b = minpos; }  

  bb = batura / N;

  // aldatu A-ren balioak minimoaren eta maximoaren posizioen artean
  for (i=a; i<b; i++)
    A[i] = A[i] - bb;

  // honaino
  // =======


  printf ("\n Min: %8.1f  pos: %5d", min, minpos);
  printf ("\n Max: %8.1f  pos: %5d", max, maxpos);
  printf ("\n bb:  %8.1f\n", bb);
  printf ("\n Bukaeran  A[%d] = %1.1f\n\n\n", N/2, A[N/2]);
}
