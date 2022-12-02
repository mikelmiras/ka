/*  KA, Konputagailuen Arkitektura - Informatika Ingeniaritza, 2. maila
    OpenMP laborategia

    harikop.c (SERIE)

    Azelerazio-faktoreak neurtu hari kopuruaren arabera 
    PARALELIZATZEKO 
    Hariak: 2, 4, 8, 16, 32, 64
***********************************************************************/

#include <stdio.h>
#include <time.h>

#define N 800
#define ITERAZIO 5

int  A[N][N], B[N][N], C[N][N];


void Exe_Denbora (char *Testu, struct timespec *t0, struct timespec *t1)
{
  double  tex;

  tex = (t1->tv_sec - t0->tv_sec) + (t1->tv_nsec - t0->tv_nsec) / (double)1e9;
  printf ("%s = %10.3f ms\n", Testu, tex*1000);
}


// PROGRAMA NAGUSIA
void main ()  
{
  int  i, j, k, itera_kop, diag_bat = 0;;
int tid, nth;
  struct timespec  t0, t1;


  printf ("\n  serie - %d errepikapen\n", ITERAZIO);

  for (itera_kop=0; itera_kop<ITERAZIO; itera_kop++)
  {
    // hasiera-balioak
    for (i=0; i<N; i++)
    for (j=0; j<N; j++)
    {
      A[i][j] = (i % 5) - 2;
      B[i][j] = (j % 7) - 4;
    }

    clock_gettime (CLOCK_REALTIME, &t0);

    // paraleloan exekutatzeko begizta
    #pragma omp parallel private(i, j, tid)
{
#pragma omp for
    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
      {
        C[i][j] = 0;
        for (k=0; k<N; k++)
          C[i][j] += A[i][k] * B[k][j];
      }  
}
    clock_gettime (CLOCK_REALTIME, &t1);
    Exe_Denbora ("Tex: ", &t0, &t1);


  for (i=0; i<N; i++) diag_bat += C[i][i];
  printf ("\n diag_bat = %d\n", diag_bat);
}

