#include <iostream>
#include <deque>
#include <cmath>

using namespace std;

int *massive;
int *y;

void make_tree(int cur, int left, int right) {
    if (left != right) {
        make_tree(cur * 2, left, (left + right) / 2);
        make_tree(cur * 2 + 1, 1 + (left + right) / 2, right);
        massive[cur] = min(massive[cur * 2], massive[cur * 2 + 1]);
    } else {
        massive[cur] = y[left];
    }
}

int get_min(int cur, int left, int right, int l, int r) {
    if (l == left  && r == right) {
        return massive[cur];
    } else if (l > r) {
        return 1000000;
    } else {
        return min(get_min(cur * 2, left, (left + right) / 2, l, min(r, (left + right) / 2)),
                   get_min(cur * 2 + 1, 1 + (left + right) / 2, right,
                           max(l, 1 + (left + right) / 2), r));
    }
}

void defineMassiveSize(int n) {
    massive = new int[4 * n + 1];
    y = new int[n + 1];
}

int main() {
    int n, k;
    cin >> n >> k;
    defineMassiveSize(n);
    for (int i = 1; i <= n; ++i) {
        cin >> y[i];
    }
    make_tree(1, 1, n);
    for (int i = 0; i < n - k + 1; ++i) {
        cout << get_min(1, 0, n - 1, i, i + k - 1) << " ";
    }
    return 0;
}
