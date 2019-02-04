#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#include "funksjoner.h"

extern Spillere spillere;
extern Idrettene idrettene;

void skrivMeny(){
  cout << "\nS  - Skriv spiller";
  cout << "\nI  - Skriv idrett";
  cout << "\nN  - Ny spiller, idrett eller divisjon/avdeling";
  cout << "\nF  - Fjern spiller, idrett eller avdeling";
  cout << "\nL  - Skriv terminliste for en divisjon/avdeling";
  cout << "\nK  - Skriv resultatet av alle Kampene på en gitt dato";
  cout << "\nT  - Skriv Tabellen for idrett eller divisjon/avdeling";
  cout << "\nR  - Lese inn resultatliste fra fil";
  cout << "\nD  - Skriv data om alle spillere på et lag";
  cout << "\nE  - Endre spillere på et lag";
}

char lesKommando()  {
   char komm;
   cout << "\n\n\nVelg en kommando: ";
   cin >> komm;  cin.ignore();
   return toupper(komm);
}

char lesKomm2(){
  char komm;
  cin >> komm; cin.ignore();
  return toupper(komm);
}

void ny(){
  char ch;

  ch = lesKomm2();
  switch(ch){
    case 'S': spillere.nySpiller(); break;
    case 'I': idrettene.nyIdrett(); break;
    case 'D': idrettene.nyDivisjon(); break;
  }
}

void fjern(){
  char ch;

  ch = lesKomm2();
  switch(ch){
    case 'S': spillere.fjernSpiller(); break;
    case 'I': idrettene.fjernIdrett(); break;
    case 'D': idrettene.fjernDivAvd(); break;
  }
}

void lesResultat(){

  cout << "\nSjekker filen for feil...";

  if(idrettene.sjekkFeil(false)){
    cout << "\nIngen feil funnet, leser inn fra fil...";
    idrettene.sjekkFeil(true);
  }else{
    cout << "\nFilen inneholdt feil, avbryter operasjon";
  }
}

string les(char type) {

	string temp = "";

	while (temp != "q") {
		int lengde;
		switch (type) {

		case 'n':
			lengde = NVNLEN;
			break;

		case 'd':
			lengde = DATOLEN;
			break;

		case 's':
			lengde = STRLEN;
			break;

		default:
			lengde = 0;
			break;

		}

		if (lengde != 0) {

			do {
				cout << "\nSkriv inn input: ";
				getline(cin, temp); // Tar input fra bruker
			} while ((temp.empty() || temp.length() > lengde) || std::cin.fail());
			return temp;
		}
		else {
			cout << "Ugyldig input\n";
			return temp;
		}
	}
	return temp;
}

string lesStille(char type) {

	string temp = "";

	while (temp != "q") {
		int lengde;
		switch (type) {

		case 'n':
			lengde = NVNLEN;
			break;

		case 'd':
			lengde = DATOLEN;
			break;

		case 's':
			lengde = STRLEN;
			break;

		default:
			lengde = 0;
			break;

		}

		if (lengde != 0) {

			do {
				getline(cin, temp); // Tar input fra bruker
			} while ((temp.empty() || temp.length() > lengde) || std::cin.fail());
			return temp;
		}
		else {
			return temp;
		}
	}
	return temp;
}

string lesBlank(char type) {

	string temp = "";

	while (temp != "q") {
		int lengde;
		switch (type) {

		case 'n':
			lengde = NVNLEN;
			break;

		case 'd':
			lengde = DATOLEN;
			break;

		case 's':
			lengde = STRLEN;
			break;

		default:
			lengde = 0;
			break;

		}

		if (lengde != 0) {

			do {
				cout << "\nSkriv inn input: ";
				getline(cin, temp); // Tar input fra bruker
			} while ((temp.length() > lengde) || (std::cin.fail()));			
			return temp;
		}
		else {
			cout << "Ugyldig input\n";
			return temp;
		}
	}
	return temp;
}