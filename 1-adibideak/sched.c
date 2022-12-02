/*  KA, Konputagailuen Arkitektura - Informatika Ingeniaritza, 2. maila
    OpenMP laborategia

    sched.c

    Begizta-iterazioak banatzeko aukerak ikusteko adibidea
    Banaketa modua ingurune-aldagai baten bidez (runtime)
    Adibidez:    export OMP_SCHEDULE="static,4"
***********************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <omp.h>

#define N 40


void main ()
{
  int  tid;
  int  i, A[N];


  for (i=0; i<N; i++) A[i] = -1;

  #pragma omp parallel for private (tid) schedule (runtime)
  for (i=0; i<N; i++)
  {
    tid = omp_get_thread_num ();

    A[i] = tid;
    usleep (2);
  }

  printf ("\n\n Begizta baten 40 iterazioen banaketa harien artean, schedule motaren arabera\n");

  printf ("\n iterazioa:  ");
  for (i=0; i<N/2; i++)  printf ("%3d", i);
  printf ("\n haria (tid):");
  for (i=0; i<N/2; i++)  printf ("%3d", A[i]);

  printf ("\n\n\n iterazioa:  ");
  for (i=N/2; i<N; i++)  printf ("%3d", i);
  printf ("\n haria (tid):");
  for (i=N/2; i<N; i++)  printf ("%3d", A[i]);
  printf ("\n\n");
}

