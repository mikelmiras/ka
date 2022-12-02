/*  KA, Konputagailuen Arkitektura - Informatika Ingeniaritza, 2. maila
    OpenMP laborategia - PROIEKTUA

    definetg.h
    taldegen eta funtg fitxategietan erabiltzen diren konstanteak eta datu-egiturak
**********************************************************************************/


// konstanteak

#define EMAX        230000	// osagai kopuru (elem) maximoa
#define TALDEKOPMAX 100		// talde kopurua - 10-en multiploa
#define ALDAKOP     40		// elementu bakoitzaren aldagai kopurua
#define DELTA1      0.01	// konbergentzia: zentroideen aldaketa minimoa
#define DELTA2      0.01	// konbergentzia: sailkapena (cvi)
#define ITMAX       1000	// konbergentzia: iterazio kopuru maximoa
#define ERIMOTA     18


extern int  taldekop;

// datu-egiturak

struct taldeinfo 		// taldeei buruzko informazioa
{
  int  osagaiak[EMAX]; 		// osagaiak
  int  kop;       		// osagai kopurua
};


struct analisia   		// eritasunen analisiaren emaitzak
{
  float  mmax, mmin;           	// medianaren maximoa eta minimoa eritasun bakoitzerako
  int    taldemax, taldemin;  	// maximoko eta minimoko taldeak
};

