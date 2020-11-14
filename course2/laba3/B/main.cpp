#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> ss;
vector<vector<int>> ss_new;
vector<int> ps;
vector<bool> used;
int n, k, counter;

bool dfs_kuhn(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (int i : ss[v]) {
        if (ps[i] == -1 || dfs_kuhn(ps[i])) {
            ps[i] = v;
            ss_new[v].push_back(i);
            return true;
        }
    }
    return false;
}

void dfs_path(int v) {
    used[v] = true;
    for (int i : ss_new[v]) {
        if (!used[i])
            dfs_path(i);
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int a, b;
    cin >> n >> k;
    ss = vector<vector<int>>(n);
    ss_new = vector<vector<int>>(n);
    ps = vector<int>(n, -1);
    for (int i = 0; i < k; i++) {
        cin >> a >> b;
        ss[a - 1].push_back(b - 1);
    }
    for (int i = 0; i < n; i++) {
        used = vector<bool>(n);
        dfs_kuhn(i);
    }
    used = vector<bool>(n);
    for (int i = 0; i < n; i++) {
        if (!used[i] && !ss_new[i].empty() && ps[i] == -1) {
            dfs_path(i);
            counter++;
        }
    }
    for (auto && i : used) {
        counter += !i;
    }
    cout << counter;
    return 0;
}
