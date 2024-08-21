/**
 *   Løsningsforslag til oppgave nr 5 (liten utvidelse av EKS_08_TreTraversering).
 *
 *   Det er MANGE måter å løse denne oppgaven på. Nedenfor er det angitt EN
 *   metode som bruker 'settFor' inni 'Node'. Dessuten ligner løsningen
 *   mye på den allerede ferdigkodede 'taverserPreorder'.
 *
 *   @file	  OPPG_05.CPP
 *   @author  Frode Haug, NTNU
 */



 /**
  *  Traverserer/går gjennom et tre UNDER 'node'
  *  på en POSTORDER måte ved å bruke en stakk.
  *
  *   @param   node  -  Aktuell node å behandle
  *   @see     besok(...)
  */
void traverserPostorder(Node* node) {
    if (node) {                                  //  Reell node:
        gStakk.push(node);                       //  Legger rota på stakken.
        while (!gStakk.empty()) {                //  Fortsatt noder igjen:
            node = gStakk.top();   gStakk.pop(); //  Tar av øverste node.
            if (node->settFor)                   //  Sett/pushet tidligere!
                besok(node);                     //  Kan da trygt besøke!
            else {                               //  Ny/usett node:
                node->settFor = true;            //  Markerer at sett.
                gStakk.push(node);               //  Push'er den bakerst ift:
                if (node->right)  gStakk.push(node->right); //  Push'er evt.
                if (node->left)   gStakk.push(node->left); //  h. og v.subtre.
            }
        }
    }
}
