/**
 *   Løsningsforlag til eksamen i AlgMet, august 2024, oppgave 3.
 *
 *   @file     EX_S24_3.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
using namespace std;


/**
 *  Node (med ID/key, venstre/høyre subtre og peker til foreldre/mor).
 */
struct Node {
  char ID;                //  Nodens ID/key/nøkkel/navn (ett tegn).
  Node *left, *right;     //  Referanser til begge subtrærne eller neste i
                          //    preorder rekkefølge eller  nullptr/NULL.
  bool nesteIPreorder;	  //  Er 'false' dersom høyre subtre finnes, er 'true'
                          //    dersom tomt høyre subtre og at 'right' da i
                          //    i stedet peker til neste node i preorder
                          //    rekkefølge. Har noden er tomt høyre subtre,
                          //    og er den aller siste i preorder rekkefølge,
                          //    vil den også være  true, bare at 'right'
                          //    da vil peke til  nullptr/NULL.
  Node (char id)          //  Constructor:
       { ID = id;  nesteIPreorder = false;  left = right = nullptr; }
};


Node* gRoot = nullptr,    ///< Rot-peker  (head->right er altså IKKE rota).
    * gForrige = nullptr; ///< Den forrige noden i preorder rekkefølge (oppg.3b).

/**
 *   Bygger et test-tre identisk til det i oppgaveteksten.
 *
 *   @return  Returnerer en peker til rota for det bygde treet
 */
Node* byggTre()  {
  Node *x, *f, *k, *s, *a, *e, *m, *p, *b, *v;
  x = new Node('X');     f = new Node('F');    //  Lager nodene:
  k = new Node('K');     s = new Node('S');
  a = new Node('A');     e = new Node('E');
  m = new Node('M');     p = new Node('P');
  b = new Node('B');     v = new Node('V');
  x->left = f;    x->right = k;                //  Bygger selve treet:
	   	          f->right = s;
  k->left = a;    k->right = e;
  s->left = m;
  e->left = p;
  m->left = b;    m->right = v;
  return x;                              //  Returnerer peker til rota ('x').
}


/**
 *  OPPGAVE 3A - Returnerer ALLTID peker til den NESTE i preorder rekkefølge.
 *
 *  @param    node  -  Noden som skal få sin neste i preorder returnert
 *  @return   Den neste noden i preorder rekkefølge
 */
Node* neste(Node* node)  {
  if (node)  {
     if (node->left)              //  Venstre barn/subtre finnes:
        return node->left;        //  Returner dette.
     else                         //  Ellers, kan man ALLTID trygt returnere
        return node->right;       //  høyre subtre ELLER NESTE preorder-node!
                                  //  NB: Trenger altså faktisk ikke å sjekke
                                  //      hva 'nesteIPreorder' er/inneholder!
  } else
	return nullptr;
}


/**
 *  OPPGAVE 3B - Setter evt forrige node i preorder rekkefølge til å peke på/
 *               referere en selv ('node').
 *
 *  @param  node  - Noden som evt blir tilpekt av den forrige
 */
void settNeste(Node* node)  {
  if (node)  {              //  En reell node:
     if (gForrige)  {       //  Minst EN node tidligere i preorder rekkefølge:
	    if (!gForrige->right)  {            //  Forrige har ingen høyre,
	       gForrige->right = node;          //  derfor er 'node' selv dens
           gForrige->nesteIPreorder = true; //  neste i preorder rekkefølge.
	    }
     }

     gForrige = node;        //  'gForrige' hopper etter (blir 'node' selv).

     settNeste(node->left);  //  Gjør rekursivt det samme for begge subtrærne,
                             //    men høyre tas KUN når det er REELT tre der:
     if (!node->nesteIPreorder) settNeste(node->right);

//  Innmaten inni denne ytre if-setning, frem til de to rekursive kallene,
//  KUNNE også i sin helhet ha vært erstattet med koden nedenfor.
//  Forskjellen ligger primært i at ovenfor peker 'gForrige' HELE tiden den
//  sist besøkte noden. Nedenfor peker 'gForrige' til den siste besøkte noden
//  som IKKE hadde noe reelt høyre barn, og derfor skal ha/få sin 'right' og
//  'nesteIPreorder' oppdatert/endret.
/*     if (gForrige)  {     //  'gForrige' peker til FORRIGE uten reell høyre:
  	    gForrige->right = node;    //  Forriges høyre peker på nåværende node.
	    gForrige = nullptr;        //  Nullstiller "gForrige".
     }

     if (!node->right)  {       //  Har ikke et reelt høyre barn/subtre:
 	    if (!node->left)        //  Venstre er heller ikke reelt.
	       gForrige = node;     //  Tar vare på nåværende node som forrige.
	    else                    //  Venstre tre er reelt/finnes:
	       node->right = node->left; // Høyre peker da til venstre.
        node->nesteIPreorder = true; // I begge tilfeller settes at høyre
     }                               //  er brukt til å peke på neste preorder.
*/
  }
}



/**
 *   Hovedprogrammet.
 */
int main()  {
  Node* p;                  //  Hjelpepeker for å traversere treet (preorder).

  p = gRoot = byggTre();

//  Tester oppgave 3A:
  cout << "\nFOR 'right' settes til aa peke paa NESTE I PREORDER rekkefolge:\n";
  while (p)  {              //  Traverserer treet (så langt man kommer):
    cout << "\n\tID:  " << p->ID
         << "\t\t'nesteIPpreorder':  " << (p->nesteIPreorder ? '1' : '0')
         << "  neste: " << (p->nesteIPreorder && p->right ? p->right->ID : ' ');
    p = neste(p);           //  Henter neste i preorder rekkefølge.
  }


//  Kjører/utfører oppgave 3B:
  settNeste(gRoot);    //  Oppdaterter alle 'right'-pekere og 'nesteIProrder'.

  if (gForrige)        //  Må evt. spesialbehandle den SISTE noden i preorder
     gForrige->nesteIPreorder = true;  //  rekkefølge. Denne har allerede
				       //  'right' lik 'nullptr', men må sette at dette betyr
				       //  slutten på preorder rekkefølge.
				       //  NB: Dette er UAKTUELT om benytter den alternative
				       //      koden angitt inni 'settNeste(...)'!

// Tester igjen oppgave 3A:
  cout << "\n\nETTER at 'right' er satt til aa peke paa NESTE I PREORDER rekkefolge:";
  p = gRoot;
  while (p)  {              //  Traverserer nå HELE treet preorder:
    cout << "\n\tID:  " << p->ID
         << "\t\t'nesteIPpreorder':  " << (p->nesteIPreorder ? '1' : '0')
         << "  neste: " << (p->nesteIPreorder && p->right ? p->right->ID : ' ');
    p = neste(p);           //  Henter neste i preorder rekkefølge.
  }

  cout << "\n\n";
  return 0;
}
