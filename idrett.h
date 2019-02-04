#if !defined(__IDRETT_H)
#define __IDRETT_H

#include "ListTool2B.h"
#include "enum.h"
#include "const.h"
#include "divAvd.h"
#include "funksjoner.h"


class Idrett: public TextElement{
  private:

    List* divAvdListe = nullptr;
    enum Tabelltype tabelltype;

    int antallDiv;
  public:
    Idrett();
    Idrett(ifstream &inn, const char idrettNavn);
    Idrett(const char* idrettNavn);
    Idrett(const char* nvn, char tabell, int antallDivi, ifstream &inn);
    ~Idrett();
    void display();
    void displayAll();
    void fjernDivAvd();
    void nyDiv();
    void endreSpiller();
    void visData();
    void idrettTilFil(ofstream &ut);
    void visResultater();
    bool sjekkDiv(ifstream & inn, bool feil);
	void divRef();
	void tabell();
};

#endif
