/*  KA, Konputagailuen Arkitektura - Informatika Ingeniaritza, 2. maila
    OpenMP laborategia

    matbek.c       PARALELIZATZEKO

    C() = A()() x B()
    D() = A()() x C()
    b_esk = C() x D()
    P1 > inprimatu C eta D

    A2()() = A()() x A()()
    A2ren diagonalaren batura
***********************************************************************/

#include <stdio.h>
#include <time.h>

#define NMAX 1000

double  A[NMAX][NMAX], A2[NMAX][NMAX];
double  B[NMAX], C[NMAX], D[NMAX];


int main (int argc, char *argv[])
{
  int     i, j, N, k, tid, nth = 1;
  double  b_esk = 0.0, diagonala = 0.0;

  double  tex;
  struct timespec  t0, t1;


  printf ("\n Bektoreen tamaina (<1000) = ");
  scanf  ("%d", &N);

  // hasiera-balioak (edozein)
  for (i=0; i<N; i++) 
  {
    for (j=0; j<N; j++)  A[i][j] = (double)(N-i) * 0.1 / N;
    B[i] = (double)i * 0.05 / N;
  }

  // eskatu hari kopurua eta ezarri
  // OSATZEKO


  clock_gettime (CLOCK_REALTIME, &t0);

  /**   EXEKUTATU PARALELOAN   **/ 
  /******************************/
#pragma omp parallel
{
  //  C = A x B
  #pragma omp for
  for (i=0; i<N; i++) 
  {
    C[i] = 0.0;
    for (j=0; j<N; j++)  C[i] += A[i][j] * B[j];
  }
	
#pragma omp for
  // D = A x C  eta  b_esk = C x D
  for (i=0; i<N; i++) 
  {
    D[i] = 0.0;
    for (j=0; j<N; j++)  D[i] += A[i][j] * C[j];

    b_esk += C[i] * D[i];
  }

  // 1 hariak C eta D-ren lehen 10 osagaiak inprimatzen ditu
  printf ("\n C0-C9 --> ");
#pragma omp for
  for (j=0; j<9; j++)  printf ("%6.2f", C[j]);
  printf ("\n");

  printf (" D0-D9 --> ");
#pragma omp for
  for (j=0; j<9; j++)  printf ("%6.2f", D[j]);
  printf ("\n");

  // A2 = A x A eta diagonalaren batura
  #pragma omp for
  for (i=0; i<N; i++)
  for (j=0; j<N; j++) 
  {
    A2[i][j] = 0.0;
    for (k=0; k<N; k++)  A2[i][j] += A[i][k] * A[k][j];

    if (i == j) diagonala += A2[i][j];
  }

  // atal paraleloaren bukaera

}
  clock_gettime (CLOCK_REALTIME, &t1);

  printf ("\n b_esk            = %.4f", b_esk);
  printf ("\n A2-ren diagonala = %.4f", diagonala);

  tex = (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / (double)1e9;
  printf ("\n\n  Tex (%d hari) = %1.3f s\n\n", nth, tex);

  return (0);
}
