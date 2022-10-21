#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <map>
#include <stack>

using namespace std;

int main() {
    string s;
    cin >> s;
    stack<int> trick;
    stack<int> animal;
    stack<char> common;
    int countTrick = 0;
    int countAnimal = 0;
    int ans[s.length() / 2];
    for (int i = 0; i < s.length(); ++i) {
        char newC = s[i];
        if (newC >= 65 && newC <= 90) trick.push(countTrick++);
        if (newC >= 97 && newC <= 122) animal.push(countAnimal++);
        if (!common.empty()) {
            char fromStack = common.top();
            if (newC + 32 == fromStack || newC - 32 == fromStack) {
                common.pop();
                ans[trick.top()] = animal.top();
                trick.pop();
                animal.pop();
            } else {
                common.push(newC);
            }
        } else {
            common.push(newC);
        }
    }
    if (common.empty()) {
        cout << "Possible" << endl;
        for (int i = 0; i < s.length() / 2; ++i) {
            cout << ans[i] + 1 << " ";
        }
    } else {
        cout << "Impossible";
    }
    return 0;
}