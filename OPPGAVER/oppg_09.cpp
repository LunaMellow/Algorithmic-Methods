/**
 *   Løsningsforslag til oppgave nr 9.
 *
 *   Programmet et HELT identisk til EKS_19_Permutering.cpp,
 *   bortsett fra at det i 'permuter' er gjort tre utvidelser:
 *     - if-setningen foran kallet av 'display' utvides med:
 *           &&  arr[i]-arr[i-1] != 1  &&  arr[i-1]-arr[i] != 1    
 *     - Foran begge de rekursive kallene av 'permuter', 
 *       legges følgende if-setning inn:
 *           if (i == 0  ||  (arr[i]-arr[i-1] != 1  &&  arr[i-1]-arr[i] != 1))
 *
 *   @file	  OPPG_09.CPP
 *   @author  Frode Haug, NTNU
 */


#include <iostream>
using namespace std;


/**
 *  Hovedprogrammet:
 */
int main() {

    cout << "\n\n\nLes/se denne kodefilens heading/innledning .....\n\n";

    return 0;
}