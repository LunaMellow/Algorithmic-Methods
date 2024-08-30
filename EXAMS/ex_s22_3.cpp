/**
 *   Løsningsforlag til eksamen i AlgMet, august 2022, oppgave 3.
 *
 *   @file     EX_S22_3.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
using namespace std;


/**
 *  Node (med ID/key og venstre/høyre subtre).
 */
struct Node {
  int ID;                      //  Nodens ID/key/nøkkel/navn (et tall).
  Node *left, *right;          //  Peker til begge subtrærne (evt. 'nullptr').
  Node(int id) {  ID = id;  left = right = nullptr;  }
};


Node* gRoot = nullptr;           ///<  Peker til HELE treets rot.


/**
 *  OPPGAVE 3A - Sørger (om mulig) rekursivt for at ALLE noder på nivå 'nivaa'
 *               blir skrevet ut fra venstre mot høyre (og ut på skjermen).
 *
 *  @param    t      -  Noden å besøke/behandle
 *  @param    n      -  Aktuelt nivå man er på
 *  @param    nivaa  -  Nivået man skal frem/ned til
 *  @return   Om man har kommet frem til aktuelt 'nivaa' eller ei
 */
bool skrivNivaa(const Node* t, const int n, const int nivaa) {

  if (t == nullptr)  return false;   //  Ingen node her på dette nivået.

  if (n == nivaa)  {                 //  Noden er på aktuelt/ønsket nivå:
     cout << t->ID << ' ';           //  Skriver dens ID/navn.
     return true;                    //  Returnerer at node er funnet.
  }

  bool left  = skrivNivaa(t->left,  n+1, nivaa);  //  Søker ETT NIVÅ HØYERE
  bool right = skrivNivaa(t->right, n+1, nivaa);  //   til venstre og høyre.

  return (left || right);            //  Returnerer om node(r) ble funnet
}                                    //    eller ei på høyere nivå(er).


/**
 *  OPPGAVE 3B - Bygger rekursivt et mest mulig balansert tre ut fra arrayen
 *               'arr' og dets midtpunkt (midten mellom 'start' og 'slutt').
 *
 *  @param    arr    -  Sortert array som skal gjøres om til balansert BST
 *  @param    start  -  Nederste indeks for intervallet å bygge tre ut fra
 *  @param    slutt  -  Øvertste indeks for intervallet å bygge tre ut fra
 *  @return   Peker til rota for bygget balansert (sub)tre
 */
Node* byggBalansertBST(const int arr[], const int start, const int slutt) {
  Node* nyNode;
  int   midt = (start+slutt) / 2;

  if (start <= slutt)  {
     nyNode = new Node(arr[midt]);
     nyNode->left  = byggBalansertBST(arr, start,  midt-1);
     nyNode->right = byggBalansertBST(arr, midt+1, slutt);
     return nyNode;
  } else
    return nullptr;
}


/**
 *  EKSTRA - Traverserer treet under 't' rekursivt preorder.
 *
 *  @param   t  -  Noden å besøke/behandle
 */
void traversePreorder(const Node* t) {
  if (t) {
      cout << t->ID << "  ("
           << (t->left  ? t->left->ID  : -1) << "  "
           << (t->right ? t->right->ID : -1) << ")\n";
      traversePreorder(t->left);
      traversePreorder(t->right);
  }
}


/**
 *  Hovedprogrammet:
 */
int main() {

    Node* p[20];
    for (int i = 1; i <= 19; i++)  p[i] = new Node(i);
    gRoot = p[1];                              //  Bygger treet:
    p[1]->left = p[2];  p[1]->right = p[3];    //           1             //
    p[2]->left = p[4];  p[2]->right = p[5];    //       /       \         //
    p[3]->left = p[6];  p[3]->right = p[7];    //      2         3        //
    p[4]->left = p[14]; p[4]->right = p[15];   //    /   \     /   \      //
    p[5]->left = p[8];                         //   4     5   6     7     //
    p[6]->right = p[9];                        //  / \    /     \   / \   //
    p[7]->left = p[10]; p[7]->right = p[12];   // 14 15  8       9 10 12  //
    p[8]->left = p[16]; p[8]->right = p[17];   //       / \     /   \     //
    p[9]->left = p[11];                        //     16  17   11    13   //
    p[10]->right = p[13];                      //         /     \         //
    p[17]->left = p[18];                       //        18     19        //
    p[11]->right = p[19];


    //  Tester 3A:
    cout << "\n\nTreet skrevet ut level order:\n\t";
    int aktueltNivaa = 1;
    while (skrivNivaa(gRoot, 1, aktueltNivaa))  aktueltNivaa++;


    //  Tester 3B:
    cout << "\n\n\n\nBalansert BST, traversert preorder (nodenes ID og dets barn):\n";
    int IDer[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    gRoot = byggBalansertBST(IDer, 0, 15);
    traversePreorder(gRoot);


    cout << "\n\n";
    return 0;
}
