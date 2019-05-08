#include "Coordonnee.h"

#include <iostream>
using namespace std;

Coordonnee::Coordonnee( int tabRemplissage[17] , int valeurX, int valeurY)
{
	valeurX_ = valeurX;
	valeurY_ = valeurY;
	for (int i = 0; i < 17; i++) {
		tabRemplissage_[i] = tabRemplissage[i];
	}
}


Coordonnee::~Coordonnee()
{
}

int Coordonnee::quit() {
	if (valeurX_ > 350) {
		return(1);
		}
		else
			return(0);	
}




int Coordonnee::saisie1()
{

	if (valeurX_ > 800) {												//action hors jeu sauvegarde-chargement-nouvelle partie
		if (valeurY_ > 400) {				//nouvelle partie
			cout << "vous voulez recommencer une partie" << endl;
			return(-4);					
			
		}
		else if (valeurY_ > 200) {			//charger
			cout << "vous voulez charger la derniere partie sauvegardee" << endl;
			return(-3);				
		}
		else {								//sauvegarder
			cout << "vous voulez sauvegarder cette partie" << endl;
			return(-2);					
			
		}
	}
	else {																//déplacement 1ere saisie

		if (valeurY_ <= 100) {														//soit réserve soit sortie et alors non
			if (50 < valeurX_ && valeurX_ < 330) {									//reserve
				cout << endl << "vous avez clique sur la reserve" << endl;
				int i = ((valeurX_ - 50) * 4) / 286;
				cout << "a l'emplacement " << i << endl;
				if (tabRemplissage_[i + 8 + 1] == 1) {
					cout << "il y a une carte à cette place" << endl;
					return (i); // n° carte de la reserve en comptant dans le tableau
				}
				else {																//tapis ou sortie
					//cout << "il n'y a pas de carte à cette place" << endl;
					return(-1);
				}
			}
			else {
				//cout << endl << "vous n'avez pas clique dans une zone de cartes valide pour un 1er click" << endl;
				return(-1); //pas de carte
			}
		}
		else {		//ici appel au tableau résumé des remplissages du jeu
			int numColonne = valeurX_ / 100;
			cout << endl << "vous avez clique sur la colonne numero " << numColonne << endl;
			int nbCarte = tabRemplissage_[numColonne + 1];
			if (nbCarte >= 1) {									//la colonne n'est pas vide
				cout << endl << "cette colonne contient " << nbCarte << "carte-s" << endl;
				cout << "carte associee : " << nbCarte * 8 + numColonne;			//derniere carte non nulle si colonne  	//1ere ligne pour depot et sortie 
				return (nbCarte * 8 + numColonne);		//num derniere carte de la colonne  
			}
			else return (-1);			//pas de carte dans la  colonne
		}
	}
}






// on modifie pour que la fonction renvoie [0 si reserve,: plus mnt ] 4 si sortie , nbCol si Colonne -10-nbCol si colonne vide			[-> mais du coup ne permet pas tab coordonnées d'affichage]  [plus emplacement ds réserve exactement ni spécificité si colonne vide]

int Coordonnee::saisie2()
{
	cout << "pos 1 :    x :  " << valeurX_ << "    y :  "<< valeurY_ << endl;
	cout << (50 < valeurX_) << endl << (valeurX_ < 330) << endl;
	if (valeurY_ <= 100) {													//soit réserve soit sortie		
		if (50 < valeurX_ && valeurX_ < 330) {								//réserve	//    ->   ici appel au tableau résumé des remplissages du jeu
			cout << endl << "vous avez clique sur la reserve" << endl;
			int i = ((valeurX_ - 50) * 4) / 286;					//280 ?
			cout << "a l'emplacement " << i << endl;
			if (tabRemplissage_[i + 8 + 1] == 1) {							//case déjà pleine
				cout << "il y a une carte à cette place" << " mais on va chercher ailleurs dans la reserve ...on ne sait jamais " << endl;
				if (tabRemplissage_[0] < 4) {									//il reste au moins une place dans la reserve
					int j = 0;
					while (j < 4 && tabRemplissage_[9 + j] != 0) {
						j += 1;
					}
					if (j == 5)
						cout << "il y a une erreur, incoherence dans le mini tableau de remplissage" << endl;
					else {
						cout << "on vous a trouve une place en " << j << endl;
						return(j);				//contrebalancer le "j+=1"
					}
				}
				else {															//plus de place en reserve
					cout << " dommage, tout est plein.." << endl;
					cout << "vous n'avez pas clique dans une zone de cartes valide pour un 2e click" << endl;
					return(-1);
				}
			}
			else {
				//cout << "...sur une case vide c'est bien !" << endl;
				return(i);
			}
		}
		else if (450 < valeurX_ && valeurX_ < 730) {												//sortie
			cout << endl << "vous avez clique dans la sortie" << endl;
			return(4); //-> code pour sortie, on determinera ensuite quelle couleur plus specifiquement
		}
		else {
			return(-1);
			//cout << "vous n'avez pas clique dans une zone de cartes valide " << endl;
		}
	}
	else {		//jusqu'ici potentiellement ok, (on n'applique pas les regles specifiques aux caracteriqtiques des cartes) quelle que soit la valeur dans tableau résumé des remplissages du jeu
		int numColonne = valeurX_ / 100;
		cout << endl << "vous avez clique sur la colonne numero " << numColonne << endl;
		int nbCarte = tabRemplissage_[numColonne + 1];
		if (nbCarte >= 1) {
			cout << endl << "cette colonne contient " << nbCarte << "carte-s" << endl;
			cout << "carte associee : " << (nbCarte) * 8 + numColonne;			//derniere carte non nulle si colonne  	//1ere ligne pour depot et sortie 
			return ((nbCarte) * 8 + numColonne);		//
		}
		else return (-10 - numColonne);			//pas de carte dans la colonne -> code pour dire colonne n°[-x-10]
	}

}

