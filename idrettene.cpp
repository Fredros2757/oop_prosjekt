#define _SCL_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include <fstream>
#include <cctype>

using namespace std;

#include "idrettene.h"

//Constructor for liste over idretter
Idrettene :: Idrettene(){
	idrettListe = new List(Sorted);
}

//Skriver ut liste over idretter til skjerm
void Idrettene::display(){
	idrettListe->displayList();
}

void Idrettene :: nyIdrett(){							
	char navn[NVNLEN] = "";												// Variabel som mellomlagrer navnet på idretten					
	cout << "Hva er navnet på idretten du vil opprette?";			// Spør bruker om navnet
	std::string input = les('n');										// Leser inn navnet
	input.copy(navn, NVNLEN);
	if (input != "q") {
		if (!idrettListe->inList(navn)) {									// Sjekker om ein idrett med det same navnet allereie eksisterar 
			Idrett* nyIdrett;											// Om det ikkje eksisterar, opprettar det ein ny idrett og puttar det i lista
			nyIdrett = new Idrett(navn);
			idrettListe->add(nyIdrett);
			skrivTilFil();

		}
		else {															// Om idretten allereie eksisterar, skriv ut feilmelding til brukaren som varslar om dette
			cout << "Denne idretten eksisterer allerede!\n";
		}
	}
	else {
		cout << "Avbryter..";
	}
}

void Idrettene :: nyDivisjon(){													// Funksjon for å lese inn ny divAvd
	char navn[NVNLEN] = "";

	Idrett* hjelpeIdrett;														// Hjelpepeker

	if(!idrettListe->isEmpty()){												// Sjekker om idrettlisten inneholder noe
		
		cout << "I hvilken idrett vil du legge til en ny divisjon? ";			// Spør bruker om hvilken idrett man skal legge til ny divAvd
		std::string input = les('n');										// Leser inn navnet
		input.copy(navn, NVNLEN);
		if (input != "q") {
			if (idrettListe->inList(navn)) {											// Sjekker om idretten eksisterer
				hjelpeIdrett = (Idrett*)idrettListe->remove(navn);					// Henter idretten
				hjelpeIdrett->nyDiv();												// Kaller nyDiv-funksjonen innad i divAvd-objektet
				idrettListe->add(hjelpeIdrett);
			}
			else {
				cout << "Fant ingen idrett med dette navnet";
			}
		}
		else {
			cout << "Avbryter..";
		}
	}
	else{
		cout << "\nDet finnes ingen idretter!";									// Feilmelding om idretten ikke finnes
	}
}

void Idrettene :: fjernIdrett(){
	char navn[NVNLEN] = "";
	char ch = ' ';																	// Variablar for å lagre navn og ch

	if (!idrettListe->isEmpty()) {
		cout << "Hvilken idrett vil du fjerne?";									// Spør brukaren om kva for ein idrett som skal fjernast
		std::string input = les('n');										// Leser inn navnet
		input.copy(navn, NVNLEN);
		if (input != "q") {
			if (idrettListe->inList(navn)) {												// Sjekker om idretten eksisterar
				do {
					cout << "\nEr du sikker på at du vil fjerne denne idretten? (y/n): ";		// Spør om brukaren verkeleg vil fjerne denne idretten
					cin >> ch; cin.ignore();
				} while (!(ch == 'y' || ch == 'n'));
				if (ch == 'y') {
					idrettListe->destroy(navn);										// Om input er y, fjern og ødelegg elementet fra lista
					cout << "\nIdretten " << navn << " ble slettet";
				}
				else if (ch == 'n') {
					cout << "\nIdretten ble ikke slettet";							// Om input er n, skriv ut melding om at elementet ikkje ble sletta
				}
			}
			else {
				cout << "\nDenne idretten finnes ikke";									// Om idretten ikkje finnst, skriv ut feilmelding om dette
			}
		}
		else {
			cout << "Avbryter..";
		}
	}
	else {
		cout << "Det finnes ingen idretter i lista";
	}
}

void Idrettene :: fjernDivAvd(){												// Funksjon for å fjerne DivAvd
	char navn[NVNLEN] = "";															// Variabel for å holde på navn
	Idrett* tempIdrett;															// Hjelpepeker

	cout << "\nI hvilken idrett vil du fjerne en divisjon/avdeling? ";			// Bruker får spørsmål om i hvilken idrett man skal fjerne en idrett
	std::string input = les('n');										// Leser inn navnet
	input.copy(navn, NVNLEN);
	if (input != "q") {
		if (idrettListe->inList(navn)) {												// Sjekker om idretten eksisterar
			tempIdrett = (Idrett*)idrettListe->remove(navn);						// Tar ut idretten fra listen
			tempIdrett->fjernDivAvd();												// Kaller fjernDivAvd-funksjonen i idrett-objektet
			idrettListe->add(tempIdrett);											// Legger idretten tilbake til listen
		}
		else {
			cout << "\nDenne idretten finnes ikke";									// Feilmelding om idretten ikke finnes
		}
	}
	else {
		cout << "Avbryter..";
	}
}

void Idrettene :: endreData(){													// Funksjon for å endre spillerarray hos et lag

	char navn [NVNLEN] = "";															// Hjelpefunksjon som holder på en chararray
	Idrett* tempIdrett;															// Hjelpepeker

	cout << "\nI hvilken idrett spiller spilleren du vil endre? ";				// Spør bruker om idrett
	std::string input = les('n');										// Leser inn navnet
	input.copy(navn, NVNLEN);
	if (input != "q") {
		if (idrettListe->inList(navn)) {												// Sjekker om idretten eksisterar
			tempIdrett = (Idrett*)idrettListe->remove(navn);						// Fjerner idretten fra idrettlisten
			tempIdrett->endreSpiller();												// Kaller endreSpiller-funksjonen hos Idrett
			idrettListe->add(tempIdrett);											// Legger idretten tilbake til listen
		}
		else {
			cout << "\nDenne idretten finnes ikke";									// Skriver feilmelding om idretten ikke finnes 
		}
	}
	else {
		cout << "Avbryter..";
	}
}

void Idrettene :: spillerData(){												// Funksjon for å skrive ut all data om spillere på et lag
	char navn [NVNLEN] = "";															// Hjelpevariabel som holder på en char-array
	Idrett* tempIdrett;															// Hjelpepeker

	cout << "\nOppgi idrett ";					 								// Spør bruker om idrett
	std::string input = les('n');				         						// Leser inn navnet
	input.copy(navn, NVNLEN);
	if (input != "q") {
		if (idrettListe->inList(navn)) {												// Sjekker om idretten eksisterar
			tempIdrett = (Idrett*)idrettListe->remove(navn);						// Fjerner idretten fra listen
			tempIdrett->visData();													// Kaller visData-funksjonen til Idrett
			idrettListe->add(tempIdrett);											// Legger idretten tilbake til listen
		}
		else {
			cout << "\nDenne idretten finnes ikke";									// Skriver feilmelding til bruker om idretten ikke finnes
		}
	}
	else {
		cout << "Avbryter..";
	}
}

void Idrettene :: visRes(){														// Funksjon for å finne resultater

	char navn [NVNLEN] = "";															// Hjelpevariabel som holder på en char-array
	Idrett* hjelpeIdrett;														// Hjelpepeker

	cout << "\nOppgi idrett ";													// Spør bruker etter idrett
	std::string input = les('n');	           									// Leser inn navnet
	input.copy(navn, NVNLEN);
	if (input != "q") {
		if (idrettListe->inList(navn)) {												// Sjekker om idretten eksisterer
			hjelpeIdrett = (Idrett*)idrettListe->remove(navn);						// Fjerner idretten fra listen
			hjelpeIdrett->visResultater();											// Kaller visResultater-funksjonen hos Idrett
			idrettListe->add(hjelpeIdrett);											// Legger idretten tilbake i Listen
		}
		else {
			cout << "\nDenne idretten finnes ikke";									// Skriver feilmelding til bruker om idretten ikke finnes
		}
	}
	else {
		cout << "Avbryter..";
	}
}

void Idrettene :: vis(){														// Funksjon for å vise idretter

	char navn[NVNLEN] = "";															// Variabel som held på input

	Idrett* hjelpeIdrett;														// Hjelpepeker 

	std::string input = lesStille('n');	           									// Leser inn navnet
	input.copy(navn, NVNLEN);
	if (input != "q") {
		if ((input == "a") || (input == "A")) {					// Sjekker om brukerinput er a eller A
			if (!idrettListe->isEmpty()) {											// Sjekker om det er elementer i idrettslisten
				idrettListe->displayList();											// Kaller displayList-funksjonen i listTool
			}
			else {
				cout << "Det finnes ingen idretter";								// Feilmelding om det ikke finnes idretter
			}
		}
		else if (idrettListe->inList(navn)) {										// Sjekker om den ønskede idretten finnes
			hjelpeIdrett = (Idrett*)idrettListe->remove(navn);						// Henter ut ønsket idrett fra listen
			hjelpeIdrett->displayAll();												// Kaller displayAll-funskjonen i idretts-objektet
			idrettListe->add(hjelpeIdrett);											// Legger idretten tilbake i listen
		}
		else {
			cout << "Det finst ingen idrett med dette navnet\n";					// Feilmelding om idretten ikke finnes
		}
	}
	else {
		cout << "Avbryter..";
	}
}

void Idrettene :: lesIdrettFraFil(){											// Funksjon for å lese inn idretter fra fil
	int antallIdretter;															// Hjelpevariabel for å holde på en int

	ifstream innfil("IDRETTENE.dta");												// Leser inn filen Idrett.dta

	if(innfil){																	// Sjekker om filen eksisterer
		cout << "\nLeser inn idretter fra fil...\n";
		innfil >> antallIdretter;												// Leser inn første linje i filen, som sier hvor mange idretter som skal leses inn
		innfil.ignore();														// Ignorerer blank

		for (int i = 0; i < antallIdretter; i++){								// For-loop som kjører så mange ganger som det er idretter som skal leses inn

			char tabell;														// Hjelpevariabel til å holde på en char, som sier hvilken tabelltype idretten skal ha
			char navn[NVNLEN];													// Hjelpevariabel til å holde på navnet til idretten
			int antallDiv;														// Hjelpevariabel til å holde på antall divisjoner idretten har

			innfil.getline(navn, NVNLEN);										// Leser inn linjen som inneholder navnet til idretten
			innfil >> tabell; innfil.ignore();									// Leser inn linjen som inneholder tabelltype, ignorerer blank
			innfil >> antallDiv; innfil.ignore();								// Leser inn linjen som inneholder antall divisjoner, ignorerer blank

			Idrett* tempIdrett;													// Hjelpepeker

			tempIdrett = new Idrett(navn, tabell, antallDiv, innfil);			// Oppretter ny Idrett, sender med navnet, tabelltypen, antall divisjoner og innfil

			idrettListe->add(tempIdrett);										// Legger den nye idretten til i listen over idretter


		}

		antIdrett = antallIdretter;												// setter antIdrett til antallIdretter

	}else{
		cout << "\nKunne ikkje finne filen Idrett.dta";							// Feilmelding om Idrett.dta ikke eksisterer
	}
}

void Idrettene :: skrivTilFil(){												// Funksjon for å skrive idretter til fil

	Idrett* hjelpeIdrett;														// Hjelpepeker

	ofstream utfil("IDRETTENE.dta");												// Åpner filen/oppretter filen

	utfil << idrettListe->noOfElements() << endl;								// Skriver antallet idretter til fil

	for (int i = 1; i <= idrettListe->noOfElements(); i++){						// For-loop som looper like mange ganger som det er idretter
		hjelpeIdrett = (Idrett*)idrettListe->removeNo(i);						// Tar ut idrett fra listen

		if(hjelpeIdrett){														// Om hjelpeidrett ikke er nullpeker
			hjelpeIdrett->idrettTilFil(utfil);									// Kjører idrettTilFil-funksjonen i Idrett
			idrettListe->add(hjelpeIdrett);										// Legger idretten tilbake til idrettListen
		}
	}

}

bool Idrettene :: sjekkFeil(bool feil){											// Funksjon som leser inn resultater.dta og sjekker om den inneholder feil

	int antIdr;																	// int som holder på antall idretter
	char navn[NVNLEN];															// chararray som holder på navnet til idretten
	Idrett* tempIdrett;															// Hjelpepeker

	ifstream innfil("RESULTAT.dta");											// Åpner resultater.dta
	if(innfil){																	// Om innfil eksisterer
		innfil >> antIdr; innfil.ignore();										// Leser inn antall idretter fra fil

		for (int i = 0; i < antIdr; i++){										// For-loop som looper gjennom alle idrettene
			innfil.getline(navn, NVNLEN);										// Leser inn navnet til idretten fra fil
			if(idrettListe->inList(navn)){										// Sjekker om idretten finnes i idrettListen
				tempIdrett = (Idrett*)idrettListe->remove(navn);				// Fjerner idretten fra listen
				if(tempIdrett->sjekkDiv(innfil, feil)){							// Sjekker om det er noe feil med idretten, ved å kalle sjekkDiv-funksjonen i Idrett-objektet
					idrettListe->add(tempIdrett);								// Om det ikke er noen feil, legg idretten tilbake i listen

				}else{															// Om det er feil i filen
					cout << "\nDet er noe feil med idretten";					// Skriver at det er noe feil med idretten til bruker 
					idrettListe->add(tempIdrett);								// Legger tilbake idretten i idrettListen
					return false;												// Returnerer false
				}

			}else{																// Om idretten ikke finnes i idrettListen
				cout << "\nDenne idretten finnes ikke";							// Skriver dette til bruker
				return false;													// Returnerer false
			}
		}
	}else{																		// Om filen ikke finnes
		cout << "\nDenne filen finnes ikke!";									// Skriver dette til bruker
		return false;															// Returnerer false
	}
	return true;																// Om ingen feil er funnet, returnerer true
}

void Idrettene::skrivTermList() {
	Idrett* idrett;

	char idr[NVNLEN] = "";

	cout << "Hvilken idrett vil du se terminlisten til? ";

	std::string input = les('n');								         		// Leser inn navnet
	input.copy(idr, NVNLEN);
	if (input != "q") {
		if (idrettListe->inList(idr)) {
			idrett = (Idrett*)idrettListe->remove(idr);
			idrett->divRef();
			idrettListe->add(idrett);							          		// Fjerner divisjonen fra lista
		}
		else {
			cout << "Denne idretten fins ikke!\n";
		}
	}
	else {
		cout << "Avbryter..";
	}
}

void Idrettene::tabell() {
	char navn[NVNLEN] = "";															// Hjelpefunksjon som holder på en char-array
	Idrett* tempIdrett;															// Hjelpepeker

	cout << "\nOppgi idrett: ";													// Spør bruker om idrett
	std::string input = les('n');								         		// Leser inn navnet
	input.copy(navn, NVNLEN);
	if (input != "q") {
		if (idrettListe->inList(navn)) {
			tempIdrett = (Idrett*)idrettListe->remove(navn);						// Fjerner idretten fra listen
			tempIdrett->tabell();										        	// Kaller visData-funksjonen til Idrett
			idrettListe->add(tempIdrett);									    	// Legger idretten tilbake til listen
		}
		else {
			cout << "Denne idretten finnes ikke";
		}
	}
	else {
		cout << "Avbryter..";
	}
}



