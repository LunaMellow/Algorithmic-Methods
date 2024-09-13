/**     Description:
 *      - ...
 *
 *      @file Task 7.cpp
 *      @date 9/12/2024
 *
 *      @author Luna S.
 *      @alias LunaMellow
 */
#include <iostream>
using namespace std;

constexpr int N = 10;
int brett[N][N] = {
{0,0,0,0,0,0,0,0,0,1},
{0,0,0,1,1,0,0,0,0,1},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,0,0,1,0,0},
{0,0,0,1,0,0,0,1,0,0},
{0,0,0,0,0,0,0,1,1,0},
{0,0,0,0,1,1,0,0,0,0},
{0,1,1,0,0,0,0,0,0,0},
{0,1,1,0,0,0,0,0,1,0},
{0,0,0,0,0,0,0,1,1,0}
};

int main() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == 1 || j == 1) { cout << "\U000026AA";} else { cout << "\U000026AB";}
		}
		cout << endl;
	}
	std::cin.ignore();
	return 0;
}