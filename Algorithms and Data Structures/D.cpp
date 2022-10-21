#include <iostream>
#include <string>

using namespace std;

int main() {
    long long a, b, c, d, k;
    cin >> a >> b >> c >> d >> k;
    long long count = 0;
    while (a <= d) {
        long long oldA = a;
        a *= b;
        a -= c;
        count += 1;
        if (oldA == a) {
            cout << a << endl;
            return 0;
        }
        if (a <= 0) {
            cout << 0 << endl;
            return 0;
        }
        if (count == k) {
            if (a > d) {
                cout << d << endl;
            } else {
                cout << a << endl;
            }
            return 0;
        }
    }
    cout << d << endl;
    return 0;
}
