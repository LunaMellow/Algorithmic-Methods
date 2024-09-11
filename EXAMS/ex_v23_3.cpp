/**
 *   Løsningsforlag til ekstraeksamen i AlgMet, vår 2023, oppgave 3.
 *
 *   @file     EX_V23_3.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
using namespace std;


/**
 *  Node (med ID/key, "avstand" vertikalt fra rota, og venstre/høyre subtre).
 */
struct Node {
    int ID;                      //  Nodens ID/key/nøkkel/navn (et tall).
    Node *left, *right;          //  Peker til begge subtrærne (evt. 'nullptr').
    Node(int id) { ID = id;  left = right = nullptr;  }
};


Node* gRoot = nullptr;           ///<  Peker til HELE treets rot.


/**
 *  EKSTRA - Traverserer treet under 't' rekursivt inorder.
 *
 *  @param   t  -  Noden å besøke/behandle
 */
void traverseInorder(Node* t) {
  if (t) {
      traverseInorder(t->left);
      cout << "  " << t->ID;
      traverseInorder(t->right);
  }
}


/**
 *  OPPGAVE 3A - Sjekker rekursivt om to noder er søsken (samme mor/forelder).
 *
 *  @param    t   -  Mor-/forelder-noden
 *  @param    s1  -  Node(/søsken?) nr.1
 *  @param    s2  -  Node(/søsken?) nr.2
 *  @return   Om nodene tilpekt av 's1' og 's2' er søsken under 't' eller ei
 */
bool erSosken(const Node* t, const Node* s1, const Node* s2) {
    if (t)                                            // Mor/forelder finnes:
       return((t->left == s1  &&  t->right == s2) ||  // Er søsken på den ene
              (t->left == s2  &&  t->right == s1) ||  //   eller andre siden:
              erSosken(t->left, s1, s2) ||            // Er evt. søsken lengre
              erSosken(t->right, s1, s2));            //   nede i treet:
    else                                              //  't' er lik nullptr:
       return false;
}


/**
 *  OPPGAVE 3B - Kutter rekursivt du noder i treet (og deres subtrær)
 *               større enn eller lik en gitt verdi.
 *
 *  NB: At det videre nedover i de utkuttede subtrærne evt. er IDer som er
 *      mindre enn  verdi  tar vi ikke hensyn til. At det i C++ på denne måten
 *      egentlig oppstår en memory-lekkasje, ved at det ikke sies 'delete' om
 *      alle nodene i subtrærne, tar vi heller ikke hensyn til.
 *      Vi forutsetter at rota ikke har en verdi som gjør at den skal
 *      kuttes vekk/ut.
 *
 *  @param   t      -  Noden å evt. kutte vekk subtrær under
 *  @param   verdi  -  Noder med ID >= 'verdi' kuttes vekk (og subtrærne)
 */
void kappTreNedentil(Node* t, const int verdi) {
    if (t)  {                                    //  Node finnes:
       if (t->left  &&  t->left->ID >= verdi)    //  Venstre barn finnes, og
          t->left = nullptr;                     //    skal kuttes vekk.
       else                                      //  Ellers besøkes venstre
          kappTreNedentil(t->left, verdi);       //    subtre.

       if (t->right  &&  t->right->ID >= verdi)  //  Samme for høyre barn:
          t->right = nullptr;
       else
          kappTreNedentil(t->right, verdi);
    }
}


/**
 *  Hovedprogrammet:
 */
int main() {

    Node* p[20];
    for (int i = 1; i <= 19; i++)  p[i] = new Node(i);
    gRoot = p[1];                             //  Bygger treet:
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



    //  Tester 3A:
    Node* node1, *node2;
    node1 = p[4];   node2 = p[5];
    cout << "\nNode 4 og 5 er "
         << (!erSosken(gRoot, node1, node2) ? "IKKE " : "") << "søsken!\n";
    node1 = p[9];   node2 = p[10];
    cout << "\nNode 9 og 10 er "
         << (!erSosken(gRoot, node1, node2) ? "IKKE " : "") << "søsken!\n";
    node1 = p[16];   node2 = p[17];
    cout << "\nNode 16 og 17 er "
         << (!erSosken(gRoot, node1, node2) ? "IKKE " : "") << "søsken!\n";
    node1 = p[18];   node2 = p[19];
    cout << "\nNode 18 og 19 er "
         << (!erSosken(gRoot, node1, node2) ? "IKKE " : "") << "søsken!\n";
    node1 = p[2];   node2 = p[3];
    cout << "\nNode 2 og 3 er "
         << (!erSosken(gRoot, node1, node2) ? "IKKE " : "") << "søsken!\n";
    node1 = p[6];   node2 = p[6];
    cout << "\nNode 6 og 6 er "
         << (!erSosken(gRoot, node1, node2) ? "IKKE " : "") << "søsken!\n";
    node1 = p[1];   node2 = p[1];
    cout << "\nNode 1 og 1 er "
         << (!erSosken(gRoot, node1, node2) ? "IKKE " : "") << "søsken!\n";
    node1 = p[10];   node2 = nullptr;
    cout << "\nNode 10 og 'nullptr' er "
         << (!erSosken(gRoot, node1, node2) ? "IKKE " : "") << "søsken!\n\n";



    //  Tester 3B:
    cout << "\nNodene når de større enn 11 og deres subtrær er fjernet:\n\t";
    kappTreNedentil(gRoot, 12);
    traverseInorder(gRoot);

    cout << "\n\n\n";
    return 0;
}
