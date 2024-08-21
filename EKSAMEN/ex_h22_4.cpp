/**
 *   Løsningsforlag til eksamen i AlgMet, desember 2022, oppgave 4.
 *
 *   @file     EX_H22_4.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>     //  cout
#include <cmath>        //  sqrt
using namespace std;


/**
 *   Hovedprogram.
 */
int main()  {
  int   i, j,           //  Løkkevariable, der i = n (fra oppgaveteksten).
        sum,            //  Summen av alle heltallelige divisorer for 'i'.
        diff,           //  Differansen mellom 'sum' og '2*i'.
        kvad1;          //  HELTALLS kvadratrot av 'diff'.
  float kvad2;          //  FLYTTALLS kvadratrot av 'diff'.
  int   antall = 0;     //  Totalt antall aktuelle tall funnet.


  for (i = 1;  i < 1000000;  i++) {   //  Går gjennom alle aktuelle tall:
      sum = i;                        //  Initierer 'sum' til tallet selv.
                                      if (i % 50000 == 0)  cout << i << '\n';
      for  (j = 1;  j <= i/2;  j++)   //  Går max. opp til halve tallet:
         if (i % j == 0)              //  Heltallelig dividerbar:
            sum += j;                 //  Oppdaterer totalsummen.

      if (sum > 2*i)  {               //  Totalsummen større enn '2*i':
         diff = sum - (2*i);          //  Finner differansen dem imellom.
         kvad2 = sqrt(diff);          //  Beregner dets kvadratrot (float).
         kvad1 = kvad2;               //  Gjør om til int!
         if (kvad1 == kvad2)  {       //  int og float er like:
            antall++;                 //  Teller opp antallet funnet.
//            cout << "i: " << i << "   2i: " << 2*i << "   sum: " << sum
//                 << "   Diff: " << diff << "     kvad1: " << kvad1
//                 << "   kvad2: " << kvad2 <<  "     Antall: " << antall << '\n';
//            getchar();
         }
      }
  }

  printf("\n\nAntallet:  %i\n\n", antall);  //  Skriver ut oppgavens svar
                                            //    (som er 705).
  return 0;
}
