#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> ss;
vector<vector<int>> ss_t;
vector<vector<int>> ss_f;
vector<int> ps;
vector<bool> used;

int n, m, counter;

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
    int b, k;
    cin >> m >> n;
    ss = vector<vector<int>>(m);
    ss_f = vector<vector<int>>(m);
    ss_t = vector<vector<int>>(n);
    ps = vector<int>(m);
    for (int i = 0; i < m; i++) {
        cin >> k;
        for (int j = 0; j < k; j++) {
            cin >> b;
            ss[i].push_back(b - 1);
        }
    }
    for (int i = 0; i < m; i++) {
        cin >> ps[i];
        ps[i]--;
    }
    used = vector<bool>(m);
    for (int i = 0; i < m; i++) {
        for (int j : ss[i]) {
            if (ps[i] == j && !used[i]) {
                ss_t[j].push_back(i);
                used[i] = true;
            } else {
                ss_f[i].push_back(j);
            }
        }
    }
    vector<bool> left_used(m);
    vector<bool> right_used(n);
    for (int i = 0; i < m; i++) {
        if (ps[i] == -1) {
            queue<pair<int, bool>> q;
            q.push({i, false});
            while (!q.empty()) {
                pair vb = q.front();
                q.pop();
                int v = vb.first;
                if (!vb.second) {
                    left_used[v] = true;
                    for (int j : ss_f[v]) {
                        if (!right_used[j]) {
                            q.push({j, true});
                        }
                    }
                } else {
                    right_used[v] = true;
                    for (int j : ss_t[v]) {
                        if (!left_used[j]) {
                            q.push({j, false});
                        }
                    }
                }
            }
        }
    }
    vector<int> left_res;
    vector<int> right_res;
    for (size_t i = 0; i < left_used.size(); i++) {
        if (!left_used[i])
            left_res.push_back(i);
    }
    for (size_t i = 0; i < right_used.size(); i++) {
        if (right_used[i])
            right_res.push_back(i);
    }
    cout << left_res.size() + right_res.size() << endl;
    cout << left_res.size() << " ";
    for (int i : left_res) {
        cout << i + 1 << " ";
    }
    cout << endl << right_res.size() << " ";
    for (int i : right_res) {
        cout << i + 1 << " ";
    }
    return 0;
}
