#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;

int comparator(string a, string b) {
    return a + b > b + a;
}

int main() {
    string s;
    vector<string> vec;
    while (true) {
        cin >> s;
        if (cin.eof()) {
            break;
        }
        vec.push_back(s);
    }
    string nums[vec.size()];
    int k = 0;
    for (const string& a : vec) {
        nums[k] = a;
        ++k;
    }
    for (int i = 1; i < vec.size(); ++i) {
        string cur = nums[i];
        int j = i;
        while ((j > 0) && comparator(nums[j - 1], cur)) {
            nums[j] = nums[j - 1];
            j--;
        }
        nums[j] = cur;
    }
    for (int i = vec.size() - 1; i >= 0; --i) {
        cout << nums[i];
    }
    return 0;
}
