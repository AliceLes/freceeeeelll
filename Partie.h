#pragma once
#include "CImg.h"
using namespace cimg_library;
#include <iostream>
#include<fstream>
using namespace std;
#include "Carte.h"
#include <vector>

#include "Coordonnee.h"
#include<fstream>


/*									//deja dans Carte.h
#include "CImg.h"
using namespace std;
using namespace cimg_library;
*/


class Partie
{
	Carte jeuDeCartes_[54];				//ensemble des cartes � jouer	52 + bleu + vide + rouge
	int miniMemoire_[17];				//vision r�duite de l'occupation du plateau -> reserve + 8 colonnes + 4 sorties + 4 reserves (pour saisie 1 ds reserve)
	int memoirePartie_[20][8];			//memoire du plateau de jeu
	CImg<unsigned char>* scene_;		//environnement visuel
	CImgDisplay* disp_;					//fenetre d'affichage
	

public:

	Partie();			// constructeur sans param�tre pour d�buter une nouvelle partie 
	~Partie();

	
	void setJeuDeCartes();
	void setMemoirePartie();
	void setMiniMemoire();   // {  miniMemoire_[17] = { 0,  7,7,7,7,6,6,6,6,  0,0,0,0,   0,0,0,0}; }
	void setScene();
	void setDisp();
	


	//void setMemoirePartie(tableau);// pour reprendre une partie en cours

	int attendClick();
	int attendDeclick();

	void affiche();

	bool estDeplacementValide(int num1, int num2);			//"coordonn�es" des cartes dans mini partie methode fait des tests sur les caracteristiques des cartes � d�placer
	void deplacement(int num1, int num2);					//d�place en m�moire et dans l'affichage les cartes


	void afficherPartie();						//affiche tout tableau m�moire 
	void afficherGagner();
	void sauvegarderPartie();
	void chargerPartie();


};