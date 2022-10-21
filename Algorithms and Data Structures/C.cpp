#include <algorithm>
#include "iostream"
#include "vector"
#include "map"
#include <set>

using namespace std;

bool is_digit(const string &s) {
    for (size_t i = 0; i < s.size(); ++i)
        if (!isdigit(s[i]) && (i != 0 || (s[i] != '+' && s[i] != '-')))
            return false;
    return true;
}

int main() {
    string s;
    map<string, vector<int>> memory = {};
    vector<set<string>> used = {{}};
    while (true) {
        cin >> s;
        if (cin.eof()) {
            break;
        }
        if (s == "{") {
            used.emplace_back();
        } else if (s == "}") {
            set<string> last = used.back();
            for (const string& i : last) {
                memory[i].pop_back();
            }
            used.pop_back();
        } else {
            string var1 = s.substr(0, s.find('='));
            string var2 = s.substr(s.find('=') + 1, s.size());
            if (used.back().count(var1) == 0) {
                if (var1 != var2 || memory[var1].empty()) {
                    memory[var1].push_back(0);
                    used.back().insert(var1);
                }
            }
            if (is_digit(var2)) {
                memory[var1].back() = stoi(var2);
            } else {
                if (memory.count(var2) == 0 || memory[var2].empty()) {
                    cout << 0 << "\n";
                    memory[var1].back() = 0;
                } else {
                    cout << memory[var2].back() << "\n";
                    memory[var1].back() = memory[var2].back();
                }
            }
        }
    }
}