/**
 *   Løsningsforslag til oppgave nr 1 (liten utvidelse av EKS_01_Vector).
 *
 *   @file	  OPPG_01.CPP
 *   @author  Frode Haug, NTNU
 */


/**
 *   Smetter inn (om mulig) verdien 't' i posisjon/indeks nr 'pos'.
 *
 *   @param    pos  -  Posisjonen/indeksen der ny verdi skal inn
 *   @param    t    - Verdien som smettes/settes inn
 *   @return   Om innsmetting lyktes eller ei.
 *   @see      resize(...)
 */
bool insert(const int pos, const T t) {
    if (antall == kapasitet)          //  NYTT: Fullt, øker derfor
       resize(kapasitet + 100);       //  NYTT:   arrayens kapasitet med +100.

    if (pos >= 0 && pos <= antall) {  //  Identisk kode til EKS_01_Vector.cpp:
       for (int i = antall; i > pos; i--)
           data[i] = data[i - 1];
       data[pos] = t;
       antall++;
       return true;
    } else
      cout << "\nIndex out of bounds .....\n\n"; // Egen melding ??
      return false;
}


/**
 *   Øker arrayens ('data') lengde til 'nyLengde' lang.
 *
 *   @param   nyLengde  -  Ny lengde/'kapasitet' for arrayen 'data'
 */
void resize(const int nyLengde) {
    T* nyeData;                      //  Peker til den nye og lengre arrayen.
    if (nyLengde > kapasitet) {      //  Ny kapasitet er større enn nåværende:
        kapasitet = nyLengde;        //  Oppdaterer ny kapasitet.
        nyeData = new T[nyLengde];   //  Lager ny og lengre array.
        for (int i = 0;  i < antall;  i++)   //  Kopierer ALT fra nåværende  
            nyeData[i] = data[i];            //    array til den nye:
        delete [] data;              //  Sletter gammel array.  
        data = nyeData;              //  Flytter peker til den nye arrayen.
    } else
        cout << "\nNew capacity must be higher than current\n\n";
}