/*  KA, Konputagailuen Arkitektura - Informatika Ingeniaritza, 2. maila
    OpenMP laborategia

    indarra.c	Serieko bertsioa

    SORTU BERTSIO PARALELOA

    fpart.dat: partikulak dituen fitxategia
    findar.dat:  exekuzioaren emaitza

    exekutatzeko: indarra fpart.dat findar.dat #part_kop
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_thread_num()  0
  #define omp_get_max_threads() 1
#endif




void kalkulatu_indarrak (int *partikulak, double *indarra, int pkop) 
{
#pragma omp parallel
{
  int  i, j;

#pragma omp for 
  for (i=0; i<pkop; i++)
  for (j=0; j<pkop; j++)
    if (i != j) indarra[i] += partikulak[i] * partikulak[j] / pow ((i-j), 2);
}
}

void main (int argc, char *argv[])
{
  int     i, pkop, *partikulak;
  double  *indarra;
  FILE    *fpart, *findar;

  double  tex;
  struct timespec t0, t1, t2, t3;


  if (argc != 4) {
    printf ("\n  ADI: indarra fpart.dat findar.dat #part_kop\n\n");
    exit (-1);
  }

  // memoria esleitu partikulak eta indarra bektoreei
  pkop        = atoi (argv[3]);
  partikulak  = malloc (pkop * sizeof (int));
  indarra     = calloc (pkop, sizeof (double));  // 0z hasieratuta

 
  // neurtu programaren atal bakoitzaren exekuzio-denbora eta denbora osoa
  
  clock_gettime (CLOCK_REALTIME, &t0);

  // 1 - irakurri partikulen datuak sarrera-fitxategitik 
  // EZIN DA PARALELOAN EGIN
  // ===================================================
   
  fpart = fopen (argv[1], "r");
  if (fpart == NULL) {
    printf ("Errorea %s fitxategia irekitzean\n", argv[1]);
    fclose (fpart);
    exit (-1);
  }
  
  for (i=0; i<pkop; i++)
    fscanf (fpart, "%d", &partikulak[i]);
  fclose (fpart);

  clock_gettime (CLOCK_REALTIME, &t1);


  // 2 - kalkulatu indarrak 
  // PARALELOAN EXEKUTATZEKO
  // ===================================================

  kalkulatu_indarrak (partikulak, indarra, pkop);

  clock_gettime (CLOCK_REALTIME, &t2);


  // 3 - idatzi emaitzak irteera-fitxategian
  // EZIN DA PARALELOAN EGIN
  // ===================================================

  findar = fopen (argv[2], "w");
  if (findar == NULL) {
    printf ("Errorea %s fitxategia irekitzean\n", argv[1]);
    fclose (findar);
    exit (-1);
  }

  for (i=0; i<pkop; i++)
    fprintf (findar, "%1.4f \n", indarra[i]);
  fclose (findar);

  clock_gettime (CLOCK_REALTIME, &t3);

  printf ("\n  Exekuzio-denborak, %d hari", omp_get_max_threads ());
  printf ("\n  ==========================\n\n");
  tex = (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / (double)1e9;
  printf ("   T irakurri: %8.3f ms\n", tex*1000);
  tex = (t2.tv_sec - t1.tv_sec) + (t2.tv_nsec - t1.tv_nsec) / (double)1e9;
  printf ("   T indarra:  %8.3f ms\n", tex*1000);
  tex = (t3.tv_sec - t2.tv_sec) + (t3.tv_nsec - t2.tv_nsec) / (double)1e9;
  printf ("   T idatzi:   %8.3f ms\n", tex*1000);
  tex = (t3.tv_sec - t0.tv_sec) + (t3.tv_nsec - t0.tv_nsec) / (double)1e9;
  printf ("   ----------------------\n");
  printf ("   T osoa:     %8.3f ms\n\n", tex*1000);

  printf ("   indarra[0] = %1.4f  indarra[%d] = %1.4f  indarra[%d] = %1.4f\n\n", indarra[0], pkop/2, indarra[pkop/2], pkop-1, indarra[pkop-1]);
}

