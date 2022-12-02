

/*  KA, Konputagailuen Arkitektura - Informatika Ingeniaritza, 2. maila
    OpenMP laborategia

    aldagaiak.c 	-- OSATZEKO

    aldagaiak erazagutu
    gero, exekutatu 1, 3 eta 5 harirekin
***********************************************************************/

#include <stdio.h>
#include <omp.h>

#define N 8


void main ()
{
  int  tid, nth;
  int  A[N][N], B[N], i, j, hasi, buka;
  int  x = -1, z = 0, Amax = -1;


  for (i=0; i<N; i++)
  {
    B[i] = 0;
    for (j=0; j<N; j++)  A[i][j] = i+j;
  }


  #pragma omp parallel default (none) private(x, hasi, buka, tid, i, j, z, Amax) shared(A, B, nth)
  {
    tid  = omp_get_thread_num ();
    nth  = omp_get_num_threads ();

    hasi = tid * N / nth;
    buka = (tid+1) * N / nth;

    printf ("\n %d haria (harikop %d) -- hasi %d, buka %d", tid, nth, hasi, buka);

    for (i=hasi; i<buka; i++)
     for (j=0; j<N; j++)
     {
       x = A[i][j] * A[i][j];
       A[i][j] = x - 1;
       if (Amax < A[i][j])  Amax = A[i][j];

       B[i] = B[i] + A[i][j];
       z = z + x; 
     }
  }


  printf ("\n\n -> A matrizearen 3 errenkada \n");
  for (j=0; j<N; j++) printf ("%5d", A[3][j]);

  printf ("\n\n -> B bektorea \n");
  for (i=0; i<N; i++) printf ("%5d", B[i]);

  printf ("\n\n -> x %d, Amax %d, z %d\n\n", x, Amax, z);
}



