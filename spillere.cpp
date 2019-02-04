#define _SCL_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string.h>
#include <string>

using namespace std;

#include "spillere.h"
#include "funksjoner.h"


Spillere :: Spillere(){
  sisteNr = 1;
  spillerListe = new List(Sorted);
}

void Spillere :: lesFraFil(){										
	int antallSpillere;														//Hjelpevariabel

	ifstream innfil("SPILLERE.dta");								

	if(innfil){																//Sjekker om spillere.dta finnes
			cout << "Leser inn spillere fra fil...\n";
			innfil >> antallSpillere;										//Antall spillere i fila står øverst, lagrer dette for å finne ut hvor mange ganger for loopen skal kjøre
			innfil.ignore();												//Ignorerer blank
		for(int i = 0; i < antallSpillere; i++){							// For-loop, kjører antallSpillere ganger
			int spillerNr;													//Variabler for å midlertidig lagre info
			char navn[NVNLEN];
			char adresse[STRLEN];

			innfil >> spillerNr;											//første linja for hver spiller har spillernr
			innfil.ignore();												//Ignorerer blank
			innfil.getline(navn, NVNLEN);									//andre linja for hver spiller har navn
			innfil.getline(adresse,STRLEN);									//tredje linja for hver spiller har adresse

			Spiller* nySpiller;												//Oppretter spiller-peker

			nySpiller = new Spiller(spillerNr, navn, adresse);				//Oppretter nytt spiller-objekt

			spillerListe->add(nySpiller);									//Legger det nye objektet til i lista over spillere
			if (spillerNr > sisteNr){										//Sjekker om spillerNr er større enn sisteNr, slik at sisteNr alltid er det siste brukte nummeret
				sisteNr = spillerNr;
			}

		}

		sisteNr++;															//Etter for-loopen, auk sisteNr med ein. 
	}else{
		cout << "Filen  SPILLERE.dta finnes ikke";									//Feilmelding om filen ikkje finst
	}
}

bool Spillere :: finnesSpiller(int nr){										// Funksjon som sjekker om en spiller finnes i listen
	if(spillerListe->inList(nr)){
		return true;
	}else{
		return false;
	}
}

void Spillere :: spillerFraDivAvd(char nvn[NVNLEN], char adr[STRLEN], int nr){
	Spiller* nySpiller;
	nySpiller = new Spiller(nr, nvn, adr);
	spillerListe->add(nySpiller);
	if(nr > sisteNr){
		sisteNr = nr;
	}
	sisteNr++;
}

void Spillere :: nySpiller(){												//Funksjon for å opprette ny spiller
	Spiller* nySpiller;														//Spiller-peker
	nySpiller = new Spiller(sisteNr);										//Oppretter nytt spiller-objekt, der sisteNr blir sendt med som argument
	spillerListe->add(nySpiller);											//Legger objektet til i spillerlista
	sisteNr++;																//Auker sisteNr med en. 
}

string Spillere::lesStille(char type) {

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

void Spillere :: vis(){
	char inputt[NVNLEN] = "";														//Hjelpevariablar
	int nr;
	Spiller* hjelpeSpiller;
	bool fantSpiller = false;
	
	std::string input = lesStille('n');	           									// Leser inn navnet
	input.copy(inputt, NVNLEN);

	if (input != "q") {     
		if ((input == "a") || (input == "A")) {				            	// Sjekker om brukerinput er a eller A
			if (!spillerListe->isEmpty()) {										// Om spillerlista ikkje er tom
				spillerListe->displayList();									// Kaller displayList-funksjonen til List

			}
			else {

				cout << "Listen er tom\n";
			}

		}
		else if (isdigit(inputt[0])) {											//Sjekker om den første char'en i input er eit nummer
			nr = atoi(inputt);													//om det er tilfellet, så blir inputen gjort om til int
			if (spillerListe->inList(nr)) {										//Sjekkar om det er et element i listen med denne ID'en
				spillerListe->displayElement(nr);								//Om det er tilfellet, så blir elementet med ønsket ID displayet
			}
			else {

				cout << "Det finnes ingen spiller med dette nummeret\n";		//Feilmelding. om elementet ikke finnes

			}

		}
		else {

			cout << "Skriver ut alle spillere med navnet " << inputt << "\n";

			for (char *iter = inputt; *iter != '\0'; ++iter)
			{
				*iter = tolower(*iter);
				++iter;
			}

			for (int i = 0; i <= sisteNr; i++) { 									//For-loop som sjekkar loopar sisteNr gonger

				hjelpeSpiller = (Spiller*)spillerListe->remove(i);				//fjernar element i frå lista og gjer det om til ein peikar
				if (hjelpeSpiller) {												//Sjekkar om elementet eksisterar eller er ein nullpointer
					if (hjelpeSpiller->sjekkNavn(inputt)) {						//Kallar sjekknavn-funksjonen til spiller-objektet
						fantSpiller = true;										//Om det returnerar true, så setter den fantSpiller til true
						hjelpeSpiller->display();								//Og kallar display-funksjonen til spiller
					}
					spillerListe->add(hjelpeSpiller);							//Legger objektet attende i lista
				}
			}
			if (fantSpiller == false) {
				cout << "Fant ingen spiller med navnet " << inputt << "\n";		//Feilmelding om ingen spillere med ønsket navn ble funnet
			}

			delete hjelpeSpiller;
		}
	}
	else {
		cout << "Avbryter..";
	}
}

void Spillere :: skrivTilFil(){

	int antallSpillere = spillerListe->noOfElements();						//Sjekkar kor mange element det er i spillerlista
	Spiller* hjelpeSpiller;
	
	ofstream utfil ("SPILLERE.dta"); 										//Opnar/opprettar spillere.dta

	utfil << antallSpillere << endl;

	for(int i = 0; i < sisteNr; i++){
		hjelpeSpiller = (Spiller*)spillerListe->remove(i);
		if(hjelpeSpiller){
			hjelpeSpiller->tilFil(utfil);
			spillerListe->add(hjelpeSpiller);
		}
		
	}
}

int Spillere::lesInt() {
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


void Spillere :: fjernSpiller(){

	int spiller;															//Hjelpevariabel

	if(!spillerListe->isEmpty()){

		cout << "Skriv inn nr til spilleren du vil fjerne fra lista\n";
		spiller = lesInt();							             			//Les inn spillernr
		if(spillerListe->destroy(spiller)){									//Sjekker om element med ID spiller eksisterer, fjerner den om det er tilfellet
			cout << "Spilleren ble fjernet fra listen\n";					//Output om spiller ble fjernet
		}else{
			cout << "Denne spilleren eksisterer ikke";						//Output om spiller ikke eksisterte, og dermed ikke ble fjernet
		}

	}else{
		cout << "Det finnes ingen spillere i lista";						// Skriver ut feilmelding om listen er tom
	}

}


void Spillere :: visSpiller(int nr){										// Funksjon som skriver ut data om en enkelt bruker

	spillerListe->displayElement(nr);										// Kaller displayElement-funksjonen hos spillerLister, med nr som input

}






