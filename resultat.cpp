#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

#include "resultat.h"

Resultat :: Resultat(){
}

Resultat :: Resultat(char date[DATOLEN], int spilt){ 						// Constructor som tar inn dato og spilt-status som argument
	dato = new char[DATOLEN];												// Ny chararray
	strcpy(dato,date);														// Kopierer date inn i dato
	if(spilt == 0){															// Om spilt er 0, noko det alltid er
		kampSpilt = false;													// Setter kampSpilt til 0
	}
}

Resultat :: Resultat(char date[DATOLEN], int spilt, ifstream & inn){		// Constructor som tar inn dato, spilt-status og ofstream som argument

	int normal;																// Hjelpeint som holder på normaltidstatus (1 = ferdig etter normaltid, 0 ikke ferdig etter normaltid)

	dato = new char[DATOLEN];												// Ny chararray
	strcpy(dato,date);														// Kopierer date inn i dato
	if(spilt == 1){															// Om spilt er 1, noko det alltid er
		kampSpilt = true;													// Setter kampSpilt til 1
	}

	inn >> hmaal; inn.ignore();												// Leser inn hjemmemål, ignorerer blank
	inn >> bmaal; inn.ignore();												// Leser inn bortemål, ignorerer blank

	inn >> normal; inn.ignore();											// Leser inn normaltid, ignorerer blank

	if(normal == 1){														// Om normaltid er 1
		normalTid = true;													// setter normaltid til true
	}else{	
		normalTid = false;													// Ellers, setter normaltid til false
	}

	if(0 < hmaal){															// Om det er scoret hjemmemål
		for(int i = 0; i < hmaal; i++){										// For-loop som går like mange ganger som det er scoret hjemmemål
			inn >> hscorere[i]; inn.ignore();								// Leser inn målscorer, ignorerer blank
		}	
	}

	
	if (0 < bmaal){															// Om det er scoret bortemål
		for(int i = 0; i < bmaal; i++){										// For-loop som går like mange ganger som det er scoret bortemål
			inn >> bscorere[i]; inn.ignore();								// Leser inn målscorer, ignorerer blank
		}
	}
	
}

void Resultat :: lesResultat(ifstream & inn, bool feil){					// Funksjon som leser inn fra resultater.cpp

	int hm;																	// int som holder på hjemmemål
	int bm;																	// int som holder på bortemål
	int normal;																// int som holder på normaltid-status
	int hs[MAXSPILLERE];													// intarray som holder på målscorere på hjemmelaget 
	int bs[MAXSPILLERE];													// intarray som holder på målscorere på bortelaget

	inn >> hm; inn.ignore();												// Leser inn hjemmemål fra fil, ignorerer blank
	inn >> bm; inn.ignore();												// Leser inn bortemål fra fil, ignorerer blank

	inn >> normal; inn.ignore();											// Leser inn normaltidstatus fra fil

	if(0 < hm){																// Om hm er større enn 0
		for(int i = 0; i < hm; i++){										// Looper gjennom antall målscorere på hjemmelaget
			inn >> hs[i]; inn.ignore();										// Leser målscorer fra fil og putter den inn i hs[i], ignorerer blank
		}
	}

	if(0 < bm){																// Om bm er større enn 0
		for (int i = 0; i < bm; i++){										// Looper gjennom antall målscorere på bortelaget
			inn >> bs[i]; inn.ignore();										// Leser målscorer fra fil og putter den inn i bs[i], ignorerer blank
		}
	}

	if(feil == true){														// Om feil er true
		kampSpilt = true;													// Setter kampSpilt til true
		hmaal = hm;															// Kopierer hm inn i hmaal
		bmaal = bm;															// Kopierer bm inn i bmaal
		if(normal == 1){													// Setter normalTid til true eller false ut i fra inten som ble lest inn
			normalTid = true;
		}else{
			normalTid = false;
		}
		for (int i = 0; i < hm; i++){										// For-loop som kopierer hs inn i hscorere
			hscorere[i] = hs[i];
		}
		for (int i = 0; i < bm; i++){										// For-loop som kopierer bs inn i bscorere
			bscorere[i] = bs[i];
		}
	}
}

void Resultat :: display(){													// Display-funksjon

	if(kampSpilt){															// Om kampen er spilt
		cout << "\n" <<	hmaal << " - " << bmaal << "\n";					// Skriver ut stillingen i kampen
	}else{																	// Om kampen ikke er spilt
		cout << dato;									// Skriver ut at kampen ikke er spilt
	}
}

void Resultat :: stilling(ofstream & ut){									// Funksjon som skriver stillingen i kampen til fil

	if(kampSpilt){															// Om kampen er spilt
		ut << "\n" << hmaal << " - " << bmaal << "\n";						// Skriver ut stillingen i kampen til fil
	}else{																	// Om kampen ikke er spilt
		ut << "\nKampen er ikke spilt\n";										// Skriver at kampen ikke er spilt til fil
	}
}

void Resultat :: resTilFil(ofstream & ut){									// Funksjon som skriver resultat-objekter til fil

	if(kampSpilt){															// Om kampSpilt er true
		ut << kampSpilt << endl;											// Skriv kampSpilt til fil
		ut << dato << endl;													// Skriv dato til fil

		ut << hmaal << endl;												// Skriv hjemmemål til fil
		
		ut << bmaal << endl;												// Skriv bortemål til fil
		

		ut << normalTid << endl;											// Skriv normaltid til fil

		for(int i = 0; i < hmaal; i++){										// For-loop som looper like mange gonger som det er hjemmemål
			ut << hscorere[i];												// Skriver målscorer nr i til fil
			if(i < hmaal-1){												// Skriver et mellomrom, om forrige spiller ikke var den siste som scoret
				ut << " ";
			}
		}
		if(0 < hmaal){														// Om det var scoret hjemmemål, skriv ut et linjeskift
			ut << endl;
		}

		for(int i = 0; i < bmaal; i++){										// For-loop som looper like mange gonger som det er bortemål
			ut << bscorere[i];												// Skriver målscorer nr i til fil
			if(i < bmaal-1){												// Skriver et mellomrom, om forrige spiller ikke var den siste som scoret
				ut << " ";
			}
		}
		if(0 < bmaal){														// Om det var scoret bortemål, skriv ut et linjeskift
			ut << endl;
		}

	}else{																	// om kampSpilt er false
		ut << kampSpilt << endl;											// Skriv kampSpilt til fil
		ut << dato << endl;													// skriv dato til fil
	}
}

bool Resultat :: sjekkDato(char date[DATOLEN]){								// Funksjon som sjekker om medsent dato er den samme som datoen til objektet
	if(strcmp(date, dato) == 0){											// Bruker strcmp, om den er lik 0, returnerer true, om ikkje, returnerer false
		return true;
	}else{
		return false;
	}
}

bool Resultat :: kampErSpilt(){
	return kampSpilt;
}

char Resultat::resTabell(char res) {         //Funksjon som sender tilbake resultat for bruk i poenggiving

	char poenggis = ' ';

	switch (res) {
	case 'A':
		if (kampSpilt) {
			if (hmaal > bmaal) {
				poenggis = 'H';
			}
			else if (hmaal < bmaal) {
				poenggis = 'B';
			}
			else {
				poenggis = 'U';
			}
		}
		break;

	case 'B':
		if (kampSpilt) {
			if (hmaal > bmaal) {
				poenggis = 'H';
			}
			else if (hmaal < bmaal) {
				poenggis = 'B';
			}
			else {
				poenggis = 'U';
			}
		}
		break;

	case 'C':
		if (kampSpilt) {
			if (normalTid) {

				if (hmaal > bmaal) {
					poenggis = 'H';
				}
				else {
					poenggis = 'B';
				}
			}
			else {
				if (hmaal > bmaal) {
					poenggis = 'X';
				}
				else {
					poenggis = 'Y';
				}
			}
		}
		break;

	}
	return poenggis;
}

void Resultat::printDato() {
	char* fDato;
	fDato = dato;

	cout << fDato[0] << fDato[1] << "/" << fDato[2] << fDato[3];
}

void Resultat::datoTilFil(ofstream & ut) {
	char* fDato;
	fDato = dato;

	ut << fDato[0] << fDato[1] << "/" << fDato[2] << fDato[4];
}
