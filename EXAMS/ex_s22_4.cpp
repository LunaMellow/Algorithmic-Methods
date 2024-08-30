/**
 *   Løsningsforlag til eksamen i AlgMet, august 2022, oppgave 4.
 *
 *   @file     EX_S22_4.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;


int tallene[1000000];                    ///<   Alle de 1 million tallene.


/**
 *  Hovedprogrammet:
 */
int main()  {
   float  sum = 0;                       //  TOTALsummen av de økende tallene.
   int    i = 0,                         //  Indeks-variabel.
          tall,                          //  Aktuelt tall innlest/å behandle.
          storste = -1,                  //  Største tall registrert hittil.
          antall = 0;                    //  Antall tall i totalsummen.


//  IKKE EN DEL AV OPPGAVEN  (frem til stjernelinje):

   ifstream innfil("ex_s22_4.dta");      //  Åpner aktuell vil med
                                         //    1 million tall.
   if (innfil)  {                        //  Filen finnes.
      innfil >> tall;                    //  Leser (om mulig) ETT tall.
      while (!innfil.eof())  {           //  Ennå ikke nådd filslutt:
        tallene[i++] = tall;             //  Lagrer unna innlest tall.
        innfil >> tall;                  //  Leser (om mulig) NESTE tall.
      }
   } else                                //  Filen lot seg ikke finne/åpne:
     cout << "\n\nFant ikke filen 'EX_S22_4.DTA'!\n\n";

// *************************************************************************

//  HOVEDDELEN AV OPPGAVEN:

      for (i = 0;  i < 1000000;  i++)  {  //  Går igjennom de 1 mill.tallene:
          tall = tallene[i];               //  Henter aktuelt tall.
          if (tall >= storste)  {          //  Større eller lik et tidligere:
             antall++;                     //  Antallet telles opp.
//                                cout << tall << '\n';
             sum += tall;                  //  Totalsummen oppdateres.
             storste = tall;               //  Tar vare på det hittil største
          }                                //    registrerte tallet.
      }

      cout << fixed <<  setprecision(0);   //  Skriver ur resultatene:
      cout << "\n\nSummen av tallene er: " << sum;
      cout << "\n\nAntall tall summert: " << antall << "\n\n";

  return 0;
}
