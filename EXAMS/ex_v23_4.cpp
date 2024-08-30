/**
 *   Løsningsforlag til ekstraeksamen i AlgMet, vår 2023, oppgave 4.
 *
 *   @file     EX_V23_4.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>             //  cout
#include <cstring>              //  strlen
using namespace std;

char tekst1[] = "ABCDEFGABCDEFGHIJKLKLMNQPAHGIJKLMNPWQERSTTRETSUVVUX";  //  W
char tekst2[] = "KTWRQOPDENSKTWRQOPDENSQOPDENSKTWRQOPDENSKTWRQOPDENS";  // ' '


/**
 *  OPPGAVE 4A - Finner og returnerer den første bokstaven i en tekst som
 *               forekommer bare EN gang, UTEN å unnalagre hjelpedata.
 *
 *  Orden:  N*N
 *
 *  @param    tekst  -  Teksten som skal gjennomgås/sjekkes
 *  @param    n      -  Lengden til/antall tegn i 'tekst'
 *  @return   FØRSTE bokstaven med bare EN forekomst, evt. ' ' (blank)
 */
char forsteSingleBokstav1(const char tekst[], const int n) {
   int i, j;                            //  Løkkevariable.
   bool duplikat;                       //  Funnet duplikat eller ei.

   for(i = 0;  i < n;  i++) {           //  For hver bokstav i teksten:
      duplikat = false;                 //  Antar ingen duplikat.
                                        //  Sjekker HELE teksten for duplikat:
      for(j = 0;  j < n;  j++)          //  IKKE korrekt bare at: 'j=i+1' !!!
                                        //  IKKE samme indeks, men like:
        if (i != j  &&  tekst[i] == tekst[j])  {
           duplikat = true;             //  Duplikat funnet!
//           break;                     //  Trenger ikke sammenligne videre.
        }
        if (!duplikat) return (tekst[i]); //  Ingen duplikater!
   }                                      //  Returnerer aktuell bokstav.
   return (' ');                          //  Ingen single/unike funnet
}                                         //    - returnerer ' ' (blank).


/**
 *  OPPGAVE 4B - Finner og returnerer den første bokstaven i en tekst som
 *               forekommer bare EN gang, VED å unnalagre hjelpedata.
 *
 *  Orden:  N    ( strengt tatt:  3/2 N )
 *
 *  @param    tekst  -  Teksten som skal gjennomgås/sjekkes
 *  @param    n      -  Lengden til/antall tegn i 'tekst'
 *  @return   FØRSTE bokstaven med bare EN forekomst, evt. ' ' (blank)
 */
char forsteSingleBokstav2(const char tekst[], const int n) {
   int i;                               //  Løkkevariabel.
   int antall[26];                      //  Telling av bokstavforekomster.

   for (i = 0;  i < 26;  i++)  antall[i] = 0;  //  Nullstiller hjelpearray.

   for (i = 0;  i < n;  i++)            //  Teller opp forekomsten av ALLE
       antall[tekst[i]-'A']++;          //    bokstavene i teksten.
                                        //  Finner og returnerer den FØRSTE i
   for (i = 0;  i < n;  i++)            //    teksten med bare EN forekomst:
       if (antall[tekst[i]-'A'] == 1)  return (tekst[i]);

   return (' ');                        //  Ingen single/unike funnet
}                                       //    - returnerer ' ' (blank).


/**
 *  Hovedprogrammet:
 */
int main() {

    //  Tester 4A:
    cout << "\nFørste unike forekomst i 'tekst1' er bokstaven:  '"
         << forsteSingleBokstav1(tekst1, strlen(tekst1)) << "'\n";
    cout << "\nFørste unike forekomst i 'tekst2' er bokstaven:  '"
         << forsteSingleBokstav1(tekst2, strlen(tekst2)) << "'\n";
    cout << "\nFørste unike forekomst i '' (tom tekst) er bokstaven:  '"
         << forsteSingleBokstav1("", 0) << "'\n\n\n";

    //  Tester 4B:
    cout << "\nFørste unike forekomst i 'tekst1' er bokstaven:  '"
         << forsteSingleBokstav2(tekst1, strlen(tekst1)) << "'\n";
    cout << "\nFørste unike forekomst i 'tekst2' er bokstaven:  '"
         << forsteSingleBokstav2(tekst2, strlen(tekst2)) << "'\n";
    cout << "\nFørste unike forekomst i '' (tom tekst) er bokstaven:  '"
         << forsteSingleBokstav2("", 0) << "'\n\n\n";

    return 0;
}
