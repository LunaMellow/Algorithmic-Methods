/**
 *   Løsningsforslag til oppgave nr 2.
 *
 *   Programmet er en selvlaget implementasjon av container-klassen Map.
 *   Det er laget kode for følgende funksjoner:
 *
 *     -  Map(final int lengde);                        default = 200
 *     -  void     change(final T1 key, final T2 da);
 *     -  void     display();
 *     -  void     erase(final T1 key);
 *     -  boolean  find(final T1 key);
 *     -  T2       get(final T1 key);
 *     -  void     insert(final T1 key, final T2 da);
 *     -  int      size();
 *
 *
 *   Generelt om forskjellen ift. C++-koden:  Se HELT til slutt i denne filen.
 *
 *
 *   @file     Oppg_02.java
 *   @author   Marius Lindvall, NTNU
 */



/**
 *  Container-klassen Map, som er en selvlaget versjon av Java's <Map>.
 *
 *  Inneholder en array med keyer og en array med keyenes tilhørende data av 
 *  typen 'T'. Har også to int'er som angir total kapasitet/lengde (capacity),
 *  det nåværende antallet (size) i map'en.
 */
public class Oppg_02 {
                                        //  'T1' og 'T2': fleksible datatyper!
    static class Map<T1 extends Comparable<T1>, T2> {
        private T1[] keyer;             //  Array av typen 'T1' (keyer).
        private T2[] data;              //  Array av typen 'T2' (data).
        private int kapasitet, antall;  //  Max.lengde og nåværende antall.
        
        public Map() { this(200); };    //  I Java finnes ikke default parameter slik
                                        //  som i C++. Løsningen er i stedet å lage to
                                        //  konstruktorer, én med og én uten parameter,
                                        //  og la sistnevnte kalle førstnevnte med
                                        //  verdien(e) som skal være default.
        public Map(final int lengde) {  keyer = (T1[]) new Comparable[lengde];
                                        data  = (T2[]) new Object[lengde];
                                        kapasitet = lengde;  antall = 0;  }
        
                                        //  Endrer (om mulig) en allerede eksisterende
        public void change(final T1 key, final T2 da) {     //  keys tilhørende data:
            int i;
            if (find(key)) {                                //  Key'en finnes:
                for (i = 0; i < antall; i++)                //  Finner dens indeks:
                    if (keyer[i].equals(key)) break;
                data[i] = da;                               //  Oppdaterer keyens
            } else                                          //    tilhørende data.
                System.out.println("\nKey doesn't exists!\n");  //  Egen melding ??
        }
        
        public void display() {         //  Skriver HELE map'ens innhold:
            for (int i = 0; i < antall; i++)
                System.out.println("\t" + keyer[i] + ": " + data[i]);
            System.out.println("\n\tAntall keyer m/data i map'en:  " + antall);
        }
        
                                            //  Sletter (om mulig) helt paret med
        public void erase(final T1 key) {   //    angitt key og dets data:
            int i;
            if (find(key)) {                                //  Key'en finnes:
                for (i = 0; i < antall; i++)                //  Finner dens indeks:
                    if (keyer[i].equals(key)) break;
                antall--;                                   //  Totalantallet minskes.
                for (int j = i; j < antall; j++) {          //  ALLE etterfølgende
                    keyer[j] = keyer[j+1];                  //    flyttes ned ETT
                    data[j] = data[j+1];                    //    hakk.
                }
            } else
                System.out.println("\nKey doesn't exists!\n");  //  Egen melding ??
        }
        
        public boolean find(final T1 key) {  //  Finner (om mulig) en key:
            for (int i = 0; i < antall; i++)
                if (keyer[i].equals(key)) return true;  //  Funn!
            return false;                    //  Loop ferdig - ingen funn!
        }
        
        public T2 get(final T1 key) {   //  Henter ut (om mulig) en keys tilhørende data:
            for (int i = 0;  i < antall;  i++)
                if (keyer[i].equals(key)) return data[i];  // Funn!
            return null;                //  Loop ferdig - ingen funn!
        }
        
                                                         //  Setter inn (om mulig) et
        public void insert(final T1 key, final T2 da) {  //  nytt par med key og data:
            int nyIndeks = 0;               //  Indeks der ny skal inn.
            if (!find(key)) {               //  'key' finnes IKKE fra før:
                if (antall < kapasitet) {   //  Fortsatt plass til flere i mapen:
                                            //  Leter etter der skal smettes inn:
                    while (nyIndeks < antall && keyer[nyIndeks].compareTo(key) < 0)
                        nyIndeks++;
                    antall++;               //  Totalantallet økes med +1. 
                    for (int i = antall-1;  i > nyIndeks;  i--) {
                        keyer[i] = keyer[i-1];         //  Flytter alle ETTER opp
                        data[i] = data[i-1];           //    ETT hakk.
                    }
                    keyer[nyIndeks] = key;  //  S(m)etter inn det nye paret av 
                    data[nyIndeks] = da;    //     key og dets tilhørende data.
                } else
                    System.out.println("\nMap is already full!\n");  //  Egen melding ??
            } else
                System.out.println("\nKey already exists!\n");       //  Egen melding ??
        }
        
        public int size() { return antall; }
    }
    

    /**
     *  Hovedprogrammet:
     */
    public static void main(String[] args) {
        Map<Integer, String> mengde = new Map<>();
        
        mengde.insert(49, "FN"); mengde.insert(12, "TO"); mengde.insert( 7, "SY");
        mengde.insert(23, "TT"); mengde.insert(63, "ST"); mengde.insert(53, "TR");
        mengde.insert(42, "FT"); mengde.insert(15, "FE"); mengde.insert( 5, "FE");
        mengde.display();

        mengde.insert(23, "TT");        //  Finnes allerede!

        mengde.erase(49);   mengde.erase(5);  mengde.erase(63);
        mengde.display();

        mengde.erase(22);               //  Finnes IKKE!

        mengde.change(12, "TOLV");   mengde.change(15, "FEMTEN");
        mengde.display();

        mengde.change(96, "NS");        //  Finnes IKKE!
    
        System.out.print("\n\n");
    }

}


/*************************************************************************************** 

 Noen viktige og påkrevde forskjeller ift. C++-versjonen:

 - Java har ikke default parameter, men benytter overloading i stedet. Derfor to constructorer.
 - Arrayene i arrays og ikke pekere, siden pekere ikke brukes som kodekonsept i Java.
 - Det finnes ingen "god" måte å initialisere generic-type arrays i Java. 
   Det er brukt cast fra Comparable/Object-array til T1/T2-array i stedet,
   jfr. https://stackoverflow.com/a/2924453

***************************************************************************************/
