/**
 *   Løsningsforlag til eksamen i AlgMet, desember 2021, oppgave 4.
 *
 *   @file     EX_H21_4.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
using namespace std;


/**
 *  Skriver ut hele en arrays innhold på skjermen.
 *
 *  @param   tekst  -  Del av innledende ledetekst
 *  @param   arr    -  Arrayen hvis hele innhold skrives ut på skjermen
 *  @param   len    -  Antall elementer i arrayen, indeksert 0 til len-1
 */
void skriv(const char tekst[], const int arr[], const int len)  {
  cout << "\nArrayen " << tekst << ":  ";
  for (int i = 0;  i < len;  i++)
      cout << "  " << arr[i];
  cout << '\n';
}


/**
 *  Fletter sammen to sorterte arrayer, UTEN å bruke ekstra memoryplass.
 *
 *  @param   a     -  Arrayen med ledig plass, der det sammenflettede legges
 *  @param   b     -  Arrayen som skal flettes inn i arrayen 'a'
 *  @param   aLen  -  Antall elementer i arrayen 'a'
 *  @param   bLen  -  Antall elementer i arrayen 'b'
 */
void flettToSorterteArrayer(int a[], const int b[],
                            const int aLen, const int bLen) {
   int i, j, k,             //  Løkkevariable.
       bakerst = aLen-1;    //  Initierer til bakerste "skuff"/indeks.

   for (i = aLen-1;  i >= 0;  i--)  //  Flytter alle AKTUELLE tall
       if (a[i] != 0)               //     (IKKE 0 (null)) til bakerst i
          a[bakerst--] = a[i];      //     'a'-arrayen.
                                    //  NB:  Kan IKKE erstatte a[i] med '0'!!!
   skriv("A inni", a, aLen);

   i = bakerst+1;   j = k = 0;      //  'i' starter der første reelle tall
                                    //    er i 'a'.  'j' og 'k' på starten
                                    //    av arrayene 'b' og 'a'.
   while (i < aLen  &&  j < bLen)   //  Fletter sammen arrayene inn i 'a':
       if (a[i] < b[j])             //  Neste element i 'a' er minst:
          a[k++] = a[i++];
       else                         //  Neste element i 'b' er minst
          a[k++] = b[j++];          //    (eller likt).

   while (j < bLen)                 //  Om 'b' IKKE ble ferdiglest, MÅ dens
       a[k++] = b[j++];             //    tall legges til BAKERST i 'a'!!!
                                    //    Ble ikke 'a' ferdiglest, så ligger
}                                   //    tallene der allerede!!!


/**
 *  Hovedprogrammet:
 */
int main() {
    int arrA[15] =  { -8, -4, 0, 0, -1, 3, 0, 7, 0, 9, 11, 0, 0, 15, 19 };
    int arrB[6] =  { -10, -3, -1, 4, 9, 24};

    skriv("A før", arrA, 15);
    skriv("B før", arrB, 6);

    flettToSorterteArrayer(arrA, arrB, 15, 6);

    skriv("A etter", arrA, 15);

    cout << "\n\n";
    return 0;
}
