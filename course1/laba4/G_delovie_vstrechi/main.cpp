#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

int main() {
    ifstream fin("meetings.in");
    ofstream fout("meetings.out");
    int n, k;
    fin >> n >> k;
    vector<vector<int>> d(1 << n, vector<int>(n, INT_MAX));
    vector<pair<int, int>> allow(n);
    vector<int> w(n);
    queue<pair<int, int>> q;
    for (int i = 0; i < n; i++) {
        int a, b, wg;
        fin >> a >> b >> wg;
        allow[i] = make_pair(a, b);
        w[i] = wg;
    }
    pair<int, int> last;
    for (int i = 0; i < n; i++) {
        if (k >= allow[i].first && k <= allow[i].second) {
            d[1 << i][i] = k + w[i];
            last = make_pair(1 << i, i);
        }
    }
    int mask, ind;
    q.push(make_pair(0, -1));
    while (!q.empty()) {
        mask = q.front().first;
        ind = q.front().second + 1;
        for (int j = 0; j < n; j++) {
            if (mask & (1 << j)) {
                int b = mask ^(1 << j);
                int mini = INT_MAX;
                for (int i = 0; i < n; i++) {
                    k = d[b][i];
                    if (b & (1 << i) && k >= allow[j].first &&
                        k <= allow[j].second && d[b][i] != INT_MAX) {
                        mini = min(mini, d[b][i] + w[j]);
                    }
                }
                if (mini != INT_MAX) {
                    d[mask][j] = mini;
                    last = make_pair(mask, j);
                }
            }
        }
        for (; ind < n; ind++) {
            q.push(make_pair(mask | (1 << ind), ind));
        }
        q.pop();
    }

    mask = last.first;
    int l = last.second;
    vector<long long> path;
    path.push_back(l + 1);
    for (int i = 0; i < n; i++) {
        for (int i = 0; i < n; i++) {
            if (i != l && mask & (mask << i) && d[mask ^ (1 << l)][i] + w[l] == d[mask][l]) {
                path.push_back(i + 1);
                if (mask & (1 << l)) {
                    mask ^= 1 << l;
                    l = i;
                }
                break;
            }
        }
    }
    fout << path.size() << endl;

    for (auto it = --path.end(); it != --path.begin(); it--) {
        fout << *it << ' ';
    }

    return 0;
}
