/**
 *   L�sningsforslag til oppgave nr 5 (liten utvidelse av EKS_08_TreTraversering).
 *
 *   Det er MANGE m�ter � l�se denne oppgaven p�. Nedenfor er det angitt EN
 *   metode som bruker 'settFor' inni 'Node'. Dessuten ligner l�sningen
 *   mye p� den allerede ferdigkodede 'taverserPreorder'.
 *
 *   @file	  OPPG_05.CPP
 *   @author  Frode Haug, NTNU
 */



 /**
  *  Traverserer/g�r gjennom et tre UNDER 'node'
  *  p� en POSTORDER m�te ved � bruke en stakk.
  *
  *   @param   node  -  Aktuell node � behandle
  *   @see     besok(...)
  */
void traverserPostorder(Node* node) {
    if (node) {                                  //  Reell node:
        gStakk.push(node);                       //  Legger rota p� stakken.
        while (!gStakk.empty()) {                //  Fortsatt noder igjen:
            node = gStakk.top();   gStakk.pop(); //  Tar av �verste node.
            if (node->settFor)                   //  Sett/pushet tidligere!
                besok(node);                     //  Kan da trygt bes�ke!
            else {                               //  Ny/usett node:
                node->settFor = true;            //  Markerer at sett.
                gStakk.push(node);               //  Push'er den bakerst ift:
                if (node->right)  gStakk.push(node->right); //  Push'er evt.
                if (node->left)   gStakk.push(node->left); //  h. og v.subtre.
            }
        }
    }
}
