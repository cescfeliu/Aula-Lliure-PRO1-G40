// Comptant freqüències
// https://jutge.org/problems/P63414_ca
// P63414_ca:std:none:G++17

#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<int> comptadors(1001, 0);

	int n, x;
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> x;
		comptadors[x - 1000000000]++;
	}

    for (int i = 0; i < int(comptadors.size()); i++) {
        if (comptadors[i] > 0) {
            cout << (1000000000 + i) << " : " << comptadors[i] << endl;
        }
    }
}
