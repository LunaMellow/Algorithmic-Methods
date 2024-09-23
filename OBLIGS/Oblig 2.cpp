/**	   IDATG2102 Oblig 2
 *
 *     Beskrivelse:
 *      - Skriv alle mulige stier fra rota til enhver bladnode.
 *      - Finn alle nodene lengst til høyre på alle nivåer.
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
 *	Node Struct med ID, Venste/Høyre peker til barna
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
int gNivaa;			///< Hvilket nivå vi er på for øyeblikket i treet
int gNoder[50];		///< Array med ID for hver av nodene (Endre om fra int til char for å se bokstav på nodene)

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

	// Skriv alle høyre noder
	cout << endl << "Høyre View:" << endl;
	skrivHoyreView(root);

    return 0;
}

/**
 *	Funksjon hentet fra Frode sin kode.
 *
 *  Bygger et binært eksempel-tre (likt med det i EKS_08)
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
 *  @param node		Aktuell node å behandle
 *  @see			finnOgSkrivAlleStier(...)
 */
void finnOgSkrivAlleStier(const Node* node) {
	gNivaa++;					// Øker nåværende nivået for noden
	gNoder[gNivaa] = node->ID;  // Lagrer nodens ID i den globale arrayen

	// Hvis noden er et blad (Altså ingen barn)
	if (!node->left && !node->right) {
		// Skriver ut stien fra roten til bladet
		for (int i = 0; i <= gNivaa; i++) cout << gNoder[i] << " "; cout << endl;
	}
	else {
		// Traverser og finn videre deltrær om finnes
		if (node->left) finnOgSkrivAlleStier(node->left);
		if (node->right) finnOgSkrivAlleStier(node->right);
	}

	gNivaa--;	// Senk nåværende nivået for noden
}

/**
 *	Finner alle nodene lengst til høyre på alle nivåer.
 *
 *  @param node		Aktuell node å behandle
 *  @see			skrivHoyreView(...)
 */
void skrivHoyreView(const Node* node) {
	gNivaa++;	// Øker nåværende nivået for noden

	// Hvis noden allerede er vist
	if(!gNoder[gNivaa]){
		gNoder[gNivaa] = true;		// Sett "flagget" til true
		cout << node->ID << " ";	// Skriv ut nodens ID
	}

	// Traverser og finn videre deltrær om finnes
    if (node->right) skrivHoyreView(node->right);
    if (node->left) skrivHoyreView(node->left);

	gNivaa--;	// Senk nåværende nivået for noden
}
