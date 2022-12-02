/*  KA, Konputagailuen Arkitektura - Informatika Ingeniaritza, 2. maila
    OpenMP laborategia

    sekzioak.c

    Funtzioak (sekzioak) banatzeko aukerak (banaketa dinamikoa)
    Exekutatu 1, 2, 3 eta 4 harirekin
*************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define NA 34
#define NB 18
#define NC 10
#define ND 20


float fun (int N)
{
  usleep (N*100000);	// ezer ez, bakarrik denbora pasa
  return (N/10.0);
}


void main ()
{
  int    tid = -1, nth;
  int    norA, norB, norC, norD;
  float  A, B, C, D, E;

  struct timespec  t0, t1;
  double  tex;


  clock_gettime (CLOCK_REALTIME, &t0);

  #pragma omp parallel private (tid, nth)
  {
    tid = omp_get_thread_num ();
    nth = omp_get_num_threads ();
    if (tid == 0) printf ("\n >> hari kopurua: %d\n", nth);

    #pragma omp sections
    {
      #pragma omp section
      {
        norA = tid;
        A = fun (NA);
      }
      #pragma omp section
      {
        norB = tid;
        B = fun (NB);
      }
      #pragma omp section
      {
        norC = tid;
        C = fun (NC);
      }
      #pragma omp section
      {
        norD = tid;
        D = fun (ND);
      }
    }
  }

  E = A + B + C + D;

  clock_gettime (CLOCK_REALTIME, &t1);

  printf ("\n A = %.1f  B = %.1f  C = %.1f  D = %.1f ->  E = %.1f", A, B, C, D, E);
  printf ("\n norA %d   norB %d   norC %d   norD %d\n", norA, norB, norC, norD);

  tex = (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / (double)1e9;
  printf ("\n  Tex = %.1f s\n\n", tex);
}

