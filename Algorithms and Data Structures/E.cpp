#include <iostream>
#include <string>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    int coords[n];
    for (int i = 0; i < n; ++i) {
        cin >> coords[i];
    }
    int left = 0, right = coords[n - 1] - coords[0] + 1;
    while (left != right - 1) {
        int middle = (left + right) / 2;
        int countCows = 1;
        int lastCowCoord = coords[0];
        for (int i = 1; i < n; ++i) {
            if (coords[i] - lastCowCoord >= middle) {
                ++countCows;
                lastCowCoord = coords[i];
            }
        }
        if (countCows >= k) {
            left = middle;
        } else {
            right = middle;
        }
    }
    cout << left << endl;
    return 0;
}
