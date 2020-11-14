#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> ss;
vector<int> ps;
vector<bool> used;
int n, m, k, counter;

bool dfs_kuhn(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (int i : ss[v]) {
        if (ps[i] == -1 || dfs_kuhn(ps[i])) {
            ps[i] = v;
            return true;
        }
    }
    return false;
}

int main() {
    int a, b;
    cin >> n >> m >> k;
    ss = vector<vector<int>>(n);
    ps = vector<int>(m, -1);
    for (int i = 0; i < k; i++) {
        cin >> a >> b;
        ss[a - 1].push_back(b - 1);
    }
    for (int i = 0; i < n; i++) {
        used = vector<bool>(n);
        dfs_kuhn(i);
    }
    for (int i = 0; i < m; i++) {
        if (ps[i] != -1)
            counter++;
    }
    cout << counter;
    return 0;
}
