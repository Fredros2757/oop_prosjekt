#if !defined(__SPILLER_H)
#define __SPILLER_H

#include "ListTool2B.h"
#include "const.h"
#include "spillere.h"


class Spiller: public NumElement{
  private:
	char* navn;
	char* adresse;
	char nvn[NVNLEN]; //bruk denne til å endre på navn
	char adr[STRLEN]; //her har du en til adressen også
  public:
  	Spiller();
    Spiller(int x, char nvn[NVNLEN], char adr[STRLEN]);
    Spiller(int x);
    void display();
    bool sjekkNavn(char input[STRLEN]);
    void tilFil(ofstream & ut);
	string les(char type);

};



#endif