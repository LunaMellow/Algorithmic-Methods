/**
 *   Løsningsforlag til eksamen i AlgMet, desember 2023, oppgave 4.
 *
 *   @file     EX_H23_4.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
using namespace std;


const int SLUTT = 1000000;     ///<  Siste tall å sjekke for regnestykket.


/**
 *   Finner antall sifre i et tall.
 *
 *   @param   n  -  Tallet som skal sjekkes for antall sifre
 *   @return  Antall sifre i 'n'
 */
int antSifre(int n)  {
   int antall = 0;               //  Antall sifre i 'n'.

   while (n > 0)  {              //  Sålenge sifre igjen:
      antall++;                  //  Teller opp antall sifre.
      n /= 10;                   //  Tar vekk bakerste siffer.
   }
   return antall;                //  Returnerer antall sifre i 'n'.
}


/**
 *   Hovedprogram.
 */
int main()  {

  float faktor;
  int   i, j, ii, forsteSiffer;
  bool  losning = false;


  cout << "\n\tGangingsfaktor:  ";   cin >> faktor;

  for (i = 1;  i <= SLUTT;  i++)  {             //  For alle tallene:
      if (faktor * i == int(faktor * i))  {     //  Svaret er et heltall:
         ii = i;                                //  Initierer 'ii'.
                                                //  Finner 1.siffer i 'i/ii':
         for (j = 1;  j < antSifre(i);  j++)  ii /= 10;
         forsteSiffer = ii;                     //  Tar vare på 1.siffer.
                                                //  Plusser på '0'er bak:
         for (j = 1;  j < antSifre(i);  j++)  ii *= 10;

         ii = i - ii;                           //  Tar vekk 1.siffer i 'i'
         ii *= 10;  ii += forsteSiffer;         //  Legger siffer til bakerst.

         if (faktor * i == ii) {                //  Stemmer regnestykket med
            cout << "\t\t" << faktor << " * "   //    at er lagt til bakerst?
                 << i << " = " << ii << '\n';
            losning = true;                     //  Minst en løsning funnet.
         }
      }
  }

  if (!losning)  cout << "\n\n\tIngen løsning funnet!";

  cout << "\n\n";
  return 0;
}
