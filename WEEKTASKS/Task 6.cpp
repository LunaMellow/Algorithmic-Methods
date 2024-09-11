/**     Description:
 *      - Binary tree traverse
 *
 *      @file Task 6.cpp
 *      @date 9/11/2024
 *
 *      @author Luna S.
 *      @alias LunaMellow
 */

#include <iostream>
#include <iomanip>
using namespace std;

struct Node {
	char ID;
	Node *left, *right;
	explicit Node(const char id) { ID = id; left = right = nullptr; }
};

Node *byggTre();
int finnNoder(const Node *node);
int finnReferanse(const Node *node);
int finnFulle(const Node *node);
Node *finnHoyde(Node *node);

int main() {

	Node *root = byggTre();

	cout << "\n\nAntall noder:\n";
	cout << finnNoder(root);

	cout << "\n\nAntall pekere:\n";
	cout << finnReferanse(root);

	cout << "\n\nAntall fulle noder:\n";
	cout << finnFulle(root);

	cout << "\n\nTreets høyde:\n";
	cout << finnHoyde(root);
}

Node* byggTre() {
	/*   Bygger treet:                                     A
												  /                 \
											 B                          C
										/         \                  /
									  D             E              F
								  /       \           \          /
								G           H           I      J
								  \        / \         /        \
								   K      L   M       N          O
	*/
	Node *noder[15];
	for (int i = 0; i < 15; i++)
		noder[i] = new Node(static_cast <char> ('A' + i));

	noder[0]->left = noder[1];  noder[0]->right = noder[2];
	noder[1]->left = noder[3];  noder[1]->right = noder[4];
	noder[2]->left = noder[5];
	noder[3]->left = noder[6];  noder[3]->right = noder[7];
	noder[4]->right = noder[8];
	noder[5]->left = noder[9];
	noder[6]->right = noder[10];
	noder[7]->left = noder[11]; noder[7]->right = noder[12];
	noder[8]->left = noder[13];
	noder[9]->right = noder[14];
	return noder[0];
}

int finnNoder(const Node *node) {		return node ? 1 + finnNoder(node->left) + finnNoder(node->right) : 0; }
int finnReferanse(const Node *node) {	return finnNoder(node) + 1; }
int finnFulle(const Node *node) { return node ? 1 + finnFulle(node->left) + finnFulle(node->right) : 0; }
int finnHoyde(Node *node) {
	auto finnHoyde = [finnHoyde](const Node *node) -> int {
		if (!node) return 0;
		return 1 + max(finnHoyde(node->left), finnHoyde(node->right));
	};
}
