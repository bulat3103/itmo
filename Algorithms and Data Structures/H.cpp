#include <iostream>
#include <stdlib.h>

using namespace std;

int comparator (const void * a, const void * b)
{
    return ( *(int*)b - *(int*)a );
}

int main() {
    int n, k;
    cin >> n >> k;
    int prices[n];
    for (int i = 0; i < n; ++i) {
        cin >> prices[i];
    }
    qsort(prices, n, sizeof(int), comparator);
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if ((i + 1) % k != 0) {
            count += prices[i];
        }
    }
    cout << count << endl;
    return 0;
}
