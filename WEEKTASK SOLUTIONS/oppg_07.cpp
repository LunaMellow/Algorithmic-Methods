/**
 *   L�sningsforslag til oppgave nr 7.
 *
 *   Program som finner grupper av nabobrikker i et rutenett.
 *
 *   (Dette var oppg.nr.4 p� eksamen 13/12-1999 i L189A-Algoritmiske metoderI)
 *
 *   @file	  OPPG_07.CPP
 *   @author  Frode Haug, NTNU
 */


#include <iostream>
using namespace std;


const int N = 10;         ///<  Brettets st�rrelse.
const int BRIKKE = 1;     ///<  St�r/er en brikke p� en gitt plass/koordinat.
const int SEEN = 2;       ///<  Verdien for n�r en rute er ferdig bes�kt.


int gBrett[N+2][N+2] =    ///<  Matrise som representerer brettet.
                          //    Alle rutene blir initielt automatisk '0'.
                          //    NB  NB  NB  NB  NB  NB  NB:
                          //       Bruker indeks 1-N !!!  Har derfor en ekstra
                          //       randkant rundt det hele for � slippe �
                          //       sjekke om EGENTLIG er utenfor brettet !!!!!
          { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },  //  Setter opp brikker
            { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0 },  //  likt med det i
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },  //  oppgaveteksten:
            { 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 },
            { 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
            { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
            { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };


/**
 *  Rekursiv funksjon som evt finner f�rste brikken i en gruppe,
 *  og finner da antall brikker i denne gruppen.
 *
 *  @param   x       -  Aktuell rute � bes�k sin x-koordinat (linje!)
 *  @param   y       -  Aktuell rute � bes�k sin y-koordinat (kolonne!)
 *  @param   antall  -  Antall brikker i DENNE gruppen (referanseoverf�rt!)
 */
void besokEnGruppe(int x, int y, int & antall) {
    if (gBrett[x][y] == BRIKKE) {  //  St�r en brikke i ruten:
        antall++;                  //  Teller opp antall brikker i gruppen.
        gBrett[x][y] = SEEN;       //  Setter FOR GODT at er ferdig bes�kt !!!
        cout << " (" << x << ',' << y << ')';   //  Skriver rutens indekser.
        besokEnGruppe(x, y+1, antall);  // H�yre      Bes�ker naborutene for
        besokEnGruppe(x+1, y, antall);  // Under      � finne ut om de er med
        besokEnGruppe(x, y-1, antall);  // Venstre    i gruppen:
        besokEnGruppe(x-1, y, antall);  // Over
    }
}
//  NB:  BACKTRACKING (som i plasseringen av dronninger) er IKKE aktuelt her.
//       (Hadde da HELT til slutt i if-setningen hatt:  gBrett[x][y] = BRIKKE)
//       Dette skyldes at vi IKKE skal finne alternative l�sninger, men bare
//       telle opp antall grupper og antallet i hver EN eneste gang.


/**
 *  Hovedprogrammet:
 */
int main() {
    int antallGrupper = 0, antallIEnGruppen;   //  De to opptellingene.

    for (int i = 1; i <= N; i++)       //  Traverserer HELE brettet,
        for (int j = 1; j <= N; j++)   //  ALT p� en og en linje nedover:
            if (gBrett[i][j] == BRIKKE) {  //  Funnet "starten" p� en gruppe:
                                       //  Teller opp at funnet en ny gruppe:
                cout << "\nGruppe nr. " << ++antallGrupper
                     << " best�r av ruten(e):\n\t";
                antallIEnGruppen = 0;  //  Nullstiller antallet i gruppen.
                                       //  Bes�ker RESTEN av gruppen!!!:
                besokEnGruppe(i, j, antallIEnGruppen);
                                       //  Skriver referanseoverf�rt variabel:
                cout << "\n\tAntall i gruppen: " << antallIEnGruppen;
            }

    cout << "\n\n";
    return 0;
}
