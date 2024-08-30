/**
 *   Løsningsforlag til eksamen i AlgMet, november 2020, oppgave 3.
 *
 *   @file     EX_H20_3.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
using namespace std;


/**
 *  Node (med ID/key, "avstand" vertikalt fra rota, og venstre/høyre subtre).
 */
struct Node {
    int ID;                      //  Nodens ID/key/nøkkel/navn (et tall).
    int avstand;                 //  Nodens "vertikale avstand" ift. rota.
    Node *left, *right;          //  Peker til begge subtrærne (evt. 'nullptr').
    Node(int id) { ID = id;  left = right = nullptr;  avstand = 0;  }
};


Node* gRoot = nullptr;           ///<  Peker til HELE treets rot.


/**
 *  EKSTRA - Traverserer treet under 't' rekursivt inorder.
 *
 *  @param   t  -  Noden å besøke/behandle
 */
void traverseInorder(const Node* t) {
  if (t) {
      traverseInorder(t->left);
      cout << '\t' << t->ID << ":  " << t->avstand << '\n';
      traverseInorder(t->right);
  }
}


/**
 *  OPPGAVE 3A - Setter rekursivt vertikal "avstand" i hver node ift rota
 *               (-1 til venstre, +1 til høyre).
 *
 *  @param   t  -  Noden å besøke/behandle
 */
void settVertikalAvstand(const Node* t) {
    if (t) {                                    //  Reell node:
        if (t->left) {                          //  Har venstre barn:
            t->left->avstand = t->avstand - 1;  //  Får egen avstand - 1
            settVertikalAvstand(t->left);       //  Besøker venstre subtre.
        }
        if (t->right) {                         //  Har høyre barn:
            t->right->avstand = t->avstand + 1; //  Får egen avstand + 1
            settVertikalAvstand(t->right);      //  Besøker høyre subtre.
        }
    }
}


/**
 *  OPPGAVE 3B - Skriver rekursivt alle noder i treet som er uten søsken.
 *
 *  @param   t  -  Noden å besøke/behandle
 */
void skrivNoderUtenSosken(const Node* t) {
  if (t) {                               //  Reell node:
      if (t == gRoot)                    //  Noden er selve rota:
          cout << ' ' << t->ID;          //  Skriver rotens ID.
      if (t->left && !t->right)          //  Har KUN v.barn UTEN h.søsken:
          cout << ' ' << t->left->ID;    //  Skriver venstres ID.
      if (!t->left && t->right)          //  Har KUN h.barn UTEN v.søsken:
          cout << ' ' << t->right->ID;   //  Skriver høyres ID.
      skrivNoderUtenSosken(t->left);     //  Besøker begge subtrærne:
      skrivNoderUtenSosken(t->right);
  }
}


void byggTre(); // Definisjon nedenfor 'main', da dette er en ekstra funksjon.


/**
 *  Hovedprogrammet:
 */
int main() {

    byggTre();

    //  Tester 3A:
    cout << "\n\nNodenes vertikale avstand ift. rota:\n";
    settVertikalAvstand(gRoot);
    traverseInorder(gRoot);


    //  Tester 3B:
    cout << "\n\nNoder uten søsken:\n\t";
    skrivNoderUtenSosken(gRoot);


    cout << "\n\n\n";
    return 0;
}


/**
 *  EKSTRA - Bygger et binært testtre (angitt til høyre nedenfor).
 */
void byggTre() {
    Node* p[20];
    for (int i = 1; i <= 19; i++)  p[i] = new Node(i);
    gRoot = p[1];
    p[1]->left = p[2];  p[1]->right = p[3];   //           1             //
    p[2]->left = p[4];  p[2]->right = p[5];   //       /       \         //
    p[3]->left = p[6];  p[3]->right = p[7];   //      2         3        //
    p[4]->left = p[14]; p[4]->right = p[15];  //    /   \     /   \      //
    p[5]->left = p[8];                        //   4     5   6     7     //
    p[6]->right = p[9];                       //  / \    /     \   / \   //
    p[7]->left = p[10]; p[7]->right = p[12];  // 14 15  8       9 10 12  //
    p[8]->left = p[16]; p[8]->right = p[17];  //       / \     /   \     //
    p[9]->left = p[11];                       //     16  17   11    13   //
    p[10]->right = p[13];                     //         /     \         //
    p[17]->left = p[18];                      //        18     19        //
    p[11]->right = p[19];
}
