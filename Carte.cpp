#include "Carte.h"

Carte::Carte() {
	CImg<float> image = CImg<float>(1, 1, 0, 1);
	int valeur = 0;
	char caracteristique = 'o';
	int couleur = 0;
	int positionX = 0;
	int positionY = 0;
}

Carte::Carte(CImg<float> image, int valeur, char caracteristique, int couleur)
{
	image_ = image;
	valeur_ = valeur;
	caracteristique_ = caracteristique;
	couleur_ = couleur;
}

Carte::~Carte()
{
}


