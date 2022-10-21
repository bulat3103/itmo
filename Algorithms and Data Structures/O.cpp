#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph;
    vector<int> color;
    graph.resize(n);
    color.resize(n, 0);
    for (int i = 0; i < m; ++i) {
        int f, s;
        cin >> f >> s;
        graph[f - 1].push_back(s - 1);
        graph[s - 1].push_back(f - 1);
    }
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (color[i] == 0) {
            color[i] = 1;
            q.push(i);
            while(!q.empty()) {
                int from = q.front();
                q.pop();
                for (int j = 0; j < graph[from].size(); ++j) {
                    if (color[graph[from][j]] == 0) {
                        color[graph[from][j]] = 3 - color[from];
                        q.push(graph[from][j]);
                    } else {
                        if (color[graph[from][j]] == color[from]) {
                            cout << "NO" << endl;
                            exit(0);
                        }
                    }
                }
            }
        }
    }
    cout << "YES" << endl;
}