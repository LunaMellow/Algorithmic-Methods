/**
 *   Løsningsforlag til eksamen i AlgMet, november 2020, oppgave 4.
 *
 *   @file     EX_H20_4.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>             //  cout
using namespace std;


//  Ulike int-arrayer for testing av 'fjernDuplikater(...):
int t1[] = { 0 };                                               //  n = 0
int t2[] = { 0,  7 };                                           //  n = 1
int t3[] = { 0,  7, 11, 12, 17 };                               //  n = 4
int t4[] = { 0,  7,  7,  7,  7,  7,  7 };                       //  n = 6
int t5[] = { 0,  7,  7,  9,  9, 11, 11, 13, 13 };               //  n = 8
int t6[] = { 0,  7,  7,  9, 10, 11, 11, 12, 13, 14, 14, 14 };   //  n = 11
int t7[] = { 0,  1,  1,  2,  2,  3,  3,  3,  3, 11, 12, 12,     //  n = 33
                12, 13, 14, 14, 18, 18, 19, 20, 21, 21, 22,
                22, 26, 26, 26, 27, 27, 28, 28, 29, 29, 30 };


/**
 *  OPPGAVEN - Komprimerer en array ved å fjerne duplikater, fyller på med
 *  0 (nuller) bakerst, og returnerer antall UNIKE tall i arrayen etterpå.
 *
 *  Forutsetning:   a[0] != a[1]   og at n >= 0.
 *
 *  @param    a  -  Array som får duplikater fjernet, og fylt på med 0'er
 *  @param    n  -  Initielt antall tall i 'a'
 *  @return   Antall UNIKE tall i 'a'
 */
int fjernDuplikater(int a[], const int n) {
    int i, j = 0;                        //  j = antall ulike/unike tall.

    if (n <= 1)  return n;               //  Null eller ett element i 'a'.

    for (i = 1;  i <= n;  i++)   //  Om a[i-1]==a[i] flyttes a[i] IKKE frem:
        if (a[i-1] != a[i])  a[++j] = a[i];
                                 //  Fyller resten av 'a' (etter 'j') med '0':
    for (i = j+1;  i <= n;  i++)  a[i] = 0;

    return j;
}


/**
 *  Skriver ut hele en int-arrays innhold.
 *
 *  @param   tall  -  Arrayen som får sitt innhold skrevet ut på skjermen
 *  @param   n     -  Antall tall i arrayen, liggende i indeks 1 til n
 */
void skriv(const int tall[], const int n) {
  for (int i = 1;  i <= n;  i++)  cout << ' ' << tall[i];
}


/**
 *  Hovedprogrammet:
 */
int main() {

    cout << "\n\n't1' før: ";     skriv(t1, 0);
    cout << "\nAntall ulike: " << fjernDuplikater(t1, 0);
    cout << "\n't1' etter: ";     skriv(t1, 0);

    cout << "\n\n't2' før: ";     skriv(t2, 1);
    cout << "\nAntall ulike: " << fjernDuplikater(t2, 1);
    cout << "\n't2' etter: ";     skriv(t2, 1);

    cout << "\n\n't3' før: ";     skriv(t3, 4);
    cout << "\nAntall ulike: " << fjernDuplikater(t3, 4);
    cout << "\n't3' etter: ";     skriv(t3, 4);

    cout << "\n\n't4' før: ";     skriv(t4, 6);
    cout << "\nAntall ulike: " << fjernDuplikater(t4, 6);
    cout << "\n't4' etter: ";     skriv(t4, 6);

    cout << "\n\n't5' før: ";     skriv(t5, 8);
    cout << "\nAntall ulike: " << fjernDuplikater(t5, 8);
    cout << "\n't5' etter: ";     skriv(t5, 8);

    cout << "\n\n't6' før: ";     skriv(t6, 11);
    cout << "\nAntall ulike: " << fjernDuplikater(t6, 11);
    cout << "\n't6' etter: ";     skriv(t6, 11);

    cout << "\n\n't7' før: ";     skriv(t7, 33);
    cout << "\nAntall ulike: " << fjernDuplikater(t7, 33);
    cout << "\n't7' etter: ";     skriv(t7, 33);

    cout << "\n\n";
    return 0;
}
