#include <iostream>
#include <set>
#include <vector>

using namespace std;

vector < int > a[100001];
int b[500000];
int id[100001];
struct comp {
    bool operator()(int x, int y) {
        return a[x][id[x]] > a[y][id[y]];
    }
};

int main() {
    int n, k, p;
    cin >> n >> k >> p;
    for (int i = 0; i < p; i++) {
        cin >> b[i];
        a[b[i]].emplace_back(i);
    }
    for (int i = 0; i < n; i++) a[i].emplace_back(1e6);
    set<int, comp> floor;
    int ans = 0;
    for (int i = 0; i < p; i++) {
        bool have = false;
        if (floor.find(b[i]) != floor.end()) have = true;
        if (have) floor.erase(b[i]);
        id[b[i]]++;
        if (have) {
            floor.emplace(b[i]);
            continue;
        }
        ans++;
        if (floor.size() < k) {
            floor.emplace(b[i]);
        } else {
            floor.erase(floor.begin());
            floor.emplace(b[i]);
        }
    }
    cout << ans;
}