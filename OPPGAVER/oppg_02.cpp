/**
 *   Løsningsforslag til oppgave nr 2.
 *
 *   Programmet er en selvlaget implementasjon av container-klassen Map.
 *   Det er laget kode for følgende funksjoner:
 *
 *     -  Map(const int lengde = 200);
 *     -  ~Map();
 *     -  void change(const T1 key, const T2 da);
 *     -  void  display();
 *     -  void  erase(const T1 key);
 *     -  bool  find(const T1 key);
 *     -  T2    get(const T1 key);
 *     -  void  insert(const T1 key, const T2 da);
 *     -  int   size();
  *
 *   NB: For å formodentlig øke leseligheten og oversikten er medlems-
 *       funksjonene bevisst IKKE koemmentert etter Doxygen-standarden.
*
 *   @file     OPPG_02.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                  //  cout
#include <string>                    //  string
using namespace std;


/**
 *  Container-klassen Map, som er en selvlaget versjon av STLs <map>.
 *
 *  Inneholder en array med keyer og en array med keyenes tilhørende data av
 *  typen 'T'. Har også to int'er som angir total kapasitet/lengde (capacity),
 *  det nåværende antallet (size) i map'en.
 */
template <typename T1, typename T2>  //  T1' og 'T2': fleksible datatyper!
class Map {

  private:
      T1* keyer;                    //  PEKER til array av typen 'T1' (keyer).
      T2* data;                     //  PEKER til array av typen 'T2' (data).
      int kapasitet, antall;        //  Max.lengde og nåværende antall.

  public:                      //  Initierer medlemmer vha. default parameter:
      Map(const int lengde = 200) {  keyer = new T1[lengde];
                                     data  = new T2[lengde];
                                     kapasitet = lengde;   antall = 0;  }

                                    // Frigir allokert memory (vha.'new'):
      ~Map()  {  delete[] keyer;   delete[] data; }


                                //  Endrer (om mulig) en allerede eksisterende
      void change(const T1 key, const T2 da)   {     //  keys tilhørende data:
          int i;
          if (find(key)) {                           //  Key'en finnes:
              for (i = 0; i < antall; i++)           //  Finner dens indeks:
                  if (keyer[i] == key)  break;
              data[i] = da;                          //  Oppdaterer keyens
          } else                                     //    tilhørende data.
            cout << "\nKey doesn't exists!\n\n";     //  Egen melding ??
      }


      void display() {                       //  Skriver HELE map'ens innhold:
          for (int i = 0; i < antall; i++)
              cout << '\t' << keyer[i] << ": " << data[i] << '\n';
          cout << "\n\tAntall keyer m/data i map'en:  " << antall << '\n';

      }

                                      //  Sletter (om mulig) helt paret med
      void erase(const T1 key)  {     //    angitt key og dets data:
          int i;
          if (find(key)) {                          //  Key'en finnes:
              for (i = 0; i < antall; i++)          //  Finner dens indeks:
                  if (keyer[i] == key)  break;
              antall--;                             //  Totalantallet minskes.
              for (int j = i; j < antall; j++) {    //  ALLE etterfølgende
                  keyer[j] = keyer[j+1];            //    flyttes ned ETT
                  data[j] = data[j+1];              //    hakk.
              }
          } else
            cout << "\nKey doesn't exists!\n\n";    //  Egen melding ??
      }


      bool find(const T1 key) const {            //  Finner (om mulig) en key:
          for (int i = 0;  i < antall;  i++)
              if (keyer[i] == key)  return true;     //  Funn!
          return false;                          //  Loop ferdig - ingen funn!
      }

                                                 //  Henter ut (om mulig) en
      T2 get(const T1 key) const  {              //    keys tilhørende data:
          for (int i = 0;  i < antall;  i++)
              if (keyer[i] == key)  return data[i];  // Funn!
          return T2();                           //  Loop ferdig - ingen funn!
      }

                                                 //  Setter inn (om mulig) et
      void insert(const T1 key, const T2 da) {   //  nytt par med key og data:
          int nyIndeks = 0;              //  Indeks der ny skal inn.
          if (!find(key)) {              //  'key' finnes IKKE fra før:
             if (antall < kapasitet) {   //  Fortsatt plass til flere i mapen:
                                         //  Leter etter der skal smettes inn:
                 while (nyIndeks < antall  &&  keyer[nyIndeks] < key)
                       nyIndeks++;
                 antall++;               //  Totalantallet økes med +1.
                 for (int i = antall-1;  i > nyIndeks;  i--) {
                     keyer[i] = keyer[i-1];         //  Flytter alle ETTER opp
                     data[i] = data[i-1];           //    ETT hakk.
                 }
                 keyer[nyIndeks] = key;   //  S(m)etter inn det nye paret av
                 data[nyIndeks] = da;     //     key og dets tilhørende data.
             } else
               cout << "\nMap is already full!\n\n";    //  Egen melding ??
          } else
              cout << "\nKey already exists!\n\n";      //  Egen melding ??
      }


      int size() const  {  return antall;  }
};


/**
 *  Hovedprogrammet:
 */
int main()  {
    Map <int, string> mengde;         //  NB:   vs.  map <int, string> mengde;
                                      //        fra OOProg, da med liten 'm'.

    mengde.insert(49, "FN"); mengde.insert(12, "TO"); mengde.insert( 7, "SY");
    mengde.insert(23, "TT"); mengde.insert(63, "ST"); mengde.insert(53, "TR");
    mengde.insert(42, "FT"); mengde.insert(15, "FE"); mengde.insert( 5, "FE");
    mengde.display();

    mengde.insert(23, "TT");          //  Finnes allerede!

    mengde.erase(49);   mengde.erase(5);  mengde.erase(63);
    mengde.display();

    mengde.erase(22);                 //  Finnes IKKE!

    mengde.change(12, "TOLV");   mengde.change(15, "FEMTEN");
    mengde.display();

    mengde.change(96, "NS");          //  Finnes IKKE!

    cout << "\n\n";
    return 0;
}
