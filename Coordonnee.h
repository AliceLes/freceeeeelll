#pragma once
#pragma once


#include "CImg.h"
using namespace cimg_library;
#include <iostream>
using namespace std;




class Coordonnee

{
	int valeurX_;
	int valeurY_;
	int  tabRemplissage_[17];


public:

	Coordonnee( int tabRemplissage[17], int valeurX = 0, int valeurY = 0 );
	~Coordonnee();



	int saisie1();		//renvoie n� carte associee au click si autoris� pour un click n�1  :: il faudrait un tableau qui associe � chaque n� de carte l'emplacement o� afficher carte correspondante utilisable par la classe Partie
	int saisie2();
	int quit();

};