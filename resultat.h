#if !defined(__RESULTAT_H)
#define __RESULTAT_H

#include "const.h"


class Resultat {
  private:
    char* dato;
    int hmaal, bmaal;
    bool normalTid;
    int hscorere[MAXSPILLERE];
    int bscorere[MAXSPILLERE];
  public:
	bool kampSpilt;
    Resultat();
    Resultat(char date[DATOLEN], int spilt);
    Resultat(char date[DATOLEN], int spilt, ifstream & inn);
    void display();
    void resTilFil(ofstream & ut);
    bool sjekkDato(char date[DATOLEN]);
    void stilling(ofstream & ut);
    bool kampErSpilt();
    void lesResultat(ifstream & inn, bool feil);
	char resTabell(char res);
	void printDato();
	void datoTilFil(ofstream & ut);
};

#endif
