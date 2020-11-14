#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

vector<vector<int>> ss;
vector<vector<int>> ss_r;
vector<int> outgoing;
vector<bool> used;
vector<bool> bad;
vector<bool> good;

void dfs1(int v) {
    used[v] = true;
    if (ss[v].empty())
        bad[v] = true;
    for (int s : ss[v]) {
        if (!used[s])
            dfs1(s);
    }
}

void dfs2(int v) {
    used[v] = true;
    for (int s : ss_r[v]) {
        if (!used[s]) {
            if (bad[v])
                good[s] = true;
            else if (--outgoing[s] == 0)
                bad[s] = true;
            else
                continue;
            dfs2(s);
        }
    }
}

int main() {
    int n, m, s;
    cin >> n >> m >> s;
    s--;
    ss = vector<vector<int>>(n);
    ss_r = vector<vector<int>>(n);
    outgoing = vector<int>(n);
    used = vector<bool>(n);
    good = vector<bool>(n);
    bad = vector<bool>(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        ss_r[b - 1].push_back(a - 1);
        ss[a - 1].push_back(b - 1);
        outgoing[a - 1]++;
    }
    dfs1(s);
    used = vector<bool>(n);
    for (int i = 0; i < n; i++) {
        if (bad[i])
            dfs2(i);
    }
    if (good[s])
        cout << "First player wins";
    else
        cout << "Second player wins";
    return 0;
}
