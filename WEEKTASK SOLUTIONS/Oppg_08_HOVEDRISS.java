/**
 *   Hovedrisset til oppgave nr 8.
 *
 *   For programmets funksjonalitet:  se oppgaveteksten.
 *
 *   (Dette var oppg.nr.3 på eksamen 15/8-2016 i IMT2021-Algoritmiske metoder)
 *
 *   @file    Oppg_08_Hovedriss.java
 *   @author  Marius Lindvall, NTNU
 */
public class Oppg_08_Hovedriss {
    
    /**
     *  Node (med ID/key/data og venstre/høyre pekere til nodens barn).
     */
    static class Node {
        public int   ID;        //  Nodens ID/key/nøkkel/navn (et tall).
        public Node left;       //  Peker til venstre subtre, evt. 'null' når tomt.
        public Node right;      //  Peker til høyre subtre, evt. 'null' når tomt.
                            //  Constructor:
        Node(int id, Node l, Node r) { ID = id;  left = l;  right = r; }
    };
    
    static Node gRoot = null;       ///<  Peker til hele treets rot.
    static final int MIN = 0,       ///<  Verdier mindre/større enn ALLE ID'er i treet.
                     MAX = 9999;

    /**
     *  Hovedprogrammet:
     */
    public static void main(String[] args) {
        gRoot = byggTre();

        System.out.println("\n\nTester oppgave A - Minste og største verdi i treet:");
        System.out.println("Minste  verdi i treet er:  " + finnMin(gRoot));   //   3
        System.out.println("Største verdi i treet er:  " + finnMax(gRoot));   //  82


        System.out.println("\n\nTester oppgave B - Er treet et binært søketre eller ei:");
        System.out.println("Treet er " + (erBST(gRoot) ? "" : "IKKE ")  //  Er IKKE BST!
                         + "et binært SØKEtre\n");
    }
    
    /**
     *  Bygger et binært testtre.
     *
     *  @return   Peker til rota i treet som er bygd
     */
    static Node byggTre() {
        //          Bygger treet:                         //
        //                       17                       //
        //                  /          \                  //
        //                 33           11                //
        //               /    \       /    \              //
        //              7      35   82      5             //
        //            /   \           \    /              //
        //           27     13        31  34              //
        //                   \        /                   //
        //                   10      57                   //
        //                          /  \                  //
        //                         3   30                 //
        Node n3  = new Node(3, null, null),
             n30 = new Node(30, null, null),
             n10 = new Node(10, null, null),
             n57 = new Node(57, n3, n30),
             n27 = new Node(27, null, null),
             n13 = new Node(13, null, n10),
             n31 = new Node(31, n57, null),
             n34 = new Node(34, null, null),
             n7  = new Node(7, n27, n13),
             n35 = new Node(35, null, null),
             n82 = new Node(82, null, n31),
             n5  = new Node(5, n34, null),
             n33 = new Node(33, n7, n35),
             n11 = new Node(11, n82, n5),
             n17 = new Node(17, n33, n11);
        return n17;
    }
    
    /**
     *  OPPGAVE B - Finner ut om et binært tre er et binært SØKEtre (BST)
     *
     *  @param    node  -  Aktuell node å behandle
     *  @return   Om treet under 'node' er binært søketre (BST) eller ei
     *  @see      finnMax(...)
     *  @see      finnMin(...)
     */
    static boolean erBST(Node node) {

        //  LAG INNMATEN  (se oppgaveteksten)
        return true;                        // STRYK DENNE LINJEN!
    }
    
    /**
     *  OPPGAVE A2 - Finner STØRSTE verdi i et binært (IKKE nødvendigvis SØKE)tre.
     *
     *  @param    node  -  Aktuell node å behandle
     *  @return   ALLER største verdi (ID) funnet i HELE treet under 'node'
     */
    static int finnMax(Node node) {

        //  LAG INNMATEN  (se oppgaveteksten)
        return 0;                        // STRYK DENNE LINJEN!
    }
    
    /**
     *  OPPGAVE A1 - Finner MINSTE verdi i et binært (IKKE nødvendigvis SØKE)tre.
     *
     *  @param    node  -  Aktuell node å behandle
     *  @return   ALLER minste verdi (ID) funnet i HELE treet under 'node'
     */
    static int finnMin(Node node) {

        //  LAG INNMATEN  (se oppgaveteksten)
        return 0;                        // STRYK DENNE LINJEN!
    }

}
