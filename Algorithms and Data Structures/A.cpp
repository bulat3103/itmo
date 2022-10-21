#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int flowers[n];
    for (int i = 0; i < n; i++) cin >> flowers[i];
    if (n == 1) {
        cout << 1 << " " << 1 << endl;
        return 0;
    }
    int left = 0, max = 2;
    int ansL = 0, ansR = 1;
    for (int i = 2; i < n; i++) {
        if (i == n - 1 & flowers[i - 2] != flowers[i] & flowers[i - 1] != flowers[i]) {
            if (i - left + 1 > max) {
                max = i - left;
                ansR = i;
                ansL = left;
            }
        } else
        if (flowers[i - 2] == flowers[i] & flowers[i - 1] == flowers[i]) {
            if (i - left > max) {
                max = i - left;
                ansR = i - 1;
                ansL = left;
            }
            left = i - 1;
        }
    }
    cout << ansL + 1 << " " << ansR + 1 << endl;
    return 0;
}
