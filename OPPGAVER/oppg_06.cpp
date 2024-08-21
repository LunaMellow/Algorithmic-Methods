/**
 *   L�sningsforslag til oppgave nr 6.
 *
 *   Det er flere m�ter � l�se disse oppgavene p�.
 *   Nedenfor er det brukt b�de funksjoner som returnerer med en int som svar,
 *   og andre funksjoner som oppdaterer en global variabel. Dette er gjort for
 *   � vise hvordan disse to ulike teknikkene/m�tene begge l�ser oppgavene.
 *
 *   @file	  OPPG_06.CPP
 *   @author  Frode Haug, NTNU
 */


#include <iostream>
using namespace std;


/**
 *  Node (med ID/key/data og venstre og h�yre pekere til nodens barn).
 */
struct Node {
    char ID;
    Node *left, *right;                //  Initierende constructor:
    Node(char id) { ID = id;  left = right = nullptr; }
};


void  antallFulle(Node* node);      //  Oppgave 6.3
int   antallNoder(Node* node);      //  Oppgave 6.1
int   antallNull(Node* node);       //  Oppgave 6.2
void  besok1(const Node* node);
void  besok2(const Node* node);
Node* byggTre();
void  treetsHoyde(Node* node);      //  Oppgave 6.4


int gAntallFulleNoder = 0;          ///<  Totalt antall FULLE noder i treet.
int gMaxHoyde = -1;                 ///<  Max.h�yde hittil funnet.
int gNivaa = -1;                    ///<  N�v�rende nodes niv�.


/**
 *  Hovedprogrammet:
 */
int main() {
    Node* root = byggTre();

    //  Oppgave 6.1:
    cout << "\n\nAntall noder:\t\t" << antallNoder(root) << "\n\n";

    //  Oppgave 6.2:
    cout << "Antall null(ptr):\t" << antallNull(root) << "\n\n";

    //  Oppgave 6.3:
    cout << "FULLE noder er:\t\t";
    antallFulle(root);
    cout << "  dvs. " << gAntallFulleNoder << " stk.\n\n";

    //  Oppgave 6.4:
    treetsHoyde(root);
    cout << "Treets h�yde:\t\t" << gMaxHoyde << "\n\n\n\n";

    return 0;
}


/**
 * Oppgave 6-3 - Finner TOTALT antall FULLE noder (to ekte barn) under 'node'.
 *
 *  @param   node  -  Aktuell node � behandle
 *  @see     besok1(...)
 */
void antallFulle(Node* node) {         //  Jfr. traverser-funksjonene i EKS_12
    if (node) {
        besok1(node);                  //  Vilk�rlig om 'besok1' forekommer
        antallFulle(node->left);       //    f�r, mellom eller etter de to
        antallFulle(node->right);      //    rekursive kallene!
    }
}


/**
 *  Oppgave 6-1 - Finner TOTALT antall noder under 'node'.
 *
 *  @param    node  -  Aktuell node � behandle
 *  @return   TOTALT antall noder under 'node'
 */
int antallNoder(Node* node) {
    int antL = 0, antR = 0;                     //  Finner rekursivt antallet
    if (node->left)   antL = antallNoder(node->left);   //  i venstre og
    if (node->right)  antR = antallNoder(node->right);  //  h�yre subtre.
    return  (antL + antR + 1);     //  Returnerer med subtr�rnes totalantall
}                                  //    PLUSS en selv (+1).


/**
 *  Oppgave 6-2 - Finner TOTALT antall nullptr/null i HELE treet.
 *
 *  @param    node  -  Aktuell (rot)node � behandle
 *  @return   TOTALT antall nullptr/null i HELE treet
 *  @see      antallNoder(...)
 */
int antallNull(Node* node) {        //  Finner enkelt antall slike noder:
    return  antallNoder(node) + 1;  //  Bruker regel 3 fra forelesning nr.4! 
}


/**
 *  Teller opp 'gAntallFulleNoder' om 'node' har to interne barn/subnoder,
 *
 *  @param   node  -  Aktuell node � behandle
 */
void besok1(const Node* node) {
    if (node->left  &&  node->right) {  //  Har TO interne/ekte subnoder/barn.
        ++gAntallFulleNoder;            //  Teller opp totalantallet av slike.
        cout << node->ID << "  ";       //  Skriver nodens ID/key/data.
    }
}


/**
 *  Oppdaterer 'gMaxHoyde' om er p� et nytt og h�yere niv� enn hittil.
 *
 *  @param   node  -  Aktuell node � behandle
 */
void besok2(const Node* node) {
    if (gNivaa > gMaxHoyde)      //  Ny max. h�yde er funnet,
        gMaxHoyde = gNivaa;      //    oppdaterer nytt max.
}


/**
 *  Bygger et bin�rt eksempel-tre (likt med det i EKS_08 og EKS_12).
 *
 *  @return   Peker til det bygde treets rot
 */
Node* byggTre() {
/*   Bygger treet :                                    A
                                              /                 \
                                         B                          C
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
 *  Oppgave 6-4 - Finner treets maksimale h�yde.
 *
 *  @param   node  -  Aktuell node � behandle
 *  @see     besok2(...)
 */
void treetsHoyde(Node* node) {        //  Jfr. traverser-funksjonene i EKS_12.
    if (node) {
        gNivaa++;                     //  �ker global variabel, da nytt niv�.
        treetsHoyde(node->left);      //  Vilk�rlig om 'besok2' forekommer
        treetsHoyde(node->right);     //    f�r, mellom eller etter de to    
        besok2(node);                 //    rekursive kallene!    
        gNivaa--;                     //  Skal opp igjen ett niv� (til "mor").
    }
}