#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    int n, m, x1, y1, x2, y2;
    cin >> n >> m >> x1 >> y1 >> x2 >> y2;
    string field[n];
    for (int i = 0; i < n; ++i) {
        cin >> field[i];
    }
    int count[n][m];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            count[i][j] = INT32_MAX;
        }
    }
    queue<pair<int, int>> q;
    pair<int, int> way[n][m];
    way[x1 - 1][y1 - 1] = {-1, -1};
    q.push({x1 - 1, y1 - 1});
    count[x1 - 1][y1 - 1] = 0;
    while(!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        if (x + 1 < n) {
            if (field[x + 1][y] != '#') {
                int plus = field[x + 1][y] == '.' ? 1 : 2;
                if (count[x + 1][y] > count[x][y] + plus) {
                    q.push({x + 1, y});
                    count[x + 1][y] = count[x][y] + plus;
                    way[x + 1][y] = {x, y};
                }
            }
        }
        if (y + 1 < m) {
            if (field[x][y + 1] != '#') {
                int plus = field[x][y + 1] == '.' ? 1 : 2;
                if (count[x][y + 1] > count[x][y] + plus) {
                    q.push({x, y + 1});
                    count[x][y + 1] = count[x][y] + plus;
                    way[x][y + 1] = {x, y};
                }
            }
        }
        if (x - 1 >= 0) {
            if (field[x - 1][y] != '#') {
                int plus = field[x - 1][y] == '.' ? 1 : 2;
                if (count[x - 1][y] > count[x][y] + plus) {
                    q.push({x - 1, y});
                    count[x - 1][y] = count[x][y] + plus;
                    way[x - 1][y] = {x, y};
                }
            }
        }

        if (y - 1 >= 0) {
            if (field[x][y - 1] != '#') {
                int plus = field[x][y - 1] == '.' ? 1 : 2;
                if (count[x][y - 1] > count[x][y] + plus) {
                    q.push({x, y - 1});
                    count[x][y - 1] = count[x][y] + plus;
                    way[x][y - 1] = {x, y};
                }
            }
        }
    }
    if (count[x2 - 1][y2 - 1] == INT32_MAX) {
        cout << -1 << endl;
        exit(0);
    }
    cout << count[x2 - 1][y2 - 1] << endl;
    int xBack = way[x2 - 1][y2 - 1].first;
    int yBack = way[x2 - 1][y2 - 1].second;
    int xCur = x2 - 1;
    int yCur = y2 - 1;
    string ans;
    while (xBack != -1 && yBack != -1) {
        if (xCur - xBack == 1) {
            ans += "S";
        }
        if (xCur - xBack == -1) {
            ans += "N";
        }
        if (yCur - yBack == 1) {
            ans += "E";
        }
        if (yCur - yBack == -1) {
            ans += "W";
        }
        xCur = xBack;
        yCur = yBack;
        xBack = way[xCur][yCur].first;
        yBack = way[xCur][yCur].second;
    }
    std::reverse(ans.begin(), ans.end());
    cout << ans << endl;
}