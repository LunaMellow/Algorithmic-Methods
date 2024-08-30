/**     Description:
 *      - Postorder traverse
 *
 *      @file Task 5.cpp
 *      @date 8/30/2024
 *
 *      @author Luna S.
 *      @alias LunaMellow
 */

/**
 *  Traverserer/g�r gjennom et tre UNDER 'node'
 *  p� en POSTORDER m�te ved � bruke en stakk.
 *
 *   @param   node  -  Aktuell node � behandle
 *   @see     besok(...)
 */
void traverserPostorder(Node* node) {
	if (node) { // Hvis noden eksisterer
		gStakk.push(node); // Legg roten på stacken
		while (!gStakk.empty()) { // Imens stacken har en node
			node = gStakk.top(); gStakk.pop(); // Sett nåverende node til toppen av stacken
			if (node->besokt) { // Ved første besøk vil verdien være false
				besok(node); // Besøk node om if statement true
			}
			else {
				node->besokt = true; // Sett besøkt lik true så neste iter går igjennom
				gStakk.push(node); // Legg nåværende node tilbake på stacken
				if (node->right) gStakk.push(node->right); // Legg til barn
				if (node->left)  gStakk.push(node->left); // Legg til barn
			}
		}
	}
}