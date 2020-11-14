#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

const long long N = INT_MAX;

int main() {
    ifstream fin("salesman.in");
    ofstream fout("salesman.out");
    int n, m;
    fin >> n >> m;
    vector<vector<int>> d(1 << n, vector<int>(n, -1));
    vector<vector<int>> w(n, vector<int>(n, -1));
    for (int i = 0; i < m; i++) {
        int a, b, wg;
        fin >> a >> b >> wg;
        w[a - 1][b - 1] = wg;
        w[b - 1][a - 1] = wg;
    }
    for (int i = 0; i < n; i++) {
        d[1 << i][i] = 0;
    }
    queue<pair<int, int>> q;
    int mask, ind;
    q.push(make_pair(0, -1));
    while (!q.empty()) {
        mask = q.front().first;
        ind = q.front().second + 1;
        for (int j = 0; j < n; j++) {
            if (mask & (1 << j)) {
                int b = mask ^(1 << j);
                int mini = INT_MAX;
                for (int k = 0; k < n; k++) {
                    if (b & (1 << k) && w[k][j] != -1 && d[b][k] != -1) {
                        mini = min(mini, d[b][k] + w[k][j]);
                    }
                }
                if (mini != INT_MAX) d[mask][j] = mini;
            }
        }
        for (; ind < n; ind++) {
            q.push(make_pair(mask | (1 << ind), ind));
        }
        q.pop();
    }
    int p = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (d[(1 << n) - 1][i] != -1) {
            p = min(p, d[(1 << n) - 1][i]);
        }
    }
    if (p == INT_MAX) {
        fout << -1;
    } else {
        fout << p << endl;
    }
    return 0;
}
