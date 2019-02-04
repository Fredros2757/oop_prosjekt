#define _SCL_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

#include "idrett.h"

//parameterløs construktor, lat som den ikke eksisterer
Idrett::Idrett()
{
}

//Constructor som leser inn data fra fil
Idrett::Idrett(ifstream & inn, const char idrettNavn){

}

Idrett::Idrett(const char* nvn, char tabell, int antallDivi, ifstream &inn) : TextElement(nvn){		// Constructor for å lese inn fra fil
	divAvdListe = new List(Sorted);																	// Oppretter ny liste
	antallDiv = antallDivi;																			// Setter antallDiv til antallDivi
	switch(tabell){																					// Switch som setter tabelltypen til idretten
		case 'A': tabelltype = A; break;
		case 'B': tabelltype = B; break;
		case 'C': tabelltype = C; break;
	}

	for (int i = 0; i < antallDiv; i++){															// Loop som looper antall ganger som det er divisjoner
		int antLag;																					// Hjelpevariabel for å holde på antall lag som er i divisjonen
		char nvn[NVNLEN];																			// Hjelpevariabel for å holde navnet til divisjonen

		inn.getline(nvn, NVNLEN);																	// Leser inn linjen som har navnet på divisjonen
		inn >> antLag; inn.ignore();																// Leser inn linjen som har antall lag i divisjonen, ignorerer blank

		divAvd* tempDiv;																			// Hjelpepeker

		tempDiv = new divAvd(nvn, antLag, inn);														// Oppretter ny divAvd, sender med navnet, antall lag og inn
		divAvdListe->add(tempDiv);																	// Legger divisjonen til i divAvd-lista
	}
}

//Constructor som tar inn char som argument
Idrett::Idrett(const char * idrettNavn) : TextElement(idrettNavn) {									// Constructor brukt i nyIdrett();
	char ch;																						// Hjelpevariabel for å holde på en char
	divAvdListe = new List(Sorted);																	// Oppretter ny liste med divAvd-objekter
	antallDiv = 0;																					// Antall divisjoner i Idretten

	do {
		cout << "Oppgi tabelltype A (2-1-0), B (3-1-0), C (3-2-1-0): ";									// Spør bruker om tabelltype
		cin >> ch; cin.ignore();                                                                    // Leser inn input, ignorerer blank
		ch = toupper(ch);																				// upper-caser input
	} while (!((ch == 'A' || ch == 'B') || (ch == 'C')));
	//byttet den ut med en switch
	switch (ch){																					// Switch for å sette tabelltype
		case 'A': tabelltype = A; break;
		case 'B': tabelltype = B; break;
		case 'C': tabelltype = C; break;
	}

	cout << "\nIdretten " << text << " har vorte oppretta\n";										// Gir beskjed om at idretten har blitt opprettet
}

//Destructor
Idrett::~Idrett(){
	delete divAvdListe; /*sikker mer som må gjøres(?)*/

}

//Displayer en idrett
void Idrett::display(){																			


	cout << "\nNavnet på idretten er " << text << "\n";												// Skriver ut navnet på idretten
	cout << "Den har " << divAvdListe->noOfElements() << " divisjoner/avdelinger\n";				// Skriver ut antall divisjoner

	switch(tabelltype){																				// Switch som skriver ut tabelltypen
		case A: cout << "Tabelltypen er 2-1-0\n"; break;
		case B: cout << "Tabelltypen er 3-1-0\n"; break;
		case C: cout << "Tabelltypen er 3-2-1-0\n"; break;
	}

}

void Idrett::displayAll(){																			// display-funksjon brukt i I A-funksjonen
	display();

	divAvdListe->displayList();																		// Kaller displayliste-funksjonen til divAvdListen
}

void Idrett :: nyDiv(){																				// Funksjon for å lese inn ny divisjon fra fil

	char filNavn[STRLEN] = "";                                                                     // Hjelpevariabel som holder på filnavnet
	char divNavn[NVNLEN] = "";																			// Hjelpevariabel som holder på divisjonsnavnet
	int antLag;																						// Hjelpevariabel som holder på antall lag i divisjonen

	cout << "Hva er navnet på den nye divisjonen? ";

	std::string input = les('n');										// Leser inn navnet
	input.copy(divNavn, NVNLEN);
	if (input != "q") {

		if (!divAvdListe->inList(divNavn)) {
			cout << "Skriv navnet på filen du vil lese inn\n";												// Spør bruker om filnavn
			std::string input = les('s');										// Leser inn navnet
			input.copy(filNavn, STRLEN);
			if (input != "q") {
				ifstream innfil(filNavn);																		// Åpner filen som bruker angav
				if (innfil) {																						// Sjekker om filen eksisterer
					cout << "\nLeser inn ny divisjon fra fil...\n";
					innfil >> antLag; innfil.ignore();															// Leser linjen som holder antall lag i divisjonen, ignorerer blank
					divAvd* tempDiv;																			// Hjelpepeker
					tempDiv = new divAvd(divNavn, antLag, innfil);												// Oppretter ny divisjon, sender med navn, antall lag og innfil
					divAvdListe->add(tempDiv);																	// Legger den nye divisjonen til i divAvd-listen
				}
				else {
					cout << "\nDenne filen finnes ikke!";														// Gir bruker feilmelding om filen ikke eksisterer
				}
			}
			else {
				cout << "Avbryter..";
			}
		}
		else {
			cout << "\nDenne divisjonen finnes allerede";
		}
	}
	else {
		cout << "Avbryter..";
	}

}

void Idrett :: endreSpiller(){																			// Funksjon for å endre spillerarrayen hos et lag
	char navn[NVNLEN] = "";																					// Hjelpevariabel for å holde på char-array
	divAvd* tempDiv;																					// Hjelpepeker

	cout << "\nI hvilken divisjon er laget du vil endre? ";												// Spør bruker om divisjon
	std::string input = les('n');										// Leser inn navnet
	input.copy(navn, NVNLEN);
	if (input != "q") {																	// Tar inn input fra bruker
		if (divAvdListe->inList(navn)) {																		// Sjekker om divisjonen finnes i lista over divisjoner

			tempDiv = (divAvd*)divAvdListe->remove(navn);													// Fjerner divisjonen fra lista
			tempDiv->endreSpillere();																		// Kaller endreSpillere()-funksjonen hos divAvd
			divAvdListe->add(tempDiv);																		// Legger divisjonen tilbake i divAvd-lista
		}
		else {
			cout << "\nDenne divisjonen finnes ikke";														// Skriver ut melding til bruker om divisjonen ikke finnes i divisjons-lista
		}
	}
	else {
		cout << "Avbryter..";
	}
}

void Idrett :: visResultater(){																			// Funksjon som for å hente resultater, og skriver de til skjerm eller fil

	char navn[NVNLEN] = "";																					// Hjelpevariabel som holder en chararray
	char dato[DATOLEN] = "";																					// Hjelpevariabel som holder en chararray
	char filnavn[STRLEN] = "";																				// Hjelpevariabel som holder en chararray

	divAvd* tempDiv;																					// Hjelpepeker

	cout << "Trykk Enter for å søke i alle divisjoner, eller skriv inn navnet på divisjonen du vil søke i ";	// Spør bruker om de vil søke i en divisjon eller i alle divisjoner
	std::string input = lesBlank('n');										// Leser inn navnet
	input.copy(navn, NVNLEN);
	if (input != "q") {
		if (input.empty()) {																			// Sjekker om input er Enter
			cout << "Trykk Enter for å skrive til skjerm, eller skriv inn filnavn ";						// Spør bruker om de vil skrive til skjerm eller fil
			
			std::string input = lesBlank('s');										// Leser inn navnet
			input.copy(filnavn, STRLEN);
			if (input != "q") {
				if (input.empty()) {																		// Sjekker om input er Enter

					cout << "Hvilken dato vil du søke etter?";												// Spør bruker etter dato

					std::string input = les('d');									                
					input.copy(dato, DATOLEN);															// Leser inn dato

					if (input != "q") {

						for (int i = 1; i <= divAvdListe->noOfElements(); i++) {										// Looper gjennom listen med divAvder
							tempDiv = (divAvd*)divAvdListe->removeNo(i);											// Fjerner element nr i fra listen
							tempDiv->resTilSkjerm(dato);															// Kaller resTilSkjerm-funksjonen hos DivAvd
							divAvdListe->add(tempDiv);																// Legger divAvden tilbake til listen
						}
					}
					else {
						cout << "Avbryter..";
					}
				}
				else {																							// Om bruker skriver filnavn

					ofstream utfil(filnavn);																		// Åpner/oppretter filen

					cout << "(Til fil) Hvilken dato vil du søke etter?";													// Spør bruker etter dato
					std::string input = les('d');
					input.copy(dato, DATOLEN);															// Leser inn dato
					if (input != "q") {
						for (int i = 1; i <= divAvdListe->noOfElements(); i++) {										// Loopre gjennom listen med divAvder
							tempDiv = (divAvd*)divAvdListe->removeNo(i);											// Fjerner element nr i fra listen
							tempDiv->resTilFil(dato, utfil);														// Kaller resTilFil-funksjonen til DivAvd
							divAvdListe->add(tempDiv);																// Legger divAvden tilbake i listen
						}
					}
					else {
						cout << "Avbryter..";
					}
				}
			}
			else {
				cout << "Avbryter..";
			}

		}
		else{																								// Om bruker oppgir navnet på en divisjon

		if(divAvdListe->inList(navn)){																	// Sjekker om divisjonen eksisterer

			cout << "Trykk Enter for å skrive til skjerm, eller skriv inn filnavn ";					// Spør bruker om de vil skrive resultatene til skjerm eller fil
			std::string input = lesBlank('s');										// Leser inn navnet
			input.copy(filnavn, STRLEN);
			if (input != "q") {
				if (input.empty()) {																// Sjekker om input er enter
					cout << "Hvilken dato vil du søke etter? ";												// Spør brukeren etter dato

					std::string input = les('d');										// Leser inn navnet
					input.copy(dato, DATOLEN);
					if (input != "q") {
						tempDiv = (divAvd*)divAvdListe->remove(navn);											// Fjerner valgt divisjon fra divAvdListen
						tempDiv->resTilSkjerm(dato);															// Kaller resTilSkjerm-funksjonen hos divAvd
						divAvdListe->add(tempDiv);																// Legger divAvden tilbake til listen
					}
					else {
						cout << "Avbryter..";
					}
				}
				else {																						// Om input er et filnavn

					ofstream utfil(filnavn);																// Åpner/oppretter filen

					cout << "(Til fil) Hvilken dato vil du søke etter? ";												// Spør bruker etter dato

					std::string input = les('d');										// Leser inn navnet
					input.copy(dato, DATOLEN);
					if (input != "q") {
						tempDiv = (divAvd*)divAvdListe->remove(navn);											// Fjerner divAvden fra divAvdListen
						tempDiv->resTilFil(dato, utfil);														// Kaller resTilFil-funksjonen hos divAvd
						divAvdListe->add(tempDiv);																// Legger divAvden tilbake i listen
					}
					else {
						cout << "Avbryter..";
					}
				}
			}
			else {
				cout << "Avbryter..";
			}

		}
		else{
			cout << "Denne divisjonen finnes ikke";														// Skriver feilmelding til bruker om divisjonen ikke finnes
		}
	}
	}
	else {
		cout << "Avbryter..";
	}
	

}

void Idrett :: visData(){																				// Funksjon for å vise data for alle spillere på et lag

	char navn[NVNLEN] = "";																					// Hjelpevariabel for å holde char-array
	divAvd* tempDiv;																					// Hjelpepeker

	cout << "\nOppgi divisjon ";																		// Spør bruker om divisjon
	std::string input = les('n');										// Leser inn navnet
	input.copy(navn, NVNLEN);
	if (input != "q") {
		if (divAvdListe->inList(navn)) {																		// Sjekker om divisjonen er i divAvdListen
			tempDiv = (divAvd*)divAvdListe->remove(navn);													// Fjerner divisjonen fra listen
			tempDiv->visSpillere();																			// Kaller visSpillere() hos divAvd
			divAvdListe->add(tempDiv);																		// Legger divisjonen tilbake til divAvdListen
		}
		else {
			cout << "\nDenne divisjonen finnes ikke";														// Skriver feilmelding til bruker om divisjonen ikke finnes
		}
	}
	else {
		cout << "Avbryter..";
	}
}

void Idrett :: fjernDivAvd(){																			// Funksjon for å fjerne divAvd
	char navn[STRLEN] = "";																					// Hjelpevariabel for å holde på et navn
	char ch;																							// Hjelpevariabel for å holde en char

	if(!divAvdListe->isEmpty()){																		// Sjekker om idretten har divisjoner
		cout << "\nHvilken divisjon/avdeling vil du fjerne? ";											// Spør bruker om hvilken divisjon som skal fjernes
		std::string input = les('n');										// Leser inn navnet
		input.copy(navn, NVNLEN);
		if (input != "q") {
			if (divAvdListe->inList(navn)) {																	// Sjekker om angitt divisjon finnes i divAvd-listen
				do {
					cout << "\nEr du sikker på at du vil fjerne denne idretten? (y/n): ";						// Spør om brukeren virkelig vil fjerne divisjonen
					cin >> ch; cin.ignore();                                                                   // Tar input, ignorerer blank
				} while (!(ch == 'y' || ch == 'n'));
					
				if (ch == 'y') {																				// Om ch er y
					divAvdListe->destroy(navn);																// Destroyer angitt divisjon
					cout << "\nDivisjonen/avdelingen ble slettet";											// Gir bruker beskjed om at den er fjernet
					antallDiv--;																			// Decrementerer antallDiv
				}
				else if (ch == 'n') {																		// Om ch er n
					cout << "\nDivisjonen/avdelingen ble ikke slettet";										// Gir beskjed om at divisjonen ikke ble slettet
				}
			}
			else {
				cout << "\nDenne divisjonen/avdelingen finnes ikke";										// Gir beskjed om at divisjonen ikke finnes
			}
		}
		else {
			cout << "Avbryter..";
		}

	}else{
		cout << "\nDenne idretten har ingen divisjoner/avdelinger";										// Gir beskjed om at idretten ikke har noen divisjoner/avdelinger
	}
}

void Idrett :: idrettTilFil(ofstream &ut){																// Funksjon for å skrive idrett til fil

	divAvd* hjelpeDivAvd;																				// Hjelpepeker

	ut << text << endl;																					// Skriver navnet på idretten til fil
	switch(tabelltype){																					// Switch som skriver ut tabelltype
		case A: ut << "A" << endl; break;
		case B: ut << "B" << endl; break;
		case C: ut << "C" << endl; break;
	}
	ut << divAvdListe->noOfElements() << endl;															// Skriver antall divisjoner til fil

	for (int i = 1; i <= divAvdListe->noOfElements(); i++){												// For-loop som looper like mange ganger som det er divisjoner

		hjelpeDivAvd = (divAvd*)divAvdListe->removeNo(i);												// Fjerner divAvden fra listen
		if(hjelpeDivAvd){																				// Sjekker at hjelpepekeren ikke er en nullpeker
			hjelpeDivAvd->divAvdTilFil(ut);																// Kaller divAvdTilFil-funksjonen hos divAvd
			divAvdListe->add(hjelpeDivAvd);																// Legger divAvden tilbake til divAvdListen
		}

	}

}

bool Idrett :: sjekkDiv(ifstream & inn, bool feil){														// Funksjon som sjekker feil med divisjoner

	int antDiv;																							// int som holder på antall divisjoner
	char navn[NVNLEN];																					// Chararray som holder på et navn
	divAvd* tempDiv;																					// Hjelpepeker

	inn >> antDiv; inn.ignore();																		// Leser inn antall divisjoner fra fil, ignorerer blank	
	for (int i = 0; i < antDiv; i++){																	// For-loop som looper gjennom alle divisjoner
		inn.getline(navn, NVNLEN);																		// Leser inn divisjonsnavnet fra fil
		if(divAvdListe->inList(navn)){																	// Sjekker om en divisjon med dette navnet eksisterer i divAvd-listen
			tempDiv = (divAvd*)divAvdListe->remove(navn);												// Fjerner divAvden fra divAvdListe	
			if(tempDiv->sjekkResultat(inn, feil)){														// Sjekker om informasjonen om divisjonen er korrekt med sjekkResultat-funksjonen i divAvd-objektet
				divAvdListe->add(tempDiv);																// Om informasjonen er korrekt, legg divAvden tilbake i listen
			}else{																						// Om informasjonen ikke er korrekt
				divAvdListe->add(tempDiv);																// Legg divAvden tilbake i listen
				cout << "\nDet er noko feil med divisjonen";											// Skriv til bruker at det er noe feil med divisjonen
				return false;																			// Returner false
			}
		}else{																							// Om divisjonen ikke finnes i divAvdListen
			cout << "\nDenne divisjonen eksisterer ikke";												// Gi bruker beskjed om dette
			return false;																				// Og returner false
		}
	}
	return true;																						// Om ingenting er feil, returner true
}

void Idrett::divRef() {                                              //brukes til kommando L 

	divAvd* div;

	char avd[NVNLEN] = "";
	char fil[STRLEN] = "";
	std::string input;
	std::string inputt;

	cout << "Hvilken divisjon? ";
	input = les('n');										// Leser inn navnet
	input.copy(avd, NVNLEN);

	if (divAvdListe->inList(avd)) {

		cout << "Trykk enter for å skrive til skjerm eller skriv filnavn for å skrive til fil ";
		inputt = lesBlank('s');										// Leser inn navnet
		inputt.copy(fil, STRLEN);

		if (inputt.empty()) {									//hvis avd er ingenting blir den bare vist på sjerm
			cout << "\n\nTerminliste for " << avd << endl << endl;
			div = (divAvd*)divAvdListe->remove(avd);	 //div er foo objektet og foo forsvinn
			div->displayTerm();
			divAvdListe->add(div);
		}
		else {
			ofstream utfil(fil);
			div = (divAvd*)divAvdListe->remove(avd);	 //div er foo objektet og foo forsvinne
			div->termTilFil(utfil);
			divAvdListe->add(div);
		}
	}
	else {
		cout << "Denne idretten fins ikke!";
	}
}


void Idrett::tabell() {

	divAvd* tempDiv;                       // Hjelpepeker
	char ch = 'A';
	char div[NVNLEN] = "";
	char fil[STRLEN] = "";

	cout << "Trykk enter for å skrive for alle divisjoner, skriv inn navn på divisjon for å velge en spesifikk divisjon:  \n";
	std::string input = lesBlank('n');										// Leser inn navnet
	input.copy(div, NVNLEN);

	//const char *navn = input.c_str();

	if (input.empty()) {
		cout << "Trykk enter for å skrive til skjerm, skriv inn navn på fil for å skrive til fil:  \n";
		std::string inputt = lesBlank('s');										// Leser inn navnet
		inputt.copy(fil, STRLEN);

		if (inputt.empty()) {
			//for alle divisjoner skriv ut tabell til skjerm
			cout << "Tabell for alle divisjoner: \n\n";

			switch (tabelltype) {               //Kopierer tabelltype over i variabel som sendes med

			case 'A':
				ch = 'A';
				break;

			case 'B':
				ch = 'B';
				break;

			case 'C':
				ch = 'B';
				break;
			}

			for (int i = 1; i <= divAvdListe->noOfElements(); i++) {
				tempDiv = (divAvd*)divAvdListe->removeNo(i);                //Løkke som kaller for alle div i idretten
				tempDiv->tabellTilSkjerm(ch);
				divAvdListe->add(tempDiv);
			}
		}

		else {

			//for alle divisjoner skriv ut tabell til fil
			cout << "Skriver tabell for alle divisjoner til fil " << inputt;

			switch (tabelltype) {               //Kopierer tabelltype over i variabel som sendes med

			case 'A':
				ch = 'A';
				break;

			case 'B':
				ch = 'B';
				break;

			case 'C':
				ch = 'B';
				break;
			}

			for (int i = 1; i <= divAvdListe->noOfElements(); i++) {
				tempDiv = (divAvd*)divAvdListe->removeNo(i);                //Løkke som kaller for alle div i idretten
				tempDiv->tabellTilFil(ch, fil);
				divAvdListe->add(tempDiv);
			}
		}
	}

	else if (divAvdListe->inList(div)) {

		cout << "Trykk enter for å skrive til skjerm, skriv inn navn på fil for å skrive til fil:  \n";
		std::string inputtt = lesBlank('s');										// Leser inn navnet
		inputtt.copy(fil, STRLEN);

		if (inputtt.empty()) {
			switch (tabelltype) {               //Kopierer tabelltype over i variabel som sendes med

			case 'A':
				ch = 'A';
				break;

			case 'B':
				ch = 'B';
				break;

			case 'C':
				ch = 'B';
				break;
			}
			divAvd* temp = (divAvd*)divAvdListe->remove(div);
			temp->tabellTilSkjerm(ch);
			divAvdListe->add(temp);
		}
		else {
			cout << "Skriver divisjon " << input << " til filnavn " << inputtt;
			switch (tabelltype) {               //Kopierer tabelltype over i variabel som sendes med

			case 'A':
				ch = 'A';
				break;

			case 'B':
				ch = 'B';
				break;

			case 'C':
				ch = 'B';
				break;
			}
			tempDiv = (divAvd*)divAvdListe->remove(div);                //Løkke som kaller for alle div i idretten
			tempDiv->tabellTilFil(ch, fil);
			divAvdListe->add(tempDiv);
		}
	}


	else {                                                    //Feilmelding hvis navnet ikke finnes i listen
		cout << "Divisjonen finnes ikke";
	}
}

