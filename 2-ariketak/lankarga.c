/*  KA, Konputagailuen Arkitektura - Informatika Ingeniaritza, 2. maila
    OpenMP laborategia

    lankarga.c 	(SERIE)

    Azelerazio-faktoreak neurtu lan-kargaren arabera
    Tamainak: 10, 100, 1000, 10000, 100000 eta 1000000

    Exekutatu serieko bertsioa.
    Gero, paralelizatu begizta eta exekutatu 4 eta 8 harirekin
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>


void main () 
{
  int  i, j, btam;
  int  *A;
  int  x = 0, y = 0;

  struct timespec  t0, t1;
  double  tex;


  printf ("\n Bektorearen tamaina --->  ");
  scanf  ("%d", &btam);
 
  A = malloc (btam * sizeof(int));
  for (i=0; i<btam; i++) A[i] = rand () % 55;

  clock_gettime (CLOCK_REALTIME, &t0);


#pragma parallel for private(x, y) shared (A)
  // paraleloan exekutatzeko begizta (for i)
  for (i=0; i<btam; i++)
    for (j=0; j<1000; j++)
    {
       x = A[i];
       y =  x * x;
       A[i] = ((y+1) * (y+2)) % 20000;
    }

  
  clock_gettime (CLOCK_REALTIME, &t1);
 
  tex = (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / (double)1e9;
  printf ("\n x = %d  -- A[%d] = %d\n", x, btam-1, A[btam-1]);
  printf ("\n Tex. (serie) = %1.3f ms\n\n", tex*1000);
}
