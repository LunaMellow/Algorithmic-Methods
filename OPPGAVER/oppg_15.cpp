/**
 *   Løsningsforslag til oppgave nr 15 (liten utvidelse av EKS_25_Heap).
 *
 *   @file	  OPPG_15.CPP
 *   @author  Frode Haug, NTNU
 */


/**
 *   Endrer et gitt element til en ny verdi og opprettholder heap-betingelsen.
 *
 *   @param    keyNr    -  Elementnummeret som skal få ny verdi
 *   @param    nyVerdi  -  Den nye verdien som settes inn på 'data[keyNr]' 
 *   @see      upHeap(...)
 *   @see      downHeap(...)
 */
void change(const int keyNr, const T nyVerdi) {
    T verdi = data[keyNr];    //  Gjemmer unna nåværende verdi.
    data[keyNr] = nyVerdi;    //  Erstatter med ny verdi.
                              //  Up- eller downHeaper ut fra om den 'nyVerdi'
                              //    er større eller mindre enn den erstattede:
    if (nyVerdi >= verdi)  upHeap(keyNr);
    else                   downHeap(data, antall, keyNr);
}



/**
 *   Fjerner/sletter helt et gitt elementnummer.
 *
 *   @param    keyNr    -  Elementnummeret som skal fjernes/slettes
 *   @see      upHeap(...)
 *   @see      downHeap(...)
 */
void extract(const int keyNr) {
    T verdi = data[keyNr];         //  Gjemmer unna slettet element
    data[keyNr] = data[antall--];  //  Flytter BAKERSTE til dennes plass.
                               //  Up- eller downHeaper ut fra om den flyttede
                               //    er større eller mindre enn den slettede:
    if (verdi <= data[keyNr]) upHeap(keyNr);
    else                      downHeap(data, antall, keyNr);
}