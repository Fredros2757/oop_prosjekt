#if !defined(__SPILLERE_H)
#define __SPILLERE_H

#include "ListTool2B.h"
#include "const.h"
#include "spiller.h"

class Spillere{
  private:
    List* spillerListe = nullptr;
    int sisteNr; // gjort navnet mindre
  public:
    Spillere();
    void lesFraFil();
    void vis();
    void nySpiller();
    void fjernSpiller();
    void skrivTilFil();
    bool finnesSpiller(int nr);
    void visSpiller(int nr);
    void spillerFraDivAvd(char nvn[NVNLEN], char adr[STRLEN], int nr);
	int lesInt();
	string lesStille(char type);
};

#endif
