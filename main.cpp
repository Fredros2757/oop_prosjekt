#include <iostream>


using namespace std;

#include "funksjoner.h"


Spillere spillere;
Idrettene idrettene;

int main(){
  char ch;

  spillere.lesFraFil();
  idrettene.lesIdrettFraFil();

  skrivMeny();
  ch = lesKommando();
  while (ch != 'Q'){
    switch (ch) {
      case 'S': spillere.vis();            break;
      case 'I': idrettene.vis();           break;
      case 'N': ny();                      break;
      case 'F': fjern();                   break;
	  case 'L': idrettene.skrivTermList(); break;
	  case 'K': idrettene.visRes();        break;
      //case 'C':
	  case 'T': idrettene.tabell();        break;
      case 'R': lesResultat();             break;
      case 'D': idrettene.spillerData();   break;
      case 'E': idrettene.endreData();     break;
      //case 'B': break;
      default:  skrivMeny();
    }
    ch = lesKommando();
  }

  spillere.skrivTilFil();
  idrettene.skrivTilFil();

  return 0;


}
