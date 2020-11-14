#include <iostream>
#include <vector>
#include <set>

using namespace std;
vector<vector<int>> ss;
vector<int> tin, up;
vector<bool> used;
set<int> answer;
int time;
int maxcolor = 0;
vector<int> color;

int dfs(int v, int p) {
    used[v] = true;
    time++;
    up[v] = time;
    tin[v] = time;
    for (int u : ss[v]) {
        if (u != p) {
            if (used[u]) {
                tin[v] = min(tin[v], up[u]);
            } else {
                dfs(u, v);
                tin[v] = min(tin[v], tin[u]);
            }
        }
    }
    return 0;
}

void paint(int v, int clr) {
    color[v] = clr;
    for (int s : ss[v]) {
        if (!color[s]) {
            if (tin[s] > up[v]) {
                maxcolor++;
                paint(s, maxcolor);
            } else {
                paint(s, clr);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    used = vector<bool>(n);
    answer = set<int>();
    ss = vector<vector<int>>(n);
    color = vector<int>(n);
    tin.reserve(n);
    up.reserve(n);
    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        ss[--a].push_back(--b);
        ss[b].push_back(a);
    }
    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs(i, i);
    used = vector<bool>(n);
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            maxcolor++;
            paint(i, maxcolor);
        }
    }
    cout << maxcolor << endl;
    for (int i : color) {
        cout << i << " ";
    }

    return 0;
}
