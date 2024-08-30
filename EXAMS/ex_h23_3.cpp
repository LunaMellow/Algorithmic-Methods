/**
 *   Løsningsforlag til eksamen i AlgMet, desember 2023, oppgave 3.
 *
 *   @file     EX_H23_3.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
using namespace std;


/**
 *  Node (med ID/key, venstre/høyre subtre og peker til foreldre/mor).
 */
struct Node  {
  char  ID;			//  Nodens ID/key/nøkkel/navn (ett tegn).
  int   pos;			//  Posisjon i treet.
  Node *left, *right;	//  Referanser til begge subtrærne, evt. nullptr/NULL.
  Node (char id, int p)	//  Constructor:
            { ID = id;  pos = p;  left = right = nullptr; }
};


Node* gRoot = nullptr;	///<  Rot-peker  (head->right er altså IKKE rota).


/**
 *   EKSTRA:  Traverserer og skriver ut treet under 'p' på en preorder måte.
 *
 *   @param  p - Peker til noden som skal besøkes/skrives ut
 */
void preOrderTraverse(Node* n)  {
  if (n)  {                                        //  Reell node i treet:
     cout << ' ' << n->ID << " (pos: "             //  Skriver noden selv
          << n->pos << ") - barna:\t";             //       (ID og posisjon).
     if (n->left)  cout << n->left->ID;   cout << '\t'; //  Evt. venstre barn.
     if (n->right) cout << n->right->ID;  cout << '\n'; //  Evt. høyre barn.
     preOrderTraverse(n->left);                    //  Går til venstre subtre.
     preOrderTraverse(n->right);                   //  Går til høyre subtre.
  }
}




/**
 *   OPPGAVE 3A - Speilvender rekursivt treet under noden 'n'.
 *
 *   @param  n  -  Peker til noden som skal speilvendes
 */
void speilvend(Node* n)  {
  if (n)  {                              //  Reell node (ulik nullptr).
                                         //  Bytter venstre/høyre subtre:
     Node* nn = n->left;  n->left = n->right;  n->right = nn;
     speilvend(n->left);                 //  Gjør det samme for venstre
     speilvend(n->right);                //       og høyre subtre/barn.
  }
}


/**
 *   OPPGAVE 3A - Setter rekursivt ny posisjon ('pos') i 'n' og subtrærne.
 *
 *   @param  n  -  Peker til noden som skal få sin 'pos' satt
 *   @param  p  -  Verdien som nodens 'pos' skal settes til
 */
void settPosisjoner(Node* n, int p)  {
  if (n)  {                              //  Reell node (ulik nullptr).
     n->pos = p;                         //  Setter egen posisjon.
     settPosisjoner(n->left,  2*p);      //  Gjør det samme for venstre
     settPosisjoner(n->right, 2*p+1);    //       og høyre subtre/barn.
  }
}


/**
 *   OPPGAVE 3B - Speilvender og setter rekursivt ny posisjon i 'n' OG subtrærne.
 *
 *   @param  n  -  Peker til noden som skal speilvendes OG få sin 'pos' satt
 *   @param  p  -  Verdien som nodens 'pos' skal settes til
 */
void speilvend(Node* n, int p)  {
  if (n)  {                              //  Reell node (ulik nullptr).
     n->pos = p;                         //  Setter egen posisjon.
                                         //  Bytter venstre/høyre subtre:
     Node* nn = n->left;  n->left = n->right;  n->right = nn;
     speilvend(n->left,  2*p);           //  Gjør det samme for venstre
     speilvend(n->right, 2*p+1);         //       og høyre subtre/barn.
  }
}


/**
 *   OPPGAVE 3C - Returnerer (om mulig) noden med 'pos' lik 'p' - MED array.
 *
 *   Poenget er å finne bitmønsteret for 'p', og så følge dette ned til noden
 *   med 'pos' lik 'p'. Går derfor bare motsatt vei ift. bitmønster-bygging
 *   ifm. Huffman-trie (jfr. EKS_39_Huffman.cpp).
 *
 *   @param  p  -  Verdien som det skal letes etter som 'pos' hos en node
 */
Node*  finnNode(int p)  {
  Node* n = gRoot;                       //  Initierer søkepeker.
  if (n)  {                              //  Treet er ikke tomt:
     char intBinar[32];                  //  Array for bit-mønster (baklengs).
     int slutt = -1;                     //  Initieres til før arrayens start.
	                                     //  Bygger binærmønsteret for 'p':
     while (p)   {                       //  Så lenge bit igjen: Fyller med
       intBinar[++slutt] = (p %  2) ? '1' : '0';  //  bakerste bitet (1/0).
       p /= 2;                           //  Tar vekk det bakerste bitet(!).
     }
     slutt--;           //  Ignorerer første bit (rota), starter på 'slutt-1'.
     for (int i = slutt;  n && i >= 0;  i--)   //  Gjennomgår baklengs-bitene.
	 n = (intBinar[i] == '0') ? n->left : n->right;    //  0-venstre, 1-høyre:
  }
  return n;                          //  Returnerer noden der 'n' har stanset.


// ALTERNATIVT:  Litt mindre effektiv, men enklere(?) å forstå/skjønne:
/*
   Node* n = gRoot;		               //  Initierer søkepeker.
   int   t = p;                        //  Initierer til den søkte.

   while (n  &&  n->pos != p)  {       //  Ennå ikke ferdig/funnet:
     while (t > n->pos*2+1)  t /= 2;   //  Finner neste barns 'pos' ift.'n'
                                       //      på veien ned mot den søkte.
     n = ((t%2) ? n->right : n->left); //  Går ETT hakk ned til høyre/venstre.
     t = p;                            //  Resetter til den søkte.
  }
  return n;                          //  Returnerer noden der 'n' har stanset.
*/
}



//  ENDA en versjon, der array IKKE brukes for unnalagring av bits:

/**
 *   Finner og returnerer antall bits i en positiv int (opptil verdien 1048575).
 *
 *   @param    p  -  Int'en som det skal finnes antall bit i
 *   @return   Antall bit i 'p'
 */
int finnAntallBits(int p)  {
  int antall = 0;                              //  Finner antall bits i 'p'.

  if (p < 0)  return  -1;                      //  'p' MÅ være >= 0 (null).
  if (p == 0) return   1;                      //  Spesialbehandler 'p' = 0.

  while (p)  {                                 //  Ennå bit igjen:
    antall++;                                  //  Teller opp antall bit.
    p /= 2;                                    //  Tar vekk det bakerste.
  }
  return antall;                               //  Returnerer antallet funnet.
}


/**
 *   Finner og returnerer antall bits i en positiv int (opptil verdien 1048575).
 *
 *   @param    p  -  Int'en som det skal finnes antall bit i
 *   @return   Antall bit i 'p'
 */
int hentBit(int p, const int nr)  {
  int bit;                            //  Nåværende siste/bakerste bit.
  for (int i = 1;  i <= nr;  i++)  {  //  "Blar frem" til aktuelt bit bakfra.
      bit = p % 2;                    //  Henter nåværende bakerste bit i 'p'.
      p /= 2;                         //  Tar vekk bakerste bit i 'p'.
  }
  return bit;                         //  Returnerer funnet/ønsket bitnummer.
}


/**
 *   OPPGAVE 3C - Returnerer (om mulig) noden med 'pos' lik 'p' - UTEN array.
 *
 *   @param  p  -  Verdien som det skal letes etter som 'pos' hos en node
 */
Node*  finnNode2(int p)  {
  Node* n = gRoot;                //  Initierer søkepeker.
                                  //  Treet er ikke tomt:
  if (n)                          //  Finner antall bit, ignorerer det første
                                  //   (da rota er 1, og evt. v.barn er 2 (10)
                                  //    og evt. høyre barn er 3 (11)):
     for (int i = finnAntallBits(p)-1;  i >= 1  &&  n;  i--)
         n = (hentBit(p, i) == 0) ? n->left : n->right; // 0-venstre, 1-høyre:
  return n;                       //  Returnerer noden der 'n' har stanset.
}


/**
 *   Hovedprogrammet.
 */
int main()  {
//  Bygger test-tre:                             //         F(1)            //
  Node *nD = new Node('D', 19);                  //      /        \         //
  Node *nH = new Node('H', 26);                  //    E(2)       C(3)      //
  Node *nJ = new Node('J',  9);  nJ->right = nD; //   /    \     /    \     //
  Node *nK = new Node('K', 10);                  // I(4)  A(5) M(6)  G(7)   //
  Node *nB = new Node('B', 13);  nB->left  = nH; //   \    /    \     /     //
  Node *nL = new Node('L', 14);                  //  J(9) K(10) B(13) L(14) //
  Node *nI = new Node('I',  4);  nI->right = nJ; //    \       /            //
  Node *nA = new Node('A',  5);  nA->left  = nK; //    D(19)  H(26)         //
  Node *nM = new Node('M',  6);  nM->right = nB;
  Node *nG = new Node('G',  7);  nG->left  = nL;
  Node *nE = new Node('E',  2);  nE->left  = nI;   nE->right = nA;
  Node *nC = new Node('C',  3);  nC->left  = nM;   nC->right = nG;
  Node *nF = new Node('F',  1);  nF->left  = nE;   nF->right = nC;
  gRoot = nF;

  cout << "\n\nInitielt tre:\n";
  preOrderTraverse(gRoot);


//  Tester 3A:
  cout << "\n\nSpeilvender tre - 1.versjon:\n";
  speilvend(gRoot);
  settPosisjoner(gRoot, 1);
  preOrderTraverse(gRoot);


//  Tester 3B:
  cout << "\n\nSpeilvender tre - 2.versjon (får tilbake initielt tre):\n";
  speilvend(gRoot, 1);
  preOrderTraverse(gRoot);


//  Tester 3C - versjon med bruk av array:
  cout << "\n\nTester/viser 'finnNode':\n";
  cout << "Finn node med pos =  1:  " << finnNode(1)->ID  << '\n';  // F
  cout << "Finn node med pos =  2:  " << finnNode(2)->ID  << '\n';  // E
  cout << "Finn node med pos =  3:  " << finnNode(3)->ID  << '\n';  // C
  cout << "Finn node med pos =  4:  " << finnNode(4)->ID  << '\n';  // I
  cout << "Finn node med pos =  7:  " << finnNode(7)->ID  << '\n';  // G
  cout << "Finn node med pos =  9:  " << finnNode(9)->ID  << '\n';  // J
  cout << "Finn node med pos = 10:  " << finnNode(10)->ID << '\n';  // K
  cout << "Finn node med pos = 13:  " << finnNode(13)->ID << '\n';  // B
  cout << "Finn node med pos = 19:  " << finnNode(19)->ID << '\n';  // D
  cout << "Finn node med pos = 26:  " << finnNode(26)->ID << '\n';  // H
  Node* pp =  finnNode(27);
  if (pp) cout << "Finn node med pos = 27:  " << pp->ID;
  else    cout << "Ingen node med pos = 27";     cout << '\n';
  pp =  finnNode(17);
  if (pp) cout << "Finn node med pos = 17:  " << pp->ID;
  else    cout << "Ingen node med pos = 17";     cout << '\n';


  //  Tester 3C - EKSAKT det samme, bare IKKE bruk av array:
  cout << "\n\nTester/viser 'finnNode2':\n";
  cout << "Finn node med pos =  1:  " << finnNode2(1)->ID  << '\n';  // F
  cout << "Finn node med pos =  2:  " << finnNode2(2)->ID  << '\n';  // E
  cout << "Finn node med pos =  3:  " << finnNode2(3)->ID  << '\n';  // C
  cout << "Finn node med pos =  4:  " << finnNode2(4)->ID  << '\n';  // I
  cout << "Finn node med pos =  7:  " << finnNode2(7)->ID  << '\n';  // G
  cout << "Finn node med pos =  9:  " << finnNode2(9)->ID  << '\n';  // J
  cout << "Finn node med pos = 10:  " << finnNode2(10)->ID << '\n';  // K
  cout << "Finn node med pos = 13:  " << finnNode2(13)->ID << '\n';  // B
  cout << "Finn node med pos = 19:  " << finnNode2(19)->ID << '\n';  // D
  cout << "Finn node med pos = 26:  " << finnNode2(26)->ID << '\n';  // H
  pp =  finnNode2(27);
  if (pp) cout << "Finn node med pos = 27:  " << pp->ID;
  else    cout << "Ingen node med pos = 27";     cout << '\n';
  pp =  finnNode2(17);
  if (pp) cout << "Finn node med pos = 17:  " << pp->ID;
  else    cout << "Ingen node med pos = 17";     cout << '\n';

  cout << "\n\n";
  return 0;
}
