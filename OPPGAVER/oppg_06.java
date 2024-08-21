/**
 *   Løsningsforslag til oppgave nr 6.
 *
 *   Det er flere måter å løse disse oppgavene på.
 *   Nedenfor er det brukt både funksjoner som returnerer med en int som svar,
 *   og andre funksjoner som oppdaterer en global variabel. Dette er gjort for
 *   å vise hvordan disse to ulike teknikkene/måtene begge løser oppgavene.
 *
 *   @file    Oppg_06.java
 *   @author  Marius Lindvall, NTNU
 */

public class Oppg_06 {
    
    /**
     *  Node (med ID/key/data og venstre og høyre pekere til nodens barn).
     */
    static class Node {
        public char ID;
        public Node left, right;        //  Initierende constructor:
        Node(char id) { ID = id;  left = right = null; }
    }
    
    static int gAntallFulleNoder = 0;   ///<  Totalt antall FULLE noder i treet.
    static int gMaxHoyde = -1;          ///<  Max.høyde hittil funnet.
    static int gNivaa = -1;             ///<  Nåværende nodes nivå.

    /**
     *  Hovedprogrammet:
     */
    public static void main(String[] args) {
        Node root = byggTre();
        
        //  Oppgave 6.1:
        System.out.println("\n\nAntall noder:\t\t" + antallNoder(root) + "\n");

        //  Oppgave 6.2:
        System.out.println("Antall null(ptr):\t" + antallNull(root) + "\n");

        //  Oppgave 6.3:
        System.out.print("FULLE noder er:\t\t");
        antallFulle(root);
        System.out.println("  dvs. " + gAntallFulleNoder + " stk.\n");

        //  Oppgave 6.4:
        treetsHoyde(root);
        System.out.println("Treets høyde:\t\t" + gMaxHoyde + "\n\n\n");
    }
    
    
    /**
     * Oppgave 6-3 - Finner TOTALT antall FULLE noder (to ekte barn) under 'node'.
     *
     *  @param   node  -  Aktuell node å behandle
     *  @see     besok1(...)
     */
    static void antallFulle(Node node) {  //  Jfr. traverser-funksjonene i EKS_12
        if (node != null) {
            besok1(node);               //  Vilkårlig om 'besok1' forekommer
            antallFulle(node.left);     //    før, mellom eller etter de to
            antallFulle(node.right);    //    rekursive kallene!
        }
    }
    
    
    /**
     *  Oppgave 6-1 - Finner TOTALT antall noder under 'node'.
     *
     *  @param    node  -  Aktuell node å behandle
     *  @return   TOTALT antall noder under 'node'
     */
    static int antallNoder(Node node) {
        int antL = 0, antR = 0;         //  Finner rekursivt antallet
        if (node.left != null)   antL = antallNoder(node.left);   //  i venstre og
        if (node.right != null)  antR = antallNoder(node.right);  //  høyre subtre.
        return  (antL + antR + 1);      //  Returnerer med subtrærnes totalantall
    }                                   //    PLUSS en selv (+1).
    
    
    /**
     *  Oppgave 6-2 - Finner TOTALT antall nullptr/null i HELE treet.
     *
     *  @param    node  -  Aktuell (rot)node å behandle
     *  @return   TOTALT antall nullptr/null i HELE treet
     *  @see      antallNoder(...)
     */
    static int antallNull(Node node) {  //  Finner enkelt antall slike noder:
        return  antallNoder(node) + 1;  //  Bruker regel 3 fra forelesning nr.4! 
    }
    
    
    /**
     *  Teller opp 'gAntallFulleNoder' om 'node' har to interne barn/subnoder,
     *
     *  @param   node  -  Aktuell node å behandle
     */
    static void besok1(final Node node) {
                                        //  Har TO interne/ekte subnoder/barn.
        if (node.left != null && node.right != null) {
            ++gAntallFulleNoder;        //  Teller opp totalantallet av slike.
            System.out.print(node.ID + "  ");  //  Skriver nodens ID/key/data.
        }
    }
    
    
    /**
     *  Oppdaterer 'gMaxHoyde' om er på et nytt og høyere nivå enn hittil.
     *
     *  @param   node  -  Aktuell node å behandle
     */
    static void besok2(final Node node) {
        if (gNivaa > gMaxHoyde)         //  Ny max. høyde er funnet,
            gMaxHoyde = gNivaa;         //    oppdaterer nytt max.
    }
    
    
    /**
     *  Bygger et binært eksempel-tre (likt med det i EKS_08 og EKS_12).
     *
     *  @return   Peker til det bygde treets rot
     */
    static Node byggTre() {
    /*   Bygger treet :                                    A
                                                  /                 \
                                             B                          C
                                        /         \                  /
                                      D             E              F
                                  /       \           \          /
                                G           H           I      J
                                  \        / \         /        \
                                   K      L   M       N          O
    */
        Node[] noder = new Node[15];
        for (int i = 0; i < 15; i++)
            noder[i] = new Node((char) ('A' + i));

        noder[0].left = noder[1];  noder[0].right = noder[2];
        noder[1].left = noder[3];  noder[1].right = noder[4];
        noder[2].left = noder[5];
        noder[3].left = noder[6];  noder[3].right = noder[7];
        noder[4].right = noder[8];
        noder[5].left = noder[9];
        noder[6].right = noder[10];
        noder[7].left = noder[11]; noder[7].right = noder[12];
        noder[8].left = noder[13];
        noder[9].right = noder[14];
        return noder[0];
    }
    
    
    /**
     *  Oppgave 6-4 - Finner treets maksimale høyde.
     *
     *  @param   node  -  Aktuell node å behandle
     *  @see     besok2(...)
     */
    static void treetsHoyde(Node node) {  //  Jfr. traverser-funksjonene i EKS_12.
        if (node != null) {
            gNivaa++;                   //  Øker global variabel, da nytt nivå.
            treetsHoyde(node.left);    //  Vilkårlig om 'besok2' forekommer
            treetsHoyde(node.right);   //    før, mellom eller etter de to    
            besok2(node);               //    rekursive kallene!    
            gNivaa--;                   //  Skal opp igjen ett nivå (til "mor").
        }
    }

}
