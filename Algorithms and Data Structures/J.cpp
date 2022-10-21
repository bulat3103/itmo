#include <iostream>
#include <deque>

using namespace std;

int main() {
    int n;
    char type;
    cin >> n;
    deque<int> firstHalf;
    deque<int> secondHalf;
    for (int i = 0; i < n; ++i) {
        cin >> type;
        if (type == '+') {
            int idx;
            cin >> idx;
            secondHalf.push_back(idx);
        } else if (type == '*') {
            int idx;
            cin >> idx;
            secondHalf.push_front(idx);
        } else {
            cout << firstHalf.front() << endl;
            firstHalf.pop_front();
        }
        int sizeFirst = (int) firstHalf.size();
        int sizeSecond = (int) secondHalf.size();
        if (sizeFirst - sizeSecond == -1) {
            firstHalf.push_back(secondHalf.front());
            secondHalf.pop_front();
        } else if (sizeFirst - sizeSecond == 2) {
            secondHalf.push_front(firstHalf.back());
            firstHalf.pop_back();
        }
    }
    return 0;
}
