#define _SCL_SECURE_NO_WARNINGS

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "divAvd.h"

divAvd::divAvd() {

}

divAvd::divAvd(const char* nvn, int antLag, ifstream &inn) : TextElement(nvn){				// Constructor som skaper divisjon fra fil

	antallLag = antLag;																		// Setter antallLag til antLag
	int spilt;
	char dato[DATOLEN];


	for (int i = 0; i < antLag; i++){														// For-loop som looper like mange gonger som det er lag
		char lagNavn[NVNLEN];																// Hjelpevariabel som holder på navnet til laget 
		char adresse[STRLEN];																// Hjelpevariabel som holder på adressen til laget
		int antSpillere;																	// Hjelpevariabel som holder på antall spillere på laget

		inn.getline(lagNavn, NVNLEN);														// Leser inn linjen med navnet på laget
		inn.getline(adresse, STRLEN);														// Leser inn linjen med adressen til laget
		inn >> antSpillere; inn.ignore();													// Leser inn linjen med antall spillere på laget, ignorerer blank

		lagene[i] = new Lag(lagNavn, adresse, antSpillere, inn);							// oppretter nytt lag på plass i, sender med navn, adresse, antall spillere og inn
	}

	for (int i = 0; i < antallLag; i++){
		for (int j = 0; j < antallLag; j++){												// Nested for-loop

			if(i != j){																		// Når i != j, ettersom et lag ikke kan spille med seg selv

				inn >> spilt; inn.ignore();													// Leser inn 1 eller 0. Er det 1 har kampen resulteter
				inn.getline(dato, DATOLEN);													// Om spilt er 0 (kampen har ikke blitt spilt)
				if(spilt == 0){

					terminliste[i][j] = new Resultat(dato, spilt);							// Oppretter nytt resultat, sender med dato og spilt-status

				}else if(spilt == 1){														// Om spilt er 0 (kampen har blitt spilt)

					terminliste[i][j] = new Resultat(dato, spilt, inn);						// Oppretter nytt resultat, sender med dato, spilt-status og inn

				}
			}
		}
	}
}

void divAvd::display() {																	// Displayfunksjonen
	cout << "\nDenne divisjonen heter " << text << "\n";										// Skriver ut navnet til divisjonen
	cout << "\nDivisjonen har " << antallLag << " lag\n";										// Skriver ut hvor mange lag divisjonen har

	for (int i = 0; i < antallLag; i++){													// For-loop som looper like mange ganger som det er lag
		lagene[i]->display();																// Kaller display-funksjonen til lag i
	}

}

void divAvd :: endreSpillere(){																// Funksjon for å endre spillerarrayen hos lag
	char navn[NVNLEN] = "";																		// Hjelpefunksjon som holder en char-array som blir lest inn fra brukeren
	bool fantLag = false;																	// Hjelpefunksjon som holder en bool som blir true om man finner et lag som eksisterer innenfor divisjonen

	cout << "\nI hvilket lag vil du endre spillerene? ";									// Spør brukeren om hvilket lag som skal endre spillerstall

	std::string input = les('n');										// Leser inn navnet
	input.copy(navn, NVNLEN);
	if (input != "q") {
		for (int i = 0; i < antallLag; i++) {														// For-loop som sjekker alle lag om de har samme navn som input
			if (lagene[i]->sjekkNavn(navn)) {														// Om et lag har samme navn som input
				lagene[i]->endreSpillerstall();													// Kaller endreSpillerstall-funksjonen til lag i
				fantLag = true;																	// Setter fantLag til true
			}
		}
	}
	else {
		cout << "Avbryter..";
	}
	if (!fantLag) {																			// Om fantLag er false
		cout << "\nDette laget finnes ikke";												// Skriver til bruker at laget ikke eksisterer
	}
}

void divAvd :: visSpillere(){																// Funksjon for å endre spillerarrayen hos lag
	char navn[NVNLEN] = "";																		// Hjelpefunksjon som holder en char-array som blir lest inn fra brukeren
	bool fantLag = false;																	// Hjelpefunksjon som holder en bool som blir true om man finner et lag som eksisterer innenfor divisjonen

	cout << "\nFra hvilket lag vil du se data om alle spillerne? ";							// Spør brukeren om hvilket lag som skal endre spillerstall

	std::string input = les('n');										// Leser inn navnet
	input.copy(navn, NVNLEN);
	if (input != "q") {
		for (int i = 0; i < antallLag; i++) {														// For-loop som sjekker alle lag om de har samme navn som input
			if (lagene[i]->sjekkNavn(navn)) {														// Om et lag har samme navn som input
				lagene[i]->visData();															// Kaller endreSpillerstall-funksjonen til lag i
				fantLag = true;																	// Setter fantLag til true
			}
		}
	}
	else {
		cout << "Avbryter..";
	}
	if (!fantLag){																			// Om fantLag er false
		cout << "\nDette laget finnes ikke";												// Skriver til bruker at laget ikke eksisterer
	}
}

void divAvd :: divAvdTilFil(ofstream & ut){													// Funksjon for å skrive divAvd til fil
	ut << text << endl;																		// Skriver ut navnet på divisjonen til fil
	ut << antallLag << endl;																// Skriver antall lag til fil

	for (int i = 0; i < antallLag; i++){													// For-loop som looper like mange gonger som det er lag
		lagene[i]->lagTilFil(ut);															// Kaller lagTilFil-funksjonen hos lag i
	}

	for (int i = 0; i < antallLag; i++){													// Nested for-loop
		for (int j = 0; j < antallLag; j++){		
			if(i != j){																		// Om i ikke er j, ettersom et lag ikke spiller mot seg selv
				terminliste[i][j]->resTilFil(ut);											// Kaller resTilFil-funksjonen hos Resultat-objektet på posisjon i, j
			}

		}
	}
}

void divAvd :: resTilSkjerm(char dato[DATOLEN]){											// Funksjon for å skrive resultater til skjerm
	for (int i = 0; i < antallLag; i++){													// Nested for loop for å loope gjennom Resultat-objektene
		for (int j = 0; j < antallLag; j++ ){
			if(i != j){																		// så lenge i ikke er det same som j
				if(terminliste[i][j]->sjekkDato(dato)){										// Kaller sjekkdato hos Resultat på plass i,j, og sender med dato. Om den returnerer true, gå inn i statement
					cout << "\n";
					lagene[i]->printNavn();													// Kaller printNavn() hos Lag i
					cout << " - ";
					lagene[j]->printNavn();													// Kaller printNavn() hos Lag j
					cout << "\n";
					terminliste[i][j]->display();											// Kaller display-funksjonen hos Resultat i, j
	
				}
			}
		}
	}
}

void divAvd :: resTilFil(char dato[DATOLEN], ofstream & ut){								// Funksjon for å skrive resultater til fil
	for (int i = 0; i < antallLag; i++){													// Nested for-loop for å loope gjennom alle Resultatene
		for (int j = 0; j < antallLag; j++){
			if(i != j){																		// om i ikke er lik j
				if(terminliste[i][j]->sjekkDato(dato)){										// Kaller sjekkdato hos Resultat på plass i,j, og sender med dato. Om den returnerer true, gå inn i statement
					ut << "\n";
					lagene[i]->navnTilFil(ut);												// Kaller navnTilFil-funksjonen hos Lag i
					ut << " - ";
					lagene[j]->navnTilFil(ut);												// Kaller navnTilFil-funksjonen hos Lag j
					ut << "\n";
					terminliste[i][j]->stilling(ut);										// Kaller stilling-funksjonen hos Resultat i, j
				}
			}
		}
	}
}


bool divAvd :: sjekkResultat(ifstream & inn, bool feil){									// Funksjon som sjekker (og leser inn) resultater

	int antDato;																			// Int som holder på hvor mange ulike datoer som skal leses inn
	int antResPaaEnDato;																	// Int som holder på hvor mange ulike kamper det er under hver dato
	char dato[DATOLEN];																		// Chararray som holder på datoen
	char hlag[NVNLEN];																		// Chararray som holder på navnet til hjemmelaget
	char blag[NVNLEN];																		// Chararray som holder på navnet til bortelaget

	inn >> antDato; inn.ignore();															// Leser inn hvor mange ulike datoer det er, ignorerer blank

	for (int x = 0; x < antDato; x++){														// For-loop som looper like mange ganger som det er ulike datoer
		inn >> antResPaaEnDato; inn.ignore();												// Leser inn hvor mange kamper det er på datoen, ignorerer blank
		inn.getline(dato, DATOLEN);															// Leser inn datoen fra fil

		for(int y = 0; y < antResPaaEnDato; y++){											// For-loop som looper like manger som det er kamper på en dato

			bool fantKamp = false;															// Bool om kampen er funnet

			inn.getline(hlag, NVNLEN);														// Leser inn hjemmelaget

			if(!finnesLag(hlag)){															// Sjekker om hjemmelaget eksisterer i divisjonen
				cout << "\n" << hlag << " finnes ikke i divisjonen";						// Om laget ikke finnes, gir beskjed om dette
				return false;																// Og returnerer false
			}

			inn.getline(blag, NVNLEN);														// Leser inn bortelaget

			if(!finnesLag(blag)){															// Sjekker om bortelaget eksisterer i divisjonen
				cout << "\n" << blag << " finnes ikke i divisjonen";						// Om laget ikke finnes, gir beskjed om dette
				return false;																// Og returnerer false
			}

			for(int i = 0; i < antallLag; i++){												// Nested for-loop, som looper gjennom terminlisten
				for(int j = 0; j < antallLag; j++){
					if(i != j){																// Om i ikkje er j	
						if(terminliste[i][j]->sjekkDato(dato)){								// Sjekker om datoen som er lest inn er samme som datoen som i Resultat i,j
							if(lagene[i]->sjekkNavn(hlag) && lagene[j]->sjekkNavn(blag)){	// Sjekker om Lag i er det samme som heimelaget, og Lag j er det samme som bortelaget
								fantKamp = true;											// Kampen er funnet, setter fantKamp til true
								if(!terminliste[i][j]->kampErSpilt()){						// Sjekker om kampen er spilt
									terminliste[i][j]->lesResultat(inn, feil);				// Om kampen ikke er spilt, kaller lesResultat i Resultat i, j, sender med inn og boolen feil
								}else{
									cout << "\nKampen mellom " << hlag << " og " << blag << " er allerede spilt";	// Om kampen allerede er spilt, så får brukeren beskjed om dette
									return false;											// Returnerer false
								} 
							}					
						}		
					}
				}
			}
			if(fantKamp == false){															// Om en kamp ikke ble funnet
				cout << "\n" << hlag << " og " << blag << " spiller ikke mot hverandre på " << dato; // Gir bruker beskjed om dette
				return false;																// Returnerer false
			}
		}
	}
	return true;																			// Om ingen feil ble funnet, returnerer true
}

bool divAvd :: finnesLag(char navn[NVNLEN]){												// Funksjon som sjekker om et lag i divisjonen eksisterer, tar inn char-arrayen navn som argument
	bool finnes = false;																	// Bool finnes som er satt til false
	for (int i = 0; i < antallLag; i++){													// For-loop som looper gjennom alle lagene i divisjonen
		if(lagene[i]->sjekkNavn(navn)){														// Sjekker om Lag i har samme navnet som navn
			finnes = true;																	// Om dette, setter finnes til true
		}
	}
	return finnes;																			// Returnerer finnes
}



void divAvd::displayTerm() {											// displayer terminlisten

	cout << "\t\t";

	for (int i = 1; i <= antallLag; i++) {
		cout << i << "\t";
	}

	cout << endl;

	for (int i = 0; i < antallLag; i++) {

		cout << i + 1 << ". "; lagene[i]->printNavn();

		for (int j = 0; j < antallLag; j++) {

			if (i == j) {
				cout << "\t--";
			}

			if (i != j) {												// så lenge i ikke er det same som j
				cout << "\t";
				terminliste[i][j]->printDato();
			}
		}

		cout << endl;
	}
}





void divAvd::termTilFil(ofstream & ut) {			//skriver terminlisten til fil 

	cout << "\nSkriver terminlisten til fil...\n";

	ut << setw(27);

	for (int i = 1; i <= antallLag; i++) {
		if (i == 1) {
			ut << i;
		}
		else {
			ut << setw(24) << i;
		}
	}

	ut << endl;

	for (int i = 0; i < antallLag; i++) {

		ut << i + 1 << ". "; lagene[i]->navnTilFil(ut);
		ut << "\t\t";

		for (int j = 0; j < antallLag; j++) {

			if (i == j) {
				ut << " --\t\t\t";
			}

			if (i != j) {
				terminliste[i][j]->datoTilFil(ut);
				ut << "\t\t\t";
			}
		}

		ut << endl;
	}
}

void divAvd::tabell()                                                //Funksjon som skriver tabell for en spesifikk divisjon til enten skjerm eller fil
{
	string input;                                                    //Hjelpevariabel

	cout << "Trykk enter for å skrive til skjerm, skriv inn filnavn for å skrive til fil";
	getline(cin, input);                                                //Henter input

	if (!input.empty()) {                                               //Hvis input ikke var blank skrives tabellen til filen angitt i input 
		cout << "Skriver tabell til fil " << input;
	}
	else {                                                              //Hvis input var blank skrives tabellen til skjermen
		cout << "Skriver tabell til skjerm";
	}
}

void divAvd::tabellTilSkjerm(char ch) {                                     //Funksjon som skriver tabell til skjerm
																			//	Lag* tempLag[MAXLAG];                                              //Temp brukt i sortering av poeng
																			//	Lag* hjelpeLag[MAXLAG];
	char res = ch;//Variabel som sendes med for å bestemme tabelltype
	
	for (int x = 0; x < antallLag; x++) {
		lagene[x]->nullstillPoeng();                          //Nullstiller poeng i tabell
	}
	
	switch (ch) {
	case 'A':                                                             //Tabelltype 2-1-0
		for (int i = 0; i < antallLag; i++) {                             //Nestet for-loop
			for (int j = 0; j < antallLag; j++) {

				if (i != j) {                                             //Sjekker at ikke spiller mot seg selv
					char poenggis = terminliste[i][j]->resTabell(res);          //sjekker resultat og lagrer i variabel

					switch (poenggis) {                                  //Gir poeng til lag basert på resultat
					case 'H':
						lagene[i]->giPoeng(2);                          //Hjemmeseier
						break;
					case 'B':
						lagene[j]->giPoeng(2);                          //Borteseier
						break;
					case 'U':
						lagene[i]->giPoeng(1);                          //Uavgjort
						lagene[j]->giPoeng(1);
						break;
					}
				}
			}
		}

		break;

	case 'B':

		for (int i = 0; i < antallLag; i++) {                            //Nestet for-loop
			for (int j = 0; j < antallLag; j++) {

				if (i != j) {                                            //Sjekker at ikke spiller mot seg selv
					char poenggis = terminliste[i][j]->resTabell(res);         //sjekker resultat og lagrer i variabel         

					switch (poenggis) {                                 //Gir poeng til lag basert på resultat
					case 'H':
						lagene[i]->giPoeng(3);                             //Hjemmeseier
						break;
					case 'B':
						lagene[j]->giPoeng(3);                             //Borteseier
						break;
					case 'U':
						lagene[i]->giPoeng(1);                                //Uavgjort
						lagene[j]->giPoeng(1);
						break;
					}
				}
			}
		}

		break;

	case 'C':

		for (int i = 0; i < antallLag; i++) {                         //Nestet for-loop
			for (int j = 0; j < antallLag; j++) {

				if (i != j) {                                           //Sjekker at ikke spiller mot seg selv
					char poenggis = terminliste[i][j]->resTabell(res);                                        //sjekker resultat og lagrer i variabel         

					switch (poenggis) {                          //Gir poeng til lag basert på resultat
					case 'H':
						lagene[i]->giPoeng(2);                   //Hjemmeseier
						break;
					case 'B':
						lagene[j]->giPoeng(2);                  //Borteseier
						break;
					case 'X':
						lagene[i]->giPoeng(2);                 //Hjemmeseier på overtid
						lagene[j]->giPoeng(1);
						break;
					case 'Y':
						lagene[i]->giPoeng(1);                //Borteseier på overtid
						lagene[j]->giPoeng(2);
						break;
					}
				}
			}
		}
	}

	cout << "\n" << setw(25) << "-----" << text << "-----" << "\n";
	for (int i = 0; i < antallLag; i++) {              //Skriver ut ant poeng pr lag fra den sorterte arrayen
		char* navnn = lagene[i]->visNavn();
		int poengg = lagene[i]->visPoeng();
		cout << setw(10) << navnn << setw(50) << poengg << "\n";
	}
}


void divAvd::tabellTilFil(char ch, string filnavn) {                                     //Funksjon som skriver tabell til skjerm
																	   //	Lag* hjelpeLag[MAXLAG];
	char res = ch;                                                        //Variabel som sendes med for å bestemme tabelltype

	for (int x = 0; x < antallLag; x++) {
		lagene[x]->nullstillPoeng();                          //Nullstiller poeng i tabell
	}

	switch (ch) {

	case 'A':                                                             //Tabelltype 2-1-0

		for (int i = 0; i < antallLag; i++) {                             //Nestet for-loop
			for (int j = 0; j < antallLag; j++) {

				if (i != j) {                                             //Sjekker at ikke spiller mot seg selv
					char poenggis = terminliste[i][j]->resTabell(res);          //sjekker resultat og lagrer i variabel

					switch (poenggis) {                                  //Gir poeng til lag basert på resultat
					case 'H':
						lagene[i]->giPoeng(2);                          //Hjemmeseier
						break;
					case 'B':
						lagene[j]->giPoeng(2);                          //Borteseier
						break;
					case 'U':
						lagene[i]->giPoeng(1);                          //Uavgjort
						lagene[j]->giPoeng(1);
						break;
					}
				}
			}
		}

		break;

	case 'B':

		for (int i = 0; i < antallLag; i++) {                            //Nestet for-loop
			for (int j = 0; j < antallLag; j++) {

				if (i != j) {                                            //Sjekker at ikke spiller mot seg selv
					char poenggis = terminliste[i][j]->resTabell(res);         //sjekker resultat og lagrer i variabel         

					switch (poenggis) {                                 //Gir poeng til lag basert på resultat
					case 'H':
						lagene[i]->giPoeng(3);                             //Hjemmeseier
						break;
					case 'B':
						lagene[j]->giPoeng(3);                             //Borteseier
						break;
					case 'U':
						lagene[i]->giPoeng(1);                                //Uavgjort
						lagene[j]->giPoeng(1);
						break;
					}
				}
			}
		}

		break;

	case 'C':

		for (int i = 0; i < antallLag; i++) {                         //Nestet for-loop
			for (int j = 0; j < antallLag; j++) {

				if (i != j) {                                           //Sjekker at ikke spiller mot seg selv
					char poenggis = terminliste[i][j]->resTabell(res);                                        //sjekker resultat og lagrer i variabel         

					switch (poenggis) {                          //Gir poeng til lag basert på resultat
					case 'H':
						lagene[i]->giPoeng(2);                   //Hjemmeseier
						break;
					case 'B':
						lagene[j]->giPoeng(2);                  //Borteseier
						break;
					case 'X':
						lagene[i]->giPoeng(2);                 //Hjemmeseier på overtid
						lagene[j]->giPoeng(1);
						break;
					case 'Y':
						lagene[i]->giPoeng(1);                //Borteseier på overtid
						lagene[j]->giPoeng(2);
						break;
					}
				}
			}
		}
	}

	ofstream ut(filnavn, std::ios_base::app);
	ut << "-----" << text << "-----" << "\n";
	for (int i = 0; i < antallLag; i++) {              //Skriver ut ant poeng pr lag fra den sorterte arrayen
		char* navnn = lagene[i]->visNavn();
		int poengg = lagene[i]->visPoeng();
		ut << setw(10) << navnn << setw(50) << poengg << "\n";
	}
}