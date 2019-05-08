#include "Partie.h"



Partie::Partie()
{
	//on initialise tous les champs :

	setJeuDeCartes();	
	setMemoirePartie();
	setMiniMemoire();		
	setScene();
	setDisp();

	// on entre dans le déroulement d'une partie :

	int numero = -1;
	int numero2 = -1;


	// Main loop, exit if the display window is closed or if ESC or Q key is hit :

	while (!disp_->is_closed() && !disp_->is_keyESC() && !disp_->is_keyQ() /*&& (miniMemoire_[13]!=13 || miniMemoire_[14] != 13 || miniMemoire_[15] != 13 || miniMemoire_[16] != 13)*/ && !(miniMemoire_[13] == 13 || miniMemoire_[14] == 13 || miniMemoire_[15] == 13 || miniMemoire_[16] == 13) ) {		//la partie n'est pas gagnée

		scene_->display(*disp_);			//on affiche la scène
		
		// on attend que l'utilisateur agisse avec un clique ou click et glisse ici

		numero=attendClick();				//1ere saisie 
		numero2 = attendDeclick();			//"2e saisie"


		//on teste le click :

		if (numero == -2) {								//code de sauvegarde
				sauvegarderPartie();
		}

		else if (numero == -3) {						//code charger 
			chargerPartie();
			afficherPartie();
		}

		else if (numero == -4) {						//code nouvelle partie
			//setMemoirePartie();

			int	desordre[52];
			for (int i = 0; i < 52; i++) {			// crée tableau 52 premiers entiers tries
				desordre[i] = i;
			}
			//srand(time(NULL));
			int indiceAlea = 0;
			int temp = 0;
			for (int i = 0; i < 52; i++) {
				indiceAlea = rand() % 52;			// echange des cases i et indiceAlea
				temp = desordre[i];
				desordre[i] = desordre[indiceAlea];
				desordre[indiceAlea] = temp;
			}
			cout << "on a cree du desordre" << endl;

			// INITIALISE MEMOIRE PARTIE AVEC LES ENTIERS FAISANT REFERENCE A DES CARTES DE jeuDeCarte_

			//memoirePartie_[20][8] = { 53 };			// car 54e carte de jeuDeCartes_ : carteVide					//initialise bien tout à 53?

			for (int i = 0; i < 8; i++) {
				memoirePartie_[0][i] = 52;			// car 53e carte de jeuDeCartes_ : carteBleu
			}
			for (int i = 0; i < 52; i++) {
				memoirePartie_[i / 8 + 1][i % 8] = desordre[i];			//les 52 cases suivante de memoire à initialiser (à partir de 1ere ligne) reçoivent les entiers de desordre
			}

			for (int i = 52; i < 20 * 8; i++) {
				memoirePartie_[i / 8 + 1][i % 8] = 53;			//car 54e carte de jeuDeCartes_ = carteVide
			}





			cout << "on a changé memoirepartie" << endl;

			setMiniMemoire();

			afficherPartie();

		}

		//on test le couple (click + déclick):

		else if (numero != -1 && numero2 != -1 && estDeplacementValide(numero, numero2) )									//si cette saisie est correcte [2premiers tests : deplacement a un sens - 3e test : deplacement valide vis à vis des regles completes]
		{
			cout << "on va deplacer" << endl;
			deplacement(numero, numero2);
		}
	}



	if (miniMemoire_[13] != 13 || miniMemoire_[14] != 13 || miniMemoire_[15] != 13 || miniMemoire_[16] != 13) {				//partie gagnée
		afficherGagner();																											//puis lancer nouvelle partie ?
	}

}


/*


int	desordre[52];
for (int i = 0; i < 52; i++) {			// crée tableau 52 premiers entiers tries
	desordre[i] = i;
}
//srand(time(NULL));
int indiceAlea = 0;
int temp = 0;
for (int i = 0; i < 52; i++) {
	indiceAlea = rand() % 52;			// echange des cases i et indiceAlea
	temp = desordre[i];
	desordre[i] = desordre[indiceAlea];
	desordre[indiceAlea] = temp;
}
cout << "on a cree du desordre" << endl;

// INITIALISE MEMOIRE PARTIE AVEC LES ENTIERS FAISANT REFERENCE A DES CARTES DE jeuDeCarte_

//memoirePartie_[20][8] = { 53 };			// car 54e carte de jeuDeCartes_ : carteVide					//initialise bien tout à 53?

for (int i = 0; i < 8; i++) {
	memoirePartie_[0][i] = 52;			// car 53e carte de jeuDeCartes_ : carteBleu
}
for (int i = 0; i < 52; i++) {
	memoirePartie_[i / 8 + 1][i % 8] = desordre[i];			//les 52 cases suivante de memoire à initialiser (à partir de 1ere ligne) reçoivent les entiers de desordre
}

for (int i = 52; i < 20 * 8; i++) {
	memoirePartie_[i / 8 + 1][i % 8] = 53;			//car 54e carte de jeuDeCartes_ = carteVide
}





cout << "on a changé memoirepartie" << endl;

*/


/*unsigned char	blanc_color[3] = { 200,200,200 };
			scene_->draw_text(785, 130, "êtes-vous ", blanc_color, 0, 1, 20);
			scene_->draw_text(785, 150, " sûrs ?", blanc_color, 0, 1, 20);
			cout << "vous avez sauvegarde cette partie" << endl;
			scene_->draw_text(785, 170, "oui ", blanc_color, 0, 1, 20);
			scene_->draw_text(860, 170, "non ", blanc_color, 0, 1, 20);
			*/
			/*
						while (!disp_->is_closed() && !disp_->is_keyESC() && !disp_->is_keyQ() && val3 == 0) {								//tant que la 2e saisie n'est pas effectuée
							if (!(disp_->button() & 1)) {																				// on relache

								int y2 = disp_->mouse_y();
								int x2 = disp_->mouse_x();
								Coordonnee coord3(miniMemoire_, x2, y2);
								num3 = coord3.quit();


								//cout << endl << "							2eme carte carte associee numero " << numero2 << "   " << numero2 / 8 << "   " << numero2 % 8 << endl;
								val1 = 1;																								//2e saisie effectuée

							}
						}

						if (num3==1)*/





/*
Partie::Partie(const Partie & part)
{
	jeuDeCartes_ = part.jeuDeCartes_;				//ensemble des cartes à jouer	52 + bleu + vide + rouge
	miniMemoire_ = part.miniMemoire;				//vision réduite de l'occupation du plateau -> reserve + 8 colonnes + 4 sorties + 4 reserves (pour saisie 1 ds reserve)
	memoirePartie_ = part.memoirePartie_;		//memoire du plateau de jeu
	CImg<unsigned char>* scene_;		//environnement visuel
	CImgDisplay* disp_;
}
*/


Partie::~Partie()
{
}

void Partie::setJeuDeCartes()
{

	//IMPORTE LES IMAGES DEPUIS LE DOSSIER ET CREE LES CARTES ASSOCIEES

	CImg<unsigned char> dosBleu;		// Declare an image
	dosBleu.load("b1fv.ppm");			// Load an image file into it
	Carte dosBleu_(dosBleu);			// Cree une carte associee à cette image

	CImg<unsigned char> dosRouge;	
	dosRouge.load("b2fv.ppm");
	Carte dosRouge_(dosRouge);

	Carte carteVide;


	//en attendant pour carte vide ..						//à supprimer mnt donc ?

	CImg<unsigned char> blanc;
	blanc.load("blank.ppm");
	Carte blanche(blanc);



	CImg<unsigned char> s01;
	s01.load("s01.ppm");
	CImg<unsigned char> s02;
	s02.load("s02.ppm");
	CImg<unsigned char> s03;
	s03.load("s03.ppm");
	CImg<unsigned char> s04;
	s04.load("s04.ppm");
	CImg<unsigned char> s05;
	s05.load("s05.ppm");
	CImg<unsigned char> s06;
	s06.load("s06.ppm");
	CImg<unsigned char> s07;
	s07.load("s07.ppm");
	CImg<unsigned char> s08;
	s08.load("s08.ppm");
	CImg<unsigned char> s09;
	s09.load("s09.ppm");
	CImg<unsigned char> s10;
	s10.load("s10.ppm");
	CImg<unsigned char> s11;
	s11.load("s11.ppm");
	CImg<unsigned char> s12;
	s12.load("s12.ppm");
	CImg<unsigned char> s13;
	s13.load("s13.ppm");


	CImg<unsigned char> d01;
	d01.load("d01.ppm");
	CImg<unsigned char> d02;
	d02.load("d02.ppm");
	CImg<unsigned char> d03;
	d03.load("d03.ppm");
	CImg<unsigned char> d04;
	d04.load("d04.ppm");
	CImg<unsigned char> d05;
	d05.load("d05.ppm");
	CImg<unsigned char> d06;
	d06.load("d06.ppm");
	CImg<unsigned char> d07;
	d07.load("d07.ppm");
	CImg<unsigned char> d08;
	d08.load("d08.ppm");
	CImg<unsigned char> d09;
	d09.load("d09.ppm");
	CImg<unsigned char> d10;
	d10.load("d10.ppm");
	CImg<unsigned char> d11;
	d11.load("d11.ppm");
	CImg<unsigned char> d12;
	d12.load("d12.ppm");
	CImg<unsigned char> d13;
	d13.load("d13.ppm");


	CImg<unsigned char> c01;
	c01.load("c01.ppm");
	CImg<unsigned char> c02;
	c02.load("c02.ppm");
	CImg<unsigned char> c03;
	c03.load("c03.ppm");
	CImg<unsigned char> c04;
	c04.load("c04.ppm");
	CImg<unsigned char> c05;
	c05.load("c05.ppm");
	CImg<unsigned char> c06;
	c06.load("c06.ppm");
	CImg<unsigned char> c07;
	c07.load("c07.ppm");
	CImg<unsigned char> c08;
	c08.load("c08.ppm");
	CImg<unsigned char> c09;
	c09.load("c09.ppm");
	CImg<unsigned char> c10;
	c10.load("c10.ppm");
	CImg<unsigned char> c11;
	c11.load("c11.ppm");
	CImg<unsigned char> c12;
	c12.load("c12.ppm");
	CImg<unsigned char> c13;
	c13.load("c13.ppm");


	CImg<unsigned char> h01;
	h01.load("h01.ppm");
	CImg<unsigned char> h02;
	h02.load("h02.ppm");
	CImg<unsigned char> h03;
	h03.load("h03.ppm");
	CImg<unsigned char> h04;
	h04.load("h04.ppm");
	CImg<unsigned char> h05;
	h05.load("h05.ppm");
	CImg<unsigned char> h06;
	h06.load("h06.ppm");
	CImg<unsigned char> h07;
	h07.load("h07.ppm");
	CImg<unsigned char> h08;
	h08.load("h08.ppm");
	CImg<unsigned char> h09;
	h09.load("h09.ppm");
	CImg<unsigned char> h10;
	h10.load("h10.ppm");
	CImg<unsigned char> h11;
	h11.load("h11.ppm");
	CImg<unsigned char> h12;
	h12.load("h12.ppm");
	CImg<unsigned char> h13;
	h13.load("h13.ppm");


	//crées sur le tas ?

	Carte h01_(h01, 1, 'r', 1);
	Carte h02_(h02, 2, 'r', 1);
	Carte h03_(h03, 3, 'r', 1);
	Carte h04_(h04, 4, 'r', 1);
	Carte h05_(h05, 5, 'r', 1);
	Carte h06_(h06, 6, 'r', 1);
	Carte h07_(h07, 7, 'r', 1);
	Carte h08_(h08, 8, 'r', 1);
	Carte h09_(h09, 9, 'r', 1);
	Carte h10_(h10, 10, 'r', 1);
	Carte h11_(h11, 11, 'r', 1);		//coeur
	Carte h12_(h12, 12, 'r', 1);
	Carte h13_(h13, 13, 'r', 1);

	Carte s01_(s01, 1, 'b', 0);
	Carte s02_(s02, 2, 'b', 0);			//pique
	Carte s03_(s03, 3, 'b', 0);
	Carte s04_(s04, 4, 'b', 0);
	Carte s05_(s05, 5, 'b', 0);
	Carte s06_(s06, 6, 'b', 0);
	Carte s07_(s07, 7, 'b', 0);
	Carte s08_(s08, 8, 'b', 0);
	Carte s09_(s09, 9, 'b', 0);
	Carte s10_(s10, 10, 'b', 0);
	Carte s11_(s11, 11, 'b', 0);
	Carte s12_(s12, 12, 'b', 0);
	Carte s13_(s13, 13, 'b', 0);

	Carte d01_(d01, 1, 'r', 3);				//carreau
	Carte d02_(d02, 2, 'r', 3);
	Carte d03_(d03, 3, 'r', 3);
	Carte d04_(d04, 4, 'r', 3);
	Carte d05_(d05, 5, 'r', 3);
	Carte d06_(d06, 6, 'r', 3);
	Carte d07_(d07, 7, 'r', 3);
	Carte d08_(d08, 8, 'r', 3);
	Carte d09_(d09, 9, 'r', 3);
	Carte d10_(d10, 10, 'r', 3);
	Carte d11_(d11, 11, 'r', 3);
	Carte d12_(d12, 12, 'r', 3);
	Carte d13_(d13, 13, 'r', 3);

	Carte c01_(c01, 1, 'b', 2);
	Carte c02_(c02, 2, 'b', 2);
	Carte c03_(c03, 3, 'b', 2);
	Carte c04_(c04, 4, 'b', 2);
	Carte c05_(c05, 5, 'b', 2);		//treffle
	Carte c06_(c06, 6, 'b', 2);
	Carte c07_(c07, 7, 'b', 2);
	Carte c08_(c08, 8, 'b', 2);
	Carte c09_(c09, 9, 'b', 2);
	Carte c10_(c10, 10, 'b', 2);
	Carte c11_(c11, 11, 'b', 2);
	Carte c12_(c12, 12, 'b', 2);
	Carte c13_(c13, 13, 'b', 2);

	Carte jeuDeCartesTemporaire[54]= { s01_,s02_,s03_,s04_,s05_,s06_,s07_,s08_,s09_,s10_,s11_,s12_,s13_,h01_,h02_ ,h03_,h04_,h05_,h06_,h07_,h08_,h09_,h10_,h11_,h12_,h13_,c01_ , c02_ , c03_, c04_,c05_,c06_,c07_,c08_,c09_,c10_,c11_,c12_,c13_ ,d01_,d02_,d03_,d04_,d05_,d06_,d07_,d08_,d09_,d10_,d11_,d12_,d13_ ,dosBleu_, carteVide/*, dosRouge_*/ };
	
	for (int i = 0; i < 54; i++) {
		jeuDeCartes_[i] = jeuDeCartesTemporaire[i];							//on ne peut pas faire plus simple?
	}
	

	//tableau de toutes les cartes : 52 cartes + carte dosBleu + carte Vide
	//jeuDeCartes_[54] =  { s01_,s02_,s03_,s04_,s05_,s06_,s07_,s08_,s09_,s10_,s11_,s12_,s13_,h01_,h02_ ,h03_,h04_,h05_,h06_,h07_,h08_,h09_,h10_,h11_,h12_,h13_,c01_ , c02_ , c03_, c04_,c05_,c06_,c07_,c08_,c09_,c10_,c11_,c12_,c13_ ,d01_,d02_,d03_,d04_,d05_,d06_,d07_,d08_,d09_,d10_,d11_,d12_,d13_ ,dosBleu_, carteVide };

}






void Partie::setMemoirePartie()			//crée une distribution aléatoire des 52 cartes du jeu et enregistre ce mélange dans les 8 colonnes de jeu en mémoire
{
	// Dans le pire des cas (très peu probable qu'il soit utilisé) il doit être possible de mettre 18 cartes dans chaque colonne  (19 avec As mais peu utile, il peut aller directement en Sortie) + 1 pour reserve ou sortie
	//ce tableau represente la memoire du jeu, chaque case représente une position sur le plateau et contient un entier représentant une carte. Cet entier code la carte au travers du tableau "tableau" de 54 cartes utiles au jeu

	

	//CREE TABLEAU ALEATOIREMENT DESORDONNE DES 52 PREMIERS ENTIERS  (chacun représentant une carte)
	//bibliotheques ctime et cstdlib deja incluses dans Cimh.h

	int	desordre[52];
	for (int i = 0; i < 52; i++) {			// crée tableau 52 premiers entiers tries
		desordre[i] = i;
	}
	srand(time(NULL));
	int indiceAlea = 0;
	int temp = 0;
	for (int i = 0; i < 52; i++) {
		indiceAlea = rand() % 52;			// echange des cases i et indiceAlea
		temp = desordre[i];					
		desordre[i] = desordre[indiceAlea];
		desordre[indiceAlea] = temp;
	}


	// INITIALISE MEMOIRE PARTIE AVEC LES ENTIERS FAISANT REFERENCE A DES CARTES DE jeuDeCarte_

	//memoirePartie_[20][8] = { 53 };			// car 54e carte de jeuDeCartes_ : carteVide					//initialise bien tout à 53?
	
	for (int i = 0; i < 8; i++) {
		memoirePartie_[0][i] = 52;			// car 53e carte de jeuDeCartes_ : carteBleu
	}
	for (int i = 0; i < 52; i++) {
		memoirePartie_[i / 8 + 1][i % 8] = desordre[i];			//les 52 cases suivante de memoire à initialiser (à partir de 1ere ligne) reçoivent les entiers de desordre
	}

	for (int i = 52; i < 20 * 8; i++) {
		memoirePartie_[i / 8 + 1][i % 8] = 53;			//car 54e carte de jeuDeCartes_ = carteVide
	}

}





void Partie::setMiniMemoire() {						//ou alors va compter dans memoireJeu pour quand charge ancienne partie ?
	
	miniMemoire_[0]  = 0;							//nb de cartes dans reserve

	for (int i = 9; i < 17; i++) {					//nb de cartes dans chaque sortie et chaque reserve
		miniMemoire_[i]=0;
	}
	for (int i = 1; i < 5; i++) {					//nb de cartes dans les 8 colonnes
		miniMemoire_[i] = 7;
	}
	for (int i = 5; i < 9; i++) {
		miniMemoire_[i] = 6;
	}
}





void Partie::setScene()			
{
	// Usefull colors
	unsigned char
		blanc_color[3] = { 200,200,200 },
		grid_color[3] = { 0,0,255 },
		play1_color[3] = { 204,0,0 },
		play2_color[3] = { 0,102,0 };

	// Declare an image to draw the grid
	scene_=new CImg<unsigned char> (900, 700, 1, 3, 0);			//x y z c(rvb) et val défaut ?


	//for (int i = 1; i < 18; i++) scene_->draw_line(0, 50 * i, 800, 50 * i, grid_color);
	//for (int j = 1; j < 8; j++) scene_->draw_line(100 * j, 0, 100 * j, 800, grid_color);


	for (int j = 0; j < 4; j++) {
		scene_->draw_image(50 + j * 70, 0 * 30, 0, 0, jeuDeCartes_[52].getImage(), 1);

	}
	for (int j = 0; j < 4; j++) {
		scene_->draw_image(450 + j * 70, 0 * 30, 0, 0, jeuDeCartes_[52].getImage(), 1);

	}

	for (int j = 0; j < 8; j++) {
		for (int i = 0; i < 7; i++) {
			scene_->draw_image(j * 100, (i+4) * 30, 0, 0, jeuDeCartes_[memoirePartie_[i+1][j]].getImage(), 1);
		}
	}

	scene_->draw_line(780, 0, 780, 800, blanc_color);
	scene_->draw_line(780, 200, 900, 200, blanc_color);
	scene_->draw_line(780, 400, 900, 400, blanc_color);


	scene_ -> draw_text(785, 100, "sauvegarder", blanc_color , 0 , 1 , 20);
	scene_->draw_text(810, 300, "charger", blanc_color, 0, 1, 20);
	scene_->draw_text(800, 500, "nouvelle", blanc_color, 0, 1, 20);

	scene_->draw_text(800, 550, "partie", blanc_color, 0, 1, 20);
}





void Partie::setDisp()
{

	// Declare a display to draw the scene
	disp_ = new CImgDisplay(*scene_, "freecell", 0, false, false);						//affiche dans une fenetre 'disp' l'image 'scene_', quand on operera à un changement dans l'image, il faudra la réafficher avec la commande	'scene_->display(disp);'
		// Center the window on the screen
	disp_->move((CImgDisplay::screen_width() - disp_->width()) / 2,
		(CImgDisplay::screen_height() - disp_->height()) / 2);
}






bool Partie::estDeplacementValide(int num1, int num2)
{
	Carte carte1 = jeuDeCartes_[memoirePartie_[num1 / 8][num1 % 8]];				
	Carte carte2 = jeuDeCartes_[memoirePartie_[num2 / 8][num2 % 8]];			//utile pour depl sur une colonne non vide

	if (num2 <= 3)														//toute carte mobile peut aller en réserve
		return(true);
	else {
		if (num2 <= 7) {			// ou ==4							// pour sortir => [val en mem pour cette couleur = Carte1.getValeur()-1]
			int couleur = carte1.getCouleur();
			if (miniMemoire_[couleur+13]+1== carte1.getValeur()) {							//jeuDeCartes_[memoirePartie_[0][4+couleur]].getValeur()+1 == carte1.getValeur()) {
				cout << "true ! le deplacement est valide ";
				return (true); 
				
			}
			else {
				cout << "valeur ds sortie " << jeuDeCartes_[memoirePartie_[0][4 + couleur]].getValeur() << endl;
				cout << "valeur d'entree attendue " << jeuDeCartes_[memoirePartie_[0][4 + couleur]].getValeur() + 1 << endl;
				cout << "indice de localisation de la carte dans jeuDeCarte" << memoirePartie_[0][4 + couleur] << endl;
				cout << " valeur de carte 1 :  " << carte1.getValeur()<<endl;
				cout << "false ! le deplacement n'est pas valide ";
				return (false);
				
			}
		}
		else {							//on souhaite déplacer qqch sur une colonne
			if (num2 <= -10)			//toute carte mobile peut aller sur une colonne vide
				return(true);
			else {						//pour aller sur une colonne non vide il faut respecteur valeur_=valeur_+1 et caracteristique_ != caracteristique_
				if (carte1.getCaracteristique() != carte2.getCaracteristique() && carte1.getValeur() == carte2.getValeur() - 1)
					return (true);
				else
					cout << "car carte1 :  " << carte1.getCaracteristique() << endl;
					cout << "car carte2 :  " << carte2.getCaracteristique() << endl<<endl;
					cout << "val carte1 :  " << carte1.getValeur()<<endl;
					cout << "val carte2 :  " << carte2.getValeur() << endl;
					cout << "vous ne respectez pas les règles" << endl;

					return (false);
			}
		}
	}
}







void Partie::deplacement(int num1, int num2)				//effectue le déplacement jugé valide en memoire (memoirePartie et miniMemoire) et à l'affichage 
{
	Carte carte1;												
	//if (num1 >= 0) {													// à supprimer
	carte1 = jeuDeCartes_[memoirePartie_[num1 / 8][num1 % 8]];
	//}


	//AJOUTER___________________________________________________________________________________
	if (num2 <= -10) {								//ajouter carte1 sur colonne vide

		//memoire:
		int col = -num2 - 10;
		memoirePartie_[1][col] = (carte1.getCouleur() * 13 + carte1.getValeur()-1);			//emplacement dans jeuDeCarte de carte1					pourrait être remplacé par carte1.getPositionJeuDeCarte()
		miniMemoire_[col + 1] += 1;


		//affichage:
		scene_->draw_image(col * 100, 4 * 30, 0, 0, carte1.getImage(), 1);			//i=4, "2e" ligne  // j=col
		scene_->display(*disp_);

	}
	else {
		if (0 <= num2 && num2 <= 3) {								//ajouter carte1 dans reserve
			cout << "on va ajouter une carte ds reserve" << endl;
			//memoire:
			memoirePartie_[0][num2] = (carte1.getCouleur() * 13 + carte1.getValeur()-1);
			miniMemoire_[0] += 1;									//une carte de plus en réserve
			miniMemoire_[9 +num2] = 1;								// case reserve occupée [0/1]


			//affichage:
			scene_->draw_image(50 + num2 * 70, 0 * 30, 0, 0, carte1.getImage(), 1);
			scene_->display(*disp_);

		}


		else {
			if (num2 == 4) {								//sortir une carte

				//memoire:
				int couleur = carte1.getCouleur();
				memoirePartie_[0][couleur + 4] = (carte1.getCouleur() * 13 + carte1.getValeur()-1);
				miniMemoire_[13 + couleur] += 1 ;

				//affichage:
				scene_->draw_image(450 + couleur * 70, 0 * 30, 0, 0, jeuDeCartes_[couleur*13+miniMemoire_[13+couleur]-1].getImage() /*carte1.getImage()*/, 1);
				cout << "on a affiché";
				scene_->display(*disp_);

			}

			else {								//ajouter carte1 sur colonne NON vide

				//memoire:
				memoirePartie_[num2 / 8 + 1][num2 % 8] = (carte1.getCouleur()*13 + carte1.getValeur()-1 );			//non vide donc sur case suivante				-> "+1"
				miniMemoire_[num2 % 8 + 1] += 1;				//colonne

				// il faudrait ajouter un autre argument : place ds mini memoire de carte1 //miniMemoire_[]			//wut ?


				//affichage:				
				scene_->draw_image(num2 % 8 * 100, (4 + num2 / 8) * 30, 0, 0, carte1.getImage(), 1);			//i=4, "2e" ligne  // j=col
				scene_->display(*disp_);

			}
		}
	}

	//SUPPRIMER_________________________________________________

	if (num1 <= 3) {								//supprimer carte1 de la reserve

		//memoire:
		memoirePartie_[0][num1] = 52;				 //carte vide dosBleu;
		miniMemoire_[0] -= 1;						//une carte de moins dans la réserve
		miniMemoire_[9 + num1] = 0;					//plus de carte dans cette case de réserve


		//affichage:														//remplacer par jeuDeCartes_[54]
		//CImg<unsigned char> dosBleu;	dosBleu.load("b1fv.ppm");		// ou alors on recharge image dosBleu..
		scene_->draw_image(50 + num1 * 70, 0, 0, 0, jeuDeCartes_[52].getImage(), 1);		//jeuDeCartes_[memoirePartie_[num1/8][num1%8]].getImage()		pour bien justifier

	}
	else {												//supprimer carte d'une colonne
		if (num1 <= 15) {								//supprimer carte1 d'une colonne pour la rendre vide

			//memoire:
			memoirePartie_[1][num1] = 53 ;				//carteVide
			miniMemoire_[num1 - 8 + 1] -= 1;			// num2 % 8 + 1		//une carte en moins dans cette colonne

			//affichage:
			CImg<unsigned char> rectNoir(75, 95, 1, 3, 0);						
			scene_->draw_image((num1 - 8) * 100, (3 + 1) * 30, 0, 0, rectNoir, 1);
		}

		else {												//supprimer carte1 d'une colonne sans la rendre vide

			//memoire:
			memoirePartie_[num1 / 8][num1 % 8] = 53;		//carteVide
			miniMemoire_[num1 % 8 + 1] -= 1;

			//affichage:
			Carte carte0 = jeuDeCartes_[memoirePartie_[num1 / 8 - 1][num1 % 8]];			//carte à découvrir
			CImg<unsigned char> rectNoir(75, 95, 1, 3, 0);
			scene_->draw_image((num1 % 8) * 100, (3 + num1 / 8) * 30, 0, 0, rectNoir, 1);
			scene_->draw_image((num1 % 8) * 100, (3 + num1 / 8 - 1) * 30, 0, 0, carte0.getImage(), 1);
		}
	}


	scene_->display(*disp_);
	   	  
}




void Partie::afficherPartie()
{
	// Usefull colors
	unsigned char
		blanc_color[3] = { 200,200,200 },
		grid_color[3] = { 0,0,255 },
		play1_color[3] = { 204,0,0 },
		play2_color[3] = { 0,102,0 };

	// Declare an image to draw the grid
	CImg<unsigned char>  fondNoir(900, 700, 1, 3, 0);			//x y z c(rvb) et val défaut ?


	//for (int i = 1; i < 18; i++) scene_->draw_line(0, 50 * i, 800, 50 * i, grid_color);
	//for (int j = 1; j < 8; j++) scene_->draw_line(100 * j, 0, 100 * j, 800, grid_color);
	scene_->draw_image(0, 0, 0, 0, fondNoir, 1);
	
	for (int j = 0; j < 4; j++) {
		scene_->draw_image(50 + j * 70, 0 * 30, 0, 0, jeuDeCartes_[memoirePartie_[0][j]].getImage(), 1);

	}
	for (int j = 0; j < 4; j++) {
		scene_->draw_image(450 + j * 70, 0 * 30, 0, 0, jeuDeCartes_[memoirePartie_[0][j+4]].getImage(), 1);

	}

	for (int j = 0; j < 8; j++) {
		for (int i = 0; i < 7; i++) {
			scene_->draw_image(j * 100, (i + 4) * 30, 0, 0, jeuDeCartes_[memoirePartie_[i + 1][j]].getImage(), 1);
		}
	}


	scene_->draw_line(780, 0, 780, 800, blanc_color);
	scene_->draw_line(780, 200, 900, 200, blanc_color);
	scene_->draw_line(780, 400, 900, 400, blanc_color);


	scene_->draw_text(785, 100, "sauvegarder", blanc_color, 0, 1, 20);
	scene_->draw_text(810, 300, "charger", blanc_color, 0, 1, 20);
	scene_->draw_text(800, 500, "nouvelle", blanc_color, 0, 1, 20);

	scene_->draw_text(800, 550, "partie", blanc_color, 0, 1, 20);

}



void Partie::afficherGagner()
{
	int m[14][23] = { 0 };

	m[3][12] = 1;
	m[4][1] = m[4][3] = m[4][6] = m[4][8] = m[4][10] = m[4][14] = m[4][16] = m[4][18] = 1;
	m[5][1] = m[5][3] = m[5][6] = m[5][8] = m[5][10] = m[5][12] = m[5][14] = m[5][15] = m[5][16] = 1;
	m[6][1] = m[6][2] = m[6][3] = m[6][7] = m[6][9] = m[6][12] = m[6][14] = m[6][16] = m[6][18] = 1;

	for (int j = 0; j < 23; j++) {
		for (int i = 0; i < 14; i++) {
			cout << m[i][j];
		}
	}
		
		for (int i = 0; i < 14; i++) {
			for (int j = 0; j < 23; j++) {
				cout << m[i][j];
			}
			cout << endl;
		}/*

		CImg<unsigned char> dosBleu;		// Declare an image
		dosBleu.load("b1fv.ppm");			// Load an image file into it

		CImg<unsigned char> dosRouge;
		dosRouge.load("b2fv.ppm");

		disp_->wait();
		for (int j = 0; j < 23; j++) {
			for (int i = 0; i < 14; i++) {
				if (m[i][j]==1)
					scene_->draw_image(j * 35,i*55, 0, 0, dosRouge, 1);
				else
					scene_->draw_image(j * 35, i * 55, 0, 0, dosBleu, 1);
				disp_->wait();
				scene_->display(*disp_);
				//system("PAUSE");

			}
		}
		cout << "affichage gagne";*/
}

/*

	if (miniMemoire_[13] == 13 || miniMemoire_[14] == 13 || miniMemoire_[15] == 13 || miniMemoire_[16] == 13) {
		cout << " Vous avez gagné ! " << endl;
		CImg<unsigned char> victoire;
		victoire.load("great.png");
		scene_->draw_image(0, 0, 0, 0, victoire, 1);

	}
	*/
	//(miniMemoire_[13] == 13 && miniMemoire_[14] == 13 && miniMemoire_[15] == 13 && miniMemoire_[16] == 13) 
	/*
		cout << " test ! " << endl;
		CImg<unsigned char> victoire;
		victoire.load("vousavezgagne.png");
		scene_->draw_image(0, 0, 0, 0, victoire, 1);
	*/













/*
void Partie::deplacement(int num1, int num2)
{
	Carte carte1;
	if (num1 >= 0) {
		carte1 = memoire_[num1 / 8][num1 % 8];
	}
	
	if (num2 <= -10) {								//ajouter carte1 sur colonne vide
		
		//memoire:
		int col = -num2 - 10;
		memoire_[1][col] = carte1;
		Carte carteVide;
		memoire_[num1 / 8][num1 % 8] = carteVide;		//pas utile dans les faits
		miniMemoire_[col + 1] += 1;
		// il faudrait ajouter un autre argument : place ds mini memoire de carte1 //miniMemoire_[]


		//affichage:					//pour l'instant, pas reaffichage plus complexe que RIEN du blanc au niveau d'ancien emplacement de carte1
	   	scene_->draw_image(col * 100, 4 * 30, 0, 0, carte1.getImage(), 1);			//i=4, "2e" ligne  // j=col
	}
	if (0 < num2 && num2 < 3) {								//ajouter carte1 dans reserve

		//memoire:
		memoire_[0][num2] = carte1;
		Carte carteVide;
		memoire_[num1 / 8][num1 % 8] = carteVide;		//pas utile dans les faits
		miniMemoire_[0] += 1;
		//mod mini med de carte1 aussi


		//affichage:
		scene_->draw_image(50 + num2 * 70, 0 * 30, 0, 0, carte1.getImage(), 1);

	}


	if (num2 == 4) {								//sortir une carte

	//memoire:
		int couleur = carte1.getCouleur();
		memoire_[0][couleur+4] = carte1;
		Carte carteVide;
		memoire_[num1 / 8][num1 % 8] = carteVide;		//pas utile dans les faits
		miniMemoire_[12+couleur] += 1;
		// il faudrait ajouter un autre argument : place ds mini memoire de carte1 //miniMemoire_[]


		//affichage:					//pour l'instant, pas reaffichage plus complexe que RIEN du blanc au niveau d'ancien emplacement de carte1
		scene_->draw_image(450 + couleur * 70, 0 * 30, 0, 0, carte1.getImage(), 1);
		//scene.display(disp);
	}
}*/



int Partie::attendClick()
{

	int val0 = 0;											//1ere saisie non encore effectuée				//on pourrait supprimer cette condition et rempl par disp_->button()&1..
	int numero=-7;
	while (!disp_->is_closed() && !disp_->is_keyESC() && !disp_->is_keyQ() && val0 == 0) {							//tant que la 1ere saisie n'est pas valide
		scene_->display(*disp_);

		if (disp_->button() & 1) {							// Left button clicked.			


			int y = disp_->mouse_y();						//on récupere les coordonnees de la souris
			int x = disp_->mouse_x();

			Coordonnee coord(miniMemoire_, x, y);			//on les transforme en un entier codant 
			numero = coord.saisie1();

			cout << endl << "							1ere carte carte associee numero " << numero << "   " << numero / 8 << "   " << numero % 8 << endl;
			val0 = 1;							//on a saisi la 1ere carte 
		}

	}
	return (numero);
}

int Partie::attendDeclick() {
	int val1 = 0;
	int numero2 = -7;
	while (!disp_->is_closed() && !disp_->is_keyESC() && !disp_->is_keyQ() && val1 == 0) {								//tant que la 2e saisie n'est pas effectuée
		if (!(disp_->button() & 1)) {																				// on relache

			int y2 = disp_->mouse_y();
			int x2 = disp_->mouse_x();
			Coordonnee coord2(miniMemoire_, x2, y2);
			numero2 = coord2.saisie2();
			cout << endl << "							2eme carte carte associee numero " << numero2 << "   " << numero2 / 8 << "   " << numero2 % 8 << endl;
			val1 = 1;																								//2e saisie effectuée
		}
	}
	return(numero2);
}





void Partie::affiche(){
	disp_->display(*scene_);
}


//int m[23][14] = { 0 };				//message




void Partie::sauvegarderPartie() {
	ofstream fichier1 ("enregistrement_1.txt");
	if (!fichier1.is_open()) 
		cout << "Erreur d'ouverture" << endl;
	else {
		for (int i = 0; i < 8; i++) {							//sauvegarder memoirePartie_
			for (int j = 0; j < 20; j++) {
				fichier1 << memoirePartie_[i][j]<<endl;
			}
		}
		for (int i = 0; i < 17; i++) {							//sauvegarder miniMemoire_
			fichier1 << miniMemoire_[i] << endl;
		}



		if (!fichier1.good())
			cout << "Erreur d'écriture" << endl;
		else
			cout << "Enregistrement terminé" << endl;
		
	}
}

void Partie::chargerPartie() {
	ifstream fichier1("enregistrement_1.txt");
	if (!fichier1.is_open())
		cout << "Erreur d'ouverture" << endl;
	else {
		for (int i = 0; i < 8; i++) {							//charger memoirePartie_
			for (int j = 0; j < 20; j++) {
				fichier1 >> memoirePartie_[i][j] ;
			}
		}

		for (int i = 0; i < 17; i++) {							//charger miniMemoire_
			fichier1 >> miniMemoire_[i] ;
		}
		if (!fichier1.good())
			cout << "Erreur d'écriture" << endl;
		else
			cout << "Enregistrement terminé" << endl;

	}
}
