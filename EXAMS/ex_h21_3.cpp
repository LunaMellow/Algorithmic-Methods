/**
 *   Løsningsforlag til eksamen i AlgMet, desember 2021, oppgave 3.
 *
 *   @file     EX_H21_3.CPP
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
const int MAX = 999;             ///<  Max.nodehøyde (LANGT høyere enn reelt).


/**
 *  EKSTRA - Traverserer treet under 't' rekursivt inorder.
 *
 *  @param   t  -  Noden å besøke/behandle
 */
void traverseInorder(const Node* t) {
  if (t) {
      traverseInorder(t->left);
      cout << "  " << t->ID;
      traverseInorder(t->right);
  }
}


/**
 *  OPPGAVE 3A - Finner rekursivt treets LAVESTE høyde/dybde.
 *
 *  @param    t  -  Noden å besøke/behandle
 *  @return   Noden 't' sin høyde ift. NÆRMESTE/LAVESTE bladnode
 */
int minimumHoyde(const Node* t) {
  int vHoyde, hHoyde,          //  Laveste høyde på venstrehøyre subtre.
      minst;                   //  Den minste høyden av de to subtrærne.

  if (!gRoot)  return 0;       //  Spesialbehandler rota - tomt tre har
                               //        høyde lik 0 (null).
  if (t)  {                    //  Reell/eksisterende node:
     if (!t->left  &&  !t->right)  return 1;  //  Er en BLADNODE. Har høyde
                                              //    lik 1 (ift. "subtrærne").
     vHoyde = minimumHoyde(t->left);          //  Finner MINIMUMshøyden på
     hHoyde = minimumHoyde(t->right);         //    de to subtrærne.
//   cout << "\n\t\t\t\t\t\tID: " << t->ID << "   v: " << vHoyde << "   h: " << hHoyde << '\n';
     minst = (vHoyde < hHoyde) ?  vHoyde : hHoyde;  //  Finner den MINSTE/
                                                    //    LAVESTE av dem.
     return (minst + 1);       //  Returnerer minste høyde PLUSS en selv (+1).

  } else                       //  = nullptr - og derfor UKJENT høyde !!!
    return MAX;
}


/**
 *  OPPGAVE 3B - Sletter rekursivt alle noder som ligger på en sti der
 *               TOTALSUMMEN av ALLE sti-nodenes ID er mindre enn 'min'.
 *
 *  @param    t    -  Noden å besøke/behandle - ref.overført - KAN bli nullptr
 *  @param    sum  -  Totalsum HITTIL på stien der 't' ligger
 *  @param    min  -  Minimumsverdi på stien for ikke å slette nodene på den
 *  @return   Lengste sti som går igjennom noden 't'
 */
int slettNoderPaaStiMedMinSum(Node* & t, const int sum, const int min) {
  int vSum, hSum,             //  STØRSTE nodesum i venstre/høyre subtre.
      storst;                 //  Den største av de to summene i subtrærne.

  if (t)  {                   //  Reell/eksisterende node:
                              //  Får tak i STØRSTE stisum i subtrærne:
    vSum = slettNoderPaaStiMedMinSum(t->left,   sum + t->ID,  min);
    hSum = slettNoderPaaStiMedMinSum(t->right,  sum + t->ID,  min);

    storst = (vSum > hSum) ?  vSum : hSum;  //  Finner den STØRSTE av dem.

//  cout << "\n\t\t\t\t\t\tMin: " << min << "   ID: " << t->ID << "   v: " << vSum << "   h: " << hSum;

    if (storst < min)  {                    //  Selv den største er under
                                            //    minimumsgrensen for stien:
//  cout << "\t\tSletter: " << t->ID << '\n';
        delete t;                           //  Noden selv slettes !!!
        t = nullptr;                        //  MEDSENDT peker NULLSTILLES !!!
    }

    return storst;                          //  Returnerer største sum funnet.

  } else                                    //  nullptr - returnerer bare
    return sum;                             //    input-parameteren 'sum'.
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
    cout << "\n\nInitielt tres min.høyde:  " << minimumHoyde(gRoot) << "\n\n";


    //  Tester 3B (og mer 3A):
    cout << "\n\nInitiell inorder traversering:\n\t\t";
    traverseInorder(gRoot);   cout << "\n\n";

    slettNoderPaaStiMedMinSum(gRoot, 0, 24);   //  14, 15, 4, 12 slettes.
    cout << "\n\nEtter sletting av noder på stier MINDRE ENN enn 24:\n\t\t";
    traverseInorder(gRoot);   cout << '\n';
    cout << "Tres min.høyde nå:  " << minimumHoyde(gRoot) << "\n\n";

    slettNoderPaaStiMedMinSum(gRoot, 0, 35);   //  16, 13, 10, 7 slettes.
    cout << "\n\nEtter sletting av noder på stier MINDRE ENN enn 35:\n\t\t";
    traverseInorder(gRoot);   cout << "\n\n";

    slettNoderPaaStiMedMinSum(gRoot, 0, 50);   //  19, 11, 9, 6, 3 slettes.
    cout << "\n\nEtter sletting av noder på stier MINDRE ENN enn 50:\n\t\t";
    traverseInorder(gRoot);   cout << '\n';
    cout << "Tres min.høyde nå:  " << minimumHoyde(gRoot) << "\n\n";

    slettNoderPaaStiMedMinSum(gRoot, 0, 60);   //  ALT/resten slettes.
    cout << "\n\nEtter sletting av noder på stier MINDRE ENN enn 60:\n";
    traverseInorder(gRoot);
    cout << "Tres min.høyde nå:  " << minimumHoyde(gRoot) << "\n\n";

    if (gRoot == nullptr)  cout << "\n\n'gRoot' peker nå til 'nullptr'.\n";
    cout << "Tres min.høyde nå:  " << minimumHoyde(gRoot) << "\n\n";

    cout << "\n\nLager EN node som rot.\n";
    gRoot = new Node(77);
    cout << "Tres min.høyde nå:  " << minimumHoyde(gRoot) << "\n\n\n\n";

    return 0;
}
