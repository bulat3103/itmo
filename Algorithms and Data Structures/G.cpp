#include <algorithm>
#include "iostream"
#include "vector"
#include "map"

using namespace std;

bool cmp(pair<char, int> p1, pair<char, int> p2) {
    if (p1.second == p2.second) {
        return p1.first > p2.first;
    }
    return p1.second > p2.second;
}

int main() {
    string s;
    cin >> s;
    vector<pair<char, int>> pairs;
    for (int i = 0; i < 26; ++i) {
        int weight;
        cin >> weight;
        pair<char, int> newPair ('a' + i, weight);
        pairs.push_back(newPair);
    }
    sort(pairs.begin(), pairs.end(), cmp);
    map<char, int> counts;
    for (int i = 0; i < 26; ++i) {
        counts['a' + i] = 0;
    }
    for (int i = 0; i < s.length(); ++i) {
        counts[s[i]]++;
    }
    char ans[s.length()];
    int indexLeft = 0;
    int indexRight = s.length() - 1;
    for (pair<char, int> p : pairs) {
        if (counts[p.first] >= 2) {
            ans[indexLeft++] = p.first;
            ans[indexRight--] = p.first;
            counts[p.first] -= 2;
        }
    }
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < counts['a' + i]; ++j) {
            ans[indexLeft++] = 'a' + i;
        }
    }
    for (char i : ans) {
        cout << i;
    }
}