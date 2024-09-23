/**	   IDATG2102 Oblig 2
 *
 *     Beskrivelse:
 *      - Skriv alle mulige stier fra rota til enhver bladnode.
 *      - Finn alle nodene lengst til h�yre p� alle niv�er.
 *
 *      @file Oblig 2.cpp
 *      @date 9/13/24
 *
 *      @author Luna S.
 *      @alias LunaMellow
 */

#include <iostream>
using namespace std;

/**
 *	Node Struct med ID, Venste/H�yre peker til barna
 */
struct Node {
    char ID;				// Node ID
    Node *left, *right;		// Node pekere til barn
    explicit Node(const char id) { ID = id; left = right = nullptr; }
};

// Funksjonsdeklarasjoner
Node* byggTre();
void finnOgSkrivAlleStier(const Node* node);
void skrivHoyreView(const Node* node);

// Globale variabler
int gNivaa;			///< Hvilket niv� vi er p� for �yeblikket i treet
int gNoder[50];		///< Array med ID for hver av nodene (Endre om fra int til char for � se bokstav p� nodene)

/**
 *	Hovedprogrammet
 */
int main() {
	// Bygg treet
	const Node* root = byggTre();

	// Nullstill data
	gNivaa = -1;
	for (int & i : gNoder)  i = 0;

	// Skriv alle stier
	cout << endl << "Alle Stier:" << endl;
	finnOgSkrivAlleStier(root);

	// Nullstill data
	gNivaa = -1;
	for (int & i : gNoder)  i = 0;

	// Skriv alle h�yre noder
	cout << endl << "H�yre View:" << endl;
	skrivHoyreView(root);

    return 0;
}

/**
 *	Funksjon hentet fra Frode sin kode.
 *
 *  Bygger et bin�rt eksempel-tre (likt med det i EKS_08)
 *
 *  @return		Peker til det bygde treets rot
 */
Node* byggTre() {

    /*   Bygger treet:
								    A
                          /                  \
                     B                        C
                /         \                  /
              D             E              F
          /       \           \          /
        G           H           I      J
          \        / \         /        \
           K      L   M       N          O
    */

    Node*  noder[15];
    for (int i = 0; i < 15; i++)
        noder[i] = new Node(static_cast <char> ('A' + i));

    noder[0]->left = noder[1];  noder[0]->right = noder[2];
    noder[1]->left = noder[3];  noder[1]->right = noder[4];
    noder[2]->left = noder[5];
    noder[3]->left = noder[6];  noder[3]->right = noder[7];
    noder[4]->right = noder[8];
    noder[5]->left = noder[9];
    noder[6]->right = noder[10];
    noder[7]->left = noder[11]; noder[7]->right = noder[12];
    noder[8]->left = noder[13];
    noder[9]->right = noder[14];

    return noder[0];
}

/**
 *	Finner alle mulige stier fra rota til enhver bladnode.
 *
 *  @param node		Aktuell node � behandle
 *  @see			finnOgSkrivAlleStier(...)
 */
void finnOgSkrivAlleStier(const Node* node) {
	gNivaa++;					// �ker n�v�rende niv�et for noden
	gNoder[gNivaa] = node->ID;  // Lagrer nodens ID i den globale arrayen

	// Hvis noden er et blad (Alts� ingen barn)
	if (!node->left && !node->right) {
		// Skriver ut stien fra roten til bladet
		for (int i = 0; i <= gNivaa; i++) cout << gNoder[i] << " "; cout << endl;
	}
	else {
		// Traverser og finn videre deltr�r om finnes
		if (node->left) finnOgSkrivAlleStier(node->left);
		if (node->right) finnOgSkrivAlleStier(node->right);
	}

	gNivaa--;	// Senk n�v�rende niv�et for noden
}

/**
 *	Finner alle nodene lengst til h�yre p� alle niv�er.
 *
 *  @param node		Aktuell node � behandle
 *  @see			skrivHoyreView(...)
 */
void skrivHoyreView(const Node* node) {
	gNivaa++;	// �ker n�v�rende niv�et for noden

	// Hvis noden allerede er vist
	if(!gNoder[gNivaa]){
		gNoder[gNivaa] = true;		// Sett "flagget" til true
		cout << node->ID << " ";	// Skriv ut nodens ID
	}

	// Traverser og finn videre deltr�r om finnes
    if (node->right) skrivHoyreView(node->right);
    if (node->left) skrivHoyreView(node->left);

	gNivaa--;	// Senk n�v�rende niv�et for noden
}
