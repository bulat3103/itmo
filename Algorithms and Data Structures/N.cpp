#include <iostream>
#include <queue>

using namespace std;
vector<vector<int>> graph;
vector<int> was;

void dfs(int v) {
    was[v] = 1;
    for (int i = 0; i < graph[v].size(); ++i) {
        if (was[graph[v][i]] == 0) {
            dfs(graph[v][i]);
        }
    }
}

int main() {
    int n;
    cin >> n;
    graph.resize(n);
    was.resize(n, 0);
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        bool check = true;
        for (int j = 0; j < graph[i].size(); ++j) {
            if (graph[i][j] == k - 1) {
                check = false;
                break;
            }
        }
        if (check) graph[i].push_back(k - 1);
        check = true;
        for (int j = 0; j < graph[k - 1].size(); ++j) {
            if (graph[k - 1][j] == i) {
                check = false;
                break;
            }
        }
        if (check) graph[k - 1].push_back(i);
    }
    int answer = 0;
    for (int i = 0; i < n; ++i) {
        if (was[i] == 0) {
            answer += 1;
            dfs(i);
        }
    }
    cout << answer << endl;
    return 0;
}