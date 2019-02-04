#if !defined(__LAG_H)
#define __LAG_H

#include "const.h"
#include "spillere.h"
#include "spiller.h"

class Lag{
  private:
    char* navn;
    char* adresse;
	int poeng;
    int antSpillere;
    int spillerNr[MAXSPILLERE];
  public:
    Lag();
    Lag(char nvn[NVNLEN], char adr[STRLEN], int antallSpillere, ifstream & inn);
    void display();
    bool sjekkNavn(char input[NVNLEN]);
    void endreSpillerstall();
    void leggeTil();
    void fjerneSpiller();
    void visData();
    void lagTilFil(ofstream & ut);
    void printNavn();
    void navnTilFil(ofstream & ut);
	int lesInt();
	void giPoeng(int i);
	int visPoeng();
	void nullstillPoeng();
	char* visNavn();
	void skrivPoeng();
	void skrivPoeng(ofstream &ut);
};

#endif
