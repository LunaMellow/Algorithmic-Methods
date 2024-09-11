/**
 *   L�sningsforslag til oppgave nr 26.
 *
 *   Oppgaven kan l�ses ved � bes�ke nodene flere ganger (backtracking),
 *   og s� for hver gang sette inn alle lovlige og aktuelle verdier i hver
 *   node etter tur. 
 *   Men, den kan ogs� (og enda enklere) l�ses ved � permutere sifrene 0-9,
 *   inntil den rette summen for hver av nodenes naboer oppst�r.
 *   Dette siste er valgt/kodet i dette l�sningsforslaget.
 *
 *   Ny kode er derfor:  Nabomatrisen 'gNabo', summen av hver nodes 
 *   naboer ligger i 'gSum', permuteringsarrayen er 'gArray' og funksjonen
 *   som sjekker lovlighet/gyldighet for denne arrayen heter 'sjekk'.
 *
 *   @file	  OPPG_26.CPP
 *   @author  Frode Haug, NTNU
 */


#include <iostream>
using namespace std;


const int N = 10;            ///<  Antall noder i grafen.

                             ///   Nabomatrisen:
         // Node nr:  0  1  2  3  4  5  6  7  8  9       Node nr: 
int gNabo[N][N] = { { 0, 1, 1, 0, 0, 0, 0, 1, 1, 0 },    //  0
                    { 1, 0, 0, 0, 1, 0, 1, 0, 0, 0 },    //  1
                    { 1, 0, 0, 0, 1, 1, 1, 0, 0, 0 },    //  2
                    { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },    //  3
                    { 0, 1, 1, 1, 0, 0, 1, 1, 1, 1 },    //  4
                    { 0, 0, 1, 0, 0, 0, 1, 1, 0, 0 },    //  5
                    { 0, 1, 1, 0, 1, 1, 0, 1, 1, 1 },    //  6
                    { 1, 0, 0, 0, 1, 1, 1, 0, 0, 1 },    //  7
                    { 1, 0, 0, 0, 1, 0, 1, 0, 0, 1 },    //  8
                    { 0, 0, 0, 0, 1, 0, 1, 1, 1, 0 } };  //  9
int gSum[N] = { 21, 33, 14, 27, 1, 14, 20, 12, 28, 20 }; ///< Nodenes nabosum.
int gArray[N] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };   ///<  Nodenes aktuelle ID.


void bytt(int & tall1, int & tall2);
void permuter(int arr[], const int i, const int n);
void roterVenstre(int arr[], const int i, const int n);
bool sjekk(const int arr[], const int n);


/**
 *  Hovedprogrammet:
 */
int main() {

    permuter(gArray, 0, N);

    cout << "\n\n";
    return 0;
}


// ***************************************************************************
// * De tre neste funksjonene er hentet rett fra/helt identiske til EKS_19:  *
// ***************************************************************************

/**
*  Bytter om to referanseoverf�rte variables innhold.
*
*  @param   tall1  -  Verdien som skal byttes med 'tall2' (referanseoverf�rt)
*  @param   tall2  -  Verdien som skal byttes med 'tall1' (referanseoverf�rt)
*/
void bytt(int & tall1, int & tall2) {
    int temp = tall1;           //  Midlertidig (temporary) unnalagring.
    tall1 = tall2;
    tall2 = temp;
}


/**
 *  Genererer rekursivt ALLE mulige permutasjoner av innholdet i 'arr'.
 *
 *  @param   arr  -  Arrayen som skal permuteres
 *  @param   i    -  Indeksen som ALLE ETTERF�LGENDE verdier skal flyttes til
 *  @param   n    -  Antall elementer i arrayen (siste indeks brukt er n-1)
 *  @see     bytt(...)
 *  @see     sjekk()
 *  @see     roterVenstre(...)
 */
void permuter(int arr[], const int i, const int n) {
    if (i == n-1)                       //  N�dd en ny permutasjon:
        sjekk(arr, n);                  //  Skriver ut arrayens innhold.
    else {                              //  Skal permutere:
        permuter(arr, i+1, n);          //  Beholder n�v�rende nr.'i'.
                                        //    Permuterer resten.
        for (int t = i+1;  t < n;  t++) {
            bytt(arr[i], arr[t]);       //  Bytter nr.'i' etter tur med
                                        //    ALLE de andre etterf�lgende.
            permuter(arr, i+1, n);      //  For hver av ombyttene: permuterer
        }                               //     resten av de etterf�lgende.
        roterVenstre(arr, i, n);        //  Gjenoppretter opprinnelig array!!!
    }
}


/**
 *  Venstreroterer en array innhold.
 *
 *  @param   arr  -  Arrayen som f�r (deler av) sitt innhold venstrerotert
 *  @param   i    -  Laveste indeks som skal venstreroteres
 *  @param   n    -  'n-1' er h�yeste indeks som venstreroteres
 */
void roterVenstre(int arr[], const int i, const int n) {
    int venstreVerdi = arr[i];            //  Tar vare p� f�rste.
    for (int k = i+1;  k < n;  k++)       //  Roterer (flytter alle ned
        arr[k-1] = arr[k];                //     ETT hakk/indeks).
    arr[n-1] = venstreVerdi;              //  Legger f�rste inn bakerst.
}


// ******************
// *  Ny funksjon:  *
// ******************
/**
 *  Sjekker om 'arr' inneholder en lovlig/aktuell l�sning.
 *
 *  @para m   arr  -  Arrayen som skal sjekkes for lovlighet
 *  @param    n    -  Antall elementer i arrayen (siste indeks brukt er n-1)
 *  @return   Om 'arr' inneholder en lovlig/aktuell l�sning eller ei
 */
bool sjekk(const int arr[], const int n) { 
    int i, j, tot;                              //  L�kkevariable og totalsum.

        for (i = 0;  i < n;  i++) {             //  G�r gjennom alle nodene:
            tot = 0;                            //  Nullstiller totalsummen.
            for (j = 0;  j < n;  j++)           //  G�r gjennom nodens naboer:
                if (gNabo[i][j])  tot += arr[j];   // Naboer? Summerer opp.
            if (tot != gSum[arr[i]]) return false; // Feil totalsum? Avbryter.
        }
                                                //  Funnet en l�sning!!
    for (i = 0; i < n; i++)  cout << "\nIndeks nr." << i << ": " << arr[i];
    cout << "\n\n";
    return true;
}