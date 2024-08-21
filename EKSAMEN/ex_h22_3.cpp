/**
 *   Løsningsforlag til eksamen i AlgMet, desember 2022, oppgave 3.
 *
 *   @file     EX_H22_3.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <iomanip>
using namespace std;


/**
 *  Node (med ID/key, venstre/høyre subtre og peker til foreldre/mor).
 */
struct Node  {
  int   ID;		       //  Nodens ID/key/nøkkel/navn (et tall).
  Node *left, *right;  //  Referanse til begge subtrærne (evt.  nullptr/NULL).
  Node* parent;		   //  Peker oppover igjen til forelder/mor,
				   	   //	  evt. nullptr/NULL om er rota.
  Node (int id, Node* l, Node* r, Node* p)  //  Constructor:
       { ID = id; left = l; right = r; parent = p; }
};


Node* gRoot = nullptr;	///<  Rot-peker  (head->right er altså IKKE rota).


/**
 *   Enum for å skrive ut på pre-, in- og postorder måte.
 */
enum Type { Pre, In, Post };


/**
 *   Skriver treet ut på rekursiv måte som pre-, in- eller postorder.
 *
 *   @param   ty  -  Order-måten (pre, in, post)
 *   @param   n   -  Noden som skal skrives ut
 */
void traverse(const Type ty, const Node* n)  {
  if (n != nullptr)  {         //  Reell node i treet:
     if (ty == Pre)  cout << ' ' << n->ID;
     traverse(ty, n->left);    //  Går til venstre subtre.
     if (ty == In)   cout << ' ' << n->ID;
     traverse(ty, n->right);   //  Går til høyre subtre.
     if (ty == Post) cout << ' ' << n->ID;
  }
}


/**
 *  OPPGAVE 3A - Returnerer NESTE node i preorder rekkefølgen ift 'n'.
 *
 *  @param   n   -  Aktuell node å finne preorder-ETTERFØLGER til
 *  @return  Peker til noden som er preorder-etterfølger (evt. 'nullptr/NULL')
 */
Node* nestePreorder(const Node* n)  {   //  'n' IKKE peker til nullptr!
                     //  'n' har venstre - denne er neste i preorder:
  if (n->left != nullptr)  return n->left;
                     //  'n' har KUN høyre, denne er neste i preorder:
  else if (n->right != nullptr)  return n->right;
  else  {            //  'n' er bladnode (da har hverken venstre eller høyre):
     Node* p = n->parent;     //  Starter hos mora/forelder.
                     //  Så lenge ikke bladd helt opp og forbi rota og
                     //    så lenge kommer fra høyre side eller at
                     //    mora/forelder IKKE har et høyre barn/subtre:
     while (p != nullptr  &&  (n == p->right ||  p->right == nullptr))  {
        n = p;  p = n->parent;  //  Blar ett hakk opp (til mora/forelder).
     }               //  Om stanset inni treet, med en reell høyre node -
                     //    returneres denne høyre noden, ellers nullptr.
     return ((p != nullptr) ? p->right : nullptr);
  }
}


/**
 *  OPPGAVE 3B - Returnerer FORRIGE node i preorder rekkefølgen ift 'n'.
 *
 *  @param    n   -  Aktuell node å finne preorder-FORGJENGER til
 *  @return   Peker til noden som er preorder-forgjenger (evt. 'nullptr/NULL')
 */
Node* forrigePreorder(const Node* n)  {   //  'n' IKKE peker til nullptr!
                               //  'n' er rotnode, derfor ingen forrige/før:
  if (n->parent == nullptr)  return nullptr;
  Node* p = n->parent->left;   //  Starter øverst i mor's venstre subtre.
                               //  Er selv dette venstre barnet ELLER mor har
                               //    ingen venstre - forrige er da mora selv:
  if (n == p  ||  p == nullptr) return n->parent;
                       //  Looper "evig" til har funnet forrige i preorder -
                       //     som ALLTID(!!!) er en bladnode:
  while (true)         //  Primært blas det nedover mot høyre:
    if (p->right != nullptr) p = p->right;
                       //  Sekundært blas det nedover mot venstre:
    else if (p->left != nullptr) p = p->left;
    else return p;     //  Kommet ned til bladnode - og dette var den forrige!
}


/**
 *   Hovedprogrammet.
 */
int main()  {
  Node *n6, *n8, *n11, *n12, *n13, *n17, *n28, *n31, *n33, *n34, *n35, *n39;
                // Bygger treet:          17              //
                //                    /        \          //
                //                   11         33        //
                //                 /    \     /    \      //
                //                6      13 28     35     //
                //                 \    /    \     / \    //
                //                  8  12     31  34 39   //
  n8  = new Node(8,  nullptr,  nullptr, nullptr);
  n12 = new Node(12, nullptr,  nullptr, nullptr);
  n31 = new Node(31, nullptr,  nullptr, nullptr);
  n34 = new Node(34, nullptr,  nullptr, nullptr);
  n39 = new Node(39, nullptr,  nullptr, nullptr);
  n6  = new Node(6,  nullptr,  n8,      nullptr);    n8->parent  = n6;
  n13 = new Node(13, n12,      nullptr, nullptr);    n12->parent = n13;
  n28 = new Node(28, nullptr,  n31,     nullptr);    n31->parent = n28;
  n35 = new Node(35, n34, n39, nullptr); n34->parent = n35; n39->parent = n35;
  n11 = new Node(11, n6,  n13, nullptr); n6->parent  = n11; n13->parent = n11;
  n33 = new Node(33, n28, n35, nullptr); n28->parent = n33; n35->parent = n33;
  n17 = new Node(17, n11, n33, nullptr); n11->parent = n17; n33->parent = n17;
  gRoot = n17;


  cout << "\n\nTreet traversert:\n\tPreorder:   ";
  traverse(Pre,  gRoot);   cout << "\n\tInorder:    ";
  traverse(In,   gRoot);   cout << "\n\tPostorder:  ";
  traverse(Post, gRoot);

  Node* svar;

  cout << "\n\n\nNESTE PREORDER ift:\n";
  svar = nestePreorder(n17);
  cout << "\t17: " << setw(4) << ((svar) ? svar->ID : 0) << '\n';    //  11
  svar = nestePreorder(n11);
  cout << "\t11: " << setw(4) << ((svar) ? svar->ID : 0) << '\n';    //   6
  svar = nestePreorder(n6);
  cout << "\t 6: " << setw(4) << ((svar) ? svar->ID : 0) << '\n';    //   8
  svar = nestePreorder(n13);
  cout << "\t13: " << setw(4) << ((svar) ? svar->ID : 0) << '\n';    //  12
  svar = nestePreorder(n8);
  cout << "\t 8: " << setw(4) << ((svar) ? svar->ID : 0) << '\n';    //  13
  svar = nestePreorder(n12);
  cout << "\t12: " << setw(4) << ((svar) ? svar->ID : 0) << '\n';    //  33
  svar = nestePreorder(n31);
  cout << "\t31: " << setw(4) << ((svar) ? svar->ID : 0) << '\n';    //  35
  svar = nestePreorder(n34);
  cout << "\t34: " << setw(4) << ((svar) ? svar->ID : 0) << '\n';    //  39
  svar = nestePreorder(n39);
  cout << "\t39: " << setw(4) << ((svar) ? svar->ID : 0) << '\n';    //   0

  cout << "\n\nFORRRIGE PREORDER ift:\n";
  svar = forrigePreorder(n17);
  cout << "\t17: " << setw(4) << ((svar) ? svar->ID : 0) << '\n';    //   0
  svar = forrigePreorder(n11);
  cout << "\t11: " << setw(4) << ((svar) ? svar->ID : 0) << '\n';    //  17
  svar = forrigePreorder(n6);
  cout << "\t 6: " << setw(4) << ((svar) ? svar->ID : 0) << '\n';    //  11
  svar = forrigePreorder(n13);
  cout << "\t13: " << setw(4) << ((svar) ? svar->ID : 0) << '\n';    //   8
  svar = forrigePreorder(n8);
  cout << "\t 8: " << setw(4) << ((svar) ? svar->ID : 0) << '\n';    //   6
  svar = forrigePreorder(n12);
  cout << "\t12: " << setw(4) << ((svar) ? svar->ID : 0) << '\n';    //  13
  svar = forrigePreorder(n31);
  cout << "\t31: " << setw(4) << ((svar) ? svar->ID : 0) << '\n';    //  28
  svar = forrigePreorder(n34);
  cout << "\t34: " << setw(4) << ((svar) ? svar->ID : 0) << '\n';    //  35
  svar = forrigePreorder(n39);
  cout << "\t39: " << setw(4) << ((svar) ? svar->ID : 0) << '\n';    //  34
  svar = forrigePreorder(n33);
  cout << "\t33: " << setw(4) << ((svar) ? svar->ID : 0) << '\n';    //  12
  svar = forrigePreorder(n35);
  cout << "\t35: " << setw(4) << ((svar) ? svar->ID : 0) << '\n';    //  31

  return 0;
}
