/**
 *   Programeksempel nr 5 - Infix til Postfix regneuttrykk.
 *
 *   Eksempel som viser bruk av stack i et helt konkret og praktisk tilfelle:
 *   Et infix regneuttrykk leses og omgj�res (skrives ut p� skjermen) til et
 *   postfix regnuttrykk.
 *   EKS_06_PostfixTilSvar.cpp finner svaret p� et slikt postfix-uttrykk.
 *
 *   F.eks.  (( 8 + 12 ) * ( 17 + 4 ))  omgj�res til:   8 12 + 17 4 + *
 *
 *   Algoritme: - pusher operatorene '+' og '*'
 *              - skriver rett ut igjen sifre/tall
 *              - pop'er og skriver operator n�r finner en ')' (sluttparentes)
 *              - ignorerer '('  (startparentes)
 *
 *   NB: Infix-utrykket M�:
 *       - v�re et lovlig uttrykk (med korrekt operatorbruk/antall parenteser)
 *       - kun inneholde operatorene '+' og '*' (i tillegg til '(' og ')')
 *       - starte med '(', og avslutte med ')'
 *       - ha minst EN blank ETTER hvert tall (men ikke n�dvendigvis FORAN)
 *
 *   @file     EKS_05_InfixTilPostfix.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                  //  cout
#include <stack>                     //  stack fra STL
using namespace std;


/**
 *  Skriver HELE en stakks innhold.
 *
 *  @param   st - KOPI av medsendt stack-container (derfor t�mmes den)
 */
void skriv(stack <char> st)  {
   while (!st.empty())  {              //  Enn� elementer igjen:
       cout << ' ' << st.top();        //  Skriver den n�v�rende f�rste.
       st.pop();                       //  Tar ut/fjerner den f�rste.
   }
   cout << '\n';
}


/**
 *  Hovedprogrammet:
 */
int main()  {
    stack <char> stakk;                     //  Stakk med char'er.
    char tegn;                              //  Innlest tegn fra tastaturet.

    cout << "\n\nSkriv et infix-regneuttrykk:\n";
                                            //  Leser ALLE tegn, ogs� ' '
    while ((tegn = cin.get()) != '\n') {    //    (blank), frem til '\n':
        if (tegn == ')') {                  //  Sluttparentes funnet:
            cout << stakk.top();            //  Skriver stakkens �verste tegn.
            stakk.pop();                    //  Tar ut/fjernet operatoren.
                                            //  Pusher '+' og '*':
        } else if (tegn == '+' || tegn == '*')  stakk.push(tegn);
                                                //  S� lenge sifre i ETT tall:
        while (tegn >= '0'  &&  tegn <= '9') {  // Skriver ut flersifret tall:
            cout << tegn;                       // Skriver ETT siffer.
            tegn = cin.get();                   // Leser neste siffer/tegn.
        }

        if (tegn != '(')                    //  Skriver ut en blank (viktig at
            cout << ' ';                    //    gj�res etter hvert tall).
     skriv(stakk);         //  Kommenter da vekk de 3x andre cout'ene.
                             //  Ignorer duplikate utskriftslinjer!
    }

    cout << "\n\n";
    return 0;
}
