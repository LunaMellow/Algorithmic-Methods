/**
 *   Løsningsforslag til oppgave nr 7.
 *
 *   Program som finner grupper av nabobrikker i et rutenett.
 *
 *   (Dette var oppg.nr.4 på eksamen 13/12-1999 i L189A-Algoritmiske metoderI)
 *
 *   @file	  OPPG_07.CPP
 *   @author  Frode Haug, NTNU
 */


#include <iostream>
using namespace std;


const int N = 10;         ///<  Brettets størrelse.
const int BRIKKE = 1;     ///<  Står/er en brikke på en gitt plass/koordinat.
const int SEEN = 2;       ///<  Verdien for når en rute er ferdig besøkt.


int gBrett[N+2][N+2] =    ///<  Matrise som representerer brettet.
                          //    Alle rutene blir initielt automatisk '0'.
                          //    NB  NB  NB  NB  NB  NB  NB:
                          //       Bruker indeks 1-N !!!  Har derfor en ekstra
                          //       randkant rundt det hele for å slippe å
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
 *  Rekursiv funksjon som evt finner første brikken i en gruppe,
 *  og finner da antall brikker i denne gruppen.
 *
 *  @param   x       -  Aktuell rute å besøk sin x-koordinat (linje!)
 *  @param   y       -  Aktuell rute å besøk sin y-koordinat (kolonne!)
 *  @param   antall  -  Antall brikker i DENNE gruppen (referanseoverført!)
 */
void besokEnGruppe(int x, int y, int & antall) {
    if (gBrett[x][y] == BRIKKE) {  //  Står en brikke i ruten:
        antall++;                  //  Teller opp antall brikker i gruppen.
        gBrett[x][y] = SEEN;       //  Setter FOR GODT at er ferdig besøkt !!!
        cout << " (" << x << ',' << y << ')';   //  Skriver rutens indekser.
        besokEnGruppe(x, y+1, antall);  // Høyre      Besøker naborutene for
        besokEnGruppe(x+1, y, antall);  // Under      å finne ut om de er med
        besokEnGruppe(x, y-1, antall);  // Venstre    i gruppen:
        besokEnGruppe(x-1, y, antall);  // Over
    }
}
//  NB:  BACKTRACKING (som i plasseringen av dronninger) er IKKE aktuelt her.
//       (Hadde da HELT til slutt i if-setningen hatt:  gBrett[x][y] = BRIKKE)
//       Dette skyldes at vi IKKE skal finne alternative løsninger, men bare
//       telle opp antall grupper og antallet i hver EN eneste gang.


/**
 *  Hovedprogrammet:
 */
int main() {
    int antallGrupper = 0, antallIEnGruppen;   //  De to opptellingene.

    for (int i = 1; i <= N; i++)       //  Traverserer HELE brettet,
        for (int j = 1; j <= N; j++)   //  ALT på en og en linje nedover:
            if (gBrett[i][j] == BRIKKE) {  //  Funnet "starten" på en gruppe:
                                       //  Teller opp at funnet en ny gruppe:
                cout << "\nGruppe nr. " << ++antallGrupper
                     << " består av ruten(e):\n\t";
                antallIEnGruppen = 0;  //  Nullstiller antallet i gruppen.
                                       //  Besøker RESTEN av gruppen!!!:
                besokEnGruppe(i, j, antallIEnGruppen);
                                       //  Skriver referanseoverført variabel:
                cout << "\n\tAntall i gruppen: " << antallIEnGruppen;
            }

    cout << "\n\n";
    return 0;
}
