#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <string>

using namespace std;

#include "spiller.h"

Spiller :: Spiller(){

}


Spiller::Spiller(int x) : NumElement(x) {

	/*getliner nvn fra spiller.h, navn blir så lengden av nvn
	og nvn kopiert over til navn, ingen ekstra plass sløst*/
	char navnn[NVNLEN] = "";
	char adressee[STRLEN] = "";


	cout << "Skriv navn til spiller: ";
	std::string input = les('n');	           									// Leser inn navnet
	input.copy(navnn, NVNLEN);
	navn = new char[strlen(navnn) + 1];
	strcpy(navn, navnn);


		//samme her
	cout << "Skriv adresse til spiller: ";
	std::string inputt = les('s');	           									// Leser inn navnet
	inputt.copy(adressee, STRLEN);
	adresse = new char[strlen(adressee) + 1];
	strcpy(adresse, adressee);
}

Spiller :: Spiller(int x, char nvn[NVNLEN], char adr[STRLEN]): NumElement(x){		//konstruktor som leser inn alle data som argument
	navn = new char[strlen(nvn) +1];	
	strcpy(navn, nvn);
	adresse = new char[strlen(adr) +1];
	strcpy(adresse, adr);

}

void Spiller :: display(){
  cout << "Nr." << number << ": " << navn << ", " << adresse <<"\n";
}

bool Spiller :: sjekkNavn(char input[STRLEN]){	//Funksjon som sjekkar om input er det same som namnet til objektet
	
	char *navnlower = (char*)malloc(strlen(navn) + 1);
	strcpy(navnlower, navn);                             //Lager en kopi av navn
	
	for (char *iter = navnlower; *iter != '\0'; ++iter)
	{
		*iter = tolower(*iter);                          //Gjør kopien til lowercase for sammenligning
		++iter;
	}
	
	if(strcmp(input, navnlower) == 0){
		return true;															//Returnerar true som det er det same
	}else{
		return false;															//Returnerar false om det er ulikt
	}
	free(navnlower);
}

string Spiller::les(char type) {

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

void Spiller :: tilFil(ofstream & ut){
	ut << number << endl;
	ut << navn << endl;
	ut << adresse << endl;
}



//void Spiller::lesFraFil(ifstream & inn) {

	/*filformatet er
	-number
	-navn
	-adresse
	så bare økes spillerNr per loop*/

	//while (inn)
	//while (!eof)
		//{
	//		inn >> number;
	//		inn.ignore;
	//		inn.getline(nvn, NVNLEN);
	//		navn = new char[stlen(nvn) + 1];
	//		++sisteNr;
	//	}
//}

// void Spiller::skrivTilFil(ofstream & ut) {
//	ut << number << endl
//	 << navn << endl
//	<< adresse << endl;

//} 