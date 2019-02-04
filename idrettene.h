#if !defined(__IDRETTENE_H)
#define __IDRETTENE_H

#include "ListTool2B.h"
#include "const.h"
#include "idrett.h"


class Idrettene{
  private:
    List* idrettListe = nullptr;
    int antIdrett;
  public:
    Idrettene();
    void display();
    void skrivTilFil();
    void nyIdrett();
    void fjernIdrett();
    void vis();
    void fjernDivAvd();
    void lesIdrettFraFil();
    void nyDivisjon();
    void endreData();
    void spillerData();
    void visRes();
    bool sjekkFeil(bool les);
	void skrivTermList();
	void tabell();
};

#endif
