#pragma once


#include "CImg.h"
using namespace cimg_library;
#include <iostream>
using namespace std;



class Carte
{
	int valeur_;
	char caracteristique_;
	int couleur_; // 1,2,3,4 pique, coeurr, treffle, carreau
	CImg<float> image_;


public:

	Carte();
	Carte(CImg<float> image/* = CImg<float>(1,1,0,1)*/, int valeur = 0 , char caracteristique = 'o', int couleur = 0);	//on ne peut se passer de l'initialissation par défaut de l'image, pour créer un tableau d'images qui devront alors toutes être initialisées
	~Carte();

	int getValeur() { return valeur_; }
	char getCaracteristique() { return caracteristique_; }
	int getCouleur() { return couleur_; }
	CImg<float> getImage() { return image_; }
};