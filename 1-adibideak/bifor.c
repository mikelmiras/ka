/*  KA, Konputagailuen Arkitektura - Informatika Ingeniaritza, 2. maila
    OpenMP laborategia

    bifor.c	PARALELIZATZEKO

    Bi dimentsioko begizta paralelizatzeko: i edo j
    Ez du ezer egiten: karga sintetiko bat bakarrik
    Aldatu hari kopurua 1etik 32ra, eta aztertu exekuzio-denborak
***********************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <time.h>

#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_thread_num()  0
  #define omp_get_max_threads() 1
#endif


#define N1 8
#define N2 32


int fun (int x)
{
  usleep (5000);	// karga sintetikoa
  return (x*x);
}


void main ()
{
  int     i, j, A[N1][N2], batura;
  double  tex;
  struct timespec  t0, t1;


  for (i=0; i<N1; i++) 
  for (j=0; j<N2; j++) 
    A[i][j] = (i + j) % 13;


  clock_gettime (CLOCK_REALTIME, &t0);

  // paraleloan exekutatzeko begizta
  
  for (i=0; i<N1; i++)
   for (j=0; j<N2; j++)
   {
      batura += fun (A[i][j]); 	//Karga sintetiko bat, soilik paralelismoaren efektua ikusteko
   }


  clock_gettime (CLOCK_REALTIME, &t1);
  tex = (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / (double)1e9;
  printf ("\n batura =  %d \n", batura);
  printf ("\n Tex. (%d hari) = %1.3f ms\n", omp_get_max_threads (), tex*1000);
}

