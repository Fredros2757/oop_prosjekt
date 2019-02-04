#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

#include "lag.h"

extern Spillere spillere;

Lag :: Lag(){
  antSpillere = 0;
}

Lag :: Lag(char nvn[NVNLEN], char adr[STRLEN], int antallSpillere, ifstream & inn){		// Constructor som blir brukt når lag leses inn fra fil

	int antNySpillere;
	int nr;
	char spillerAdresse[STRLEN];
	char spillerNavn[NVNLEN];

	navn = new char[strlen(nvn)+1];														// Oppretter ny char for navn
	strcpy(navn, nvn);																	// Kopierer nvn fra constructoren inn i navn
	adresse = new char[strlen(adr)+1];													// Oppretter ny char for adresse
	strcpy(adresse, adr); 																// Kopierer adr fra constructoren inn i adresse
	antSpillere = antallSpillere;														// Setter antSpillere til antallSpillere

	for (int i = 0; i < antSpillere; i++){												// For-loop som kjører like mange ganger som det er spillere
		inn >> spillerNr[i]; inn.ignore();												// Alle spillerNr er på samme linje, denne leser inn alle og setter hver enkelt inn i plass i
	}

	inn >> antNySpillere; inn.ignore();													// leser inn antall spillere som ikkje er registert, denne er hovedsakleg brukt i ny_div.dta, i idrettene.dta er denne alltid 0

	for (int i = 0; i < antNySpillere; i++){											// For-loop som looper like mange ganger som det er uregistrerte spillere
		inn >> nr; inn.ignore();														// Leser inn nr til spilleren, ignorerer blank
		inn.getline(spillerNavn, NVNLEN);												// Leser inn navnet til spilleren fra fil
		inn.getline(spillerAdresse, STRLEN);											// Leser inn adressen til spilleren fra fil
		if(!spillere.finnesSpiller(nr)){												// Om spillerNr ikke eksisterer fra før
			spillere.spillerFraDivAvd(spillerNavn, spillerAdresse, nr);					// Kaller spillerFraDivAvd-funksjonen hos spillere, sender med spillerNavn, spillerAdresse og nr
		}
		spillerNr[antSpillere] = nr;													// Legger spilleren til i listen over spillere på laget
		antSpillere++;																	// Øker antallSpillere med 1
	}
}

void Lag :: display(){																	// Displayfunksjonen til lag
  cout << "\nDette laget heter " << navn << "\n";										// Skriver ut navnet til laget
  cout << "Adressa til laget er: " << adresse << "\n";									// Skriver ut adressen til laget
  cout << "Laget har " << antSpillere << " spillere på laget\n";						// Skriver ut antall spillere på laget
  cout << "Desse spelar på laget: ";													
  for(int i = 0; i < antSpillere; i++){													// For-loop som skriver ut alle spillerNr'ene på laget
  	cout << spillerNr[i] << " ";
  }

  cout << "\n\n";

}


bool Lag :: sjekkNavn(char input[NVNLEN]){												// Sjekker om input er det samme som navnet på laget

	if(strcmp(input, navn) == 0){
		return true;																	// Returnerar true som det er det same
	}else{
		return false;																	// Returnerar false om det er ulikt
	}

}

void Lag :: endreSpillerstall(){														// Funksjon for å endre spillerstall

	char ch;																			// Hjelpefunksjon for å lagre ein char
	do {
		cout << "\nVil du (l)egge til, eller (f)jerne en spiller? ";						// Spør bruker om de vil legge til eller fjerne spiller
		cin >> ch; cin.ignore();															// Tar inn char fra bruker
		ch = toupper(ch);																	// Uppercaser ch
	} while (!(ch == 'L' || ch == 'F'));

	switch(ch){																			// Switch som enten legger til eller fjerner spiller
		case 'F': fjerneSpiller(); 	break;
		case 'L': leggeTil();		break;
		
	}
}

int Lag :: lesInt() {
	int nr;
	cout << "\nSkriv input: ";
	std::cin >> nr;
	while (std::cin.fail()) {
		std::cout << "Error: ikke et tall. prøv på nytt:" << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> nr;
	}
	return nr;
}

void Lag :: leggeTil(){																	// Funksjon som legger til spiller
	int spiller;																		// Hjelpevariabel som lagrer en int som er spillernr som skal legges inn
	bool finnes = false;																// Hjelpevariabel som lagrer en bool som er true om man finner spilleren i spillerarrayen

	cout << "\nHva er nummeret på spilleren du vil legge til? ";						// Spør brukeren om hvilken spiller som skal legges til
	spiller = lesInt();																		// Tar inn spillerNr fra bruker

	if(spillere.finnesSpiller(spiller)){												// Kaller finnesSpiller-funksjonen i spillere, for å finne ut om spilleren er i listen over alle spillere

		for (int i = 0; i < antSpillere; i++){											// For-loop som sjekker om spilleren allerede finnes blant spillerene på laget
			if(spillerNr[i] == spiller){												// Sjekker om spilleren på plass i har det samme nr som brukeren oppgav
				finnes = true;															// Om det finnes, setter finnes til true
			}
		}

		if(!finnes){																	// Om spilleren ikke finnes i listen over spillere på laget
			spillerNr[antSpillere] = spiller;											// Setter neste skuffe i arrayen til nummeret som spilleren oppgav
			antSpillere++;																// setter antallSpillere til antallSpillere + 1
			cout << "\nSpiller nr " << spiller << " er lagt til på laget";				// Skriver ut til bruker at spilleren er lagt til

		}else{
			cout << "\nDenne spilleren er allerede på laget: ";							// Feilmelding om spilleren allerede er på laget 
		}

	}else{
		cout << "\nDenne spilleren finnes ikke i spillerlisten";						// Feilmelding om spilleren ikke finnes i spillerlisten
	}	
}

void Lag :: fjerneSpiller(){															// Funksjon for å fjerne spiller fra arrayen med spillere på laget
	int spiller;																		// Hjelpevariabel som holder på brukerinput
	int posisjon;																		// Hjelpevariabel som holder på posisjonen til spilleren som skal fjernes i arrayen
	bool finnes = false;																// Hjelpevariabel som lagrer en bool som er true om man finner spilleren i spillerarrayen

	cout << "\nHva er nummeret på spillere du vil fjerne? ";							// Spør bruker om hvilken spiller som skal fjernes
	spiller = lesInt();																		// Tar inn brukerinput

	if(spillere.finnesSpiller(spiller)){												// Kaller finnesSpiller-funksjonen til spillere, for å finne ut om spilleren finnes i listen over alle spillerene
		for(int i = 0; i < antSpillere; i++){											// For-loop som sjekker om spilleren allerede finnes blant spillerene på laget
			if(spillerNr[i] == spiller){												// Sjekker om spilleren på plass i har samme nr som input
				finnes = true;															// Setter finnes til true
				posisjon = i;															// Setter posisjon til i
			}
		}

		if(finnes){																		// Om spilleren finnes i spiller-arrayen

			for (int i = posisjon; i < antSpillere; i++){								// For-loop som overskriver spilleren som skal fjernes, og flytter resten av arrayen et hakk frem
				spillerNr[i] = spillerNr[i+1];
			}
			spillerNr[antSpillere] = 0;													// tømmer den tidligere brukte skuffen
			antSpillere--;																// Setter antSpillere til antSpillere -1

			cout << "\nSpiller nr " << spiller << " er fjernet fra spillerlisten";		// Gir beskjed til brukeren om at spilleren er fjernet


		}else{
			cout << "\nDenne spilleren er ikke på laget";								// Gir beskjed om at spilleren ikke er på laget
		}
	}else{
		cout <<"\nDenne spilleren finnes ikke i spillerlisten";							// Gir beskjed om at spilleren ikke finnes i spillerlisten
	}

}

void Lag :: visData(){																	// Funksjon for å vise data for alle spillere på et lag

	int spiller;																		// Hjelpevariabel for å lagre en int

	for (int i = 0; i < antSpillere; i++){												// For-loop som looper gjennom spiller-arrayen
		spiller = spillerNr[i];															// Setter spiller til inten i skuffe nr i
		spillere.visSpiller(spiller);													// Kaller visSpiller hos spillere, sender med spiller som parameter
	}
}

void Lag :: lagTilFil(ofstream & ut){													// Funksjon for å skrive lag til fil
	ut << navn << endl;																	// Skriver navnet til laget til fil
	ut << adresse << endl;																// Skriver adressen til laget til fil
	ut << antSpillere << endl;															// Skriver antall spillere til fil
	for (int i = 0; i < antSpillere; i++){												// For-loop som looper like mange gonger det er spillere
		ut << spillerNr[i];																// Skriver ut nummer til fil
		if(i < antSpillere-1){															// Sjekker om nummeret som ble skrevet ut ikke er siste spiller
			ut << " ";																	// Om det er tilfellet, skriv mellomrom til fil
		}
	}
	ut << endl;																			// Skriver endline til fil
	ut << 0 << endl;																	// Skriver ut en 0 som alltid er der i idrettene.dta, tallet kan vere noko anna i ny_div.dta

}

void Lag :: printNavn(){																// Funksjon som skriver ut navnet til laget til skjerm
	cout << navn;										
}

void Lag :: navnTilFil(ofstream & ut){													// Funksjon som skriver ut navnet til laget til fil
	ut << navn;
}

void Lag::giPoeng(int i) {                                                              //Legger til poeng som brukes i tabell
	poeng += i;
}

int Lag::visPoeng() {                                                                   //Gjør poeng tilgjengelig i tabell
	return poeng;
}

void Lag::nullstillPoeng() {                                                            //Nullstiller poeng ved generering av ny tabell
	poeng = 0;
}

char* Lag::visNavn() {                                                                  //Gjør navn tilgjengelig i utskrift av tabell
	return navn;
}

void Lag::skrivPoeng() {                                                                //Brukes for å skrive tabell til skjerm
	cout << navn << "        " << poeng << "\n";
}

void Lag::skrivPoeng(ofstream &ut) {                                                    //Brukes for å skrive tabell til fil
	ut << navn << "         " << poeng << "\n";
}
