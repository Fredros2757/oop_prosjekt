#if !defined(__DIVAVD_H)
#define __DIVAVD_H

#include "ListTool2B.h"
#include "const.h"
#include "lag.h"
#include "resultat.h"
#include "funksjoner.h"


class divAvd: public TextElement{
  private:
    int antallLag;

    Lag* lagene[MAXLAG];
	Lag* pts[MAXLAG];

    Resultat* terminliste[MAXLAG][MAXLAG];

    bool resultater;
    
  public:
    divAvd();
    divAvd(const char* nvn, int antLag, ifstream &inn);
    void display();
    void endreSpillere();
    void visSpillere();
    void divAvdTilFil(ofstream & ut);
    void resTilSkjerm(char dato[DATOLEN]);
    void resTilFil(char dato[DATOLEN], ofstream & ut);
    bool sjekkResultat(ifstream & inn, bool feil);
    bool finnesLag(char navn[NVNLEN]);
	void termTilFil(ofstream & ut);
	void displayTerm();
	void tabell();
	void tabellTilSkjerm(char ch);
	void tabellTilFil(char ch, string filnavn);
};

#endif
