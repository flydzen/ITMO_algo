#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

int n, m, nm;

int get_left(int y, int x) {
    return y <= x ? x - y : m + y - x - 1;
}

int get_right(int y, int x) {
    return x + y;
}

bool dfs_kuhn(int v, vector<bool> &used, vector<vector<int>> &ss, vector<int> &ps) {
    if (used[v])
        return false;
    used[v] = true;
    for (int i : ss[v]) {
        if (ps[i] == -1 || dfs_kuhn(ps[i], used, ss, ps)) {
            ps[i] = v;
            return true;
        }
    }
    return false;
}

void solve(vector<vector<int>> &ss, vector<int> &left_res, vector<int> &right_res) {
    vector<int> ps(nm, -1);
    for (int i = 0; i < nm; i++) {
        vector<bool> used(nm);
        dfs_kuhn(i, used, ss, ps);
    }
    vector<vector<int>> ss_t(nm);
    vector<vector<int>> ss_f(nm);
    vector<bool> left_used(nm);
    vector<bool> right_used(nm);
    vector<bool> used(nm);
    vector<int> rps(nm, -1);
    for (int i = 0; i < nm; i++) {
        if (ps[i] != -1) {
            rps[ps[i]] = i;
        }
        for (int j : ss[i]) {
            if (ps[j] == i && !used[i]) {
                ss_t[j].push_back(i);
                used[i] = true;
            } else {
                ss_f[i].push_back(j);
            }
        }
    }
    for (int i = 0; i < nm; i++) {
        if (rps[i] == -1) {
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
    for (size_t i = 0; i < left_used.size(); i++) {
        if (!left_used[i])
            left_res.push_back(i);
    }
    for (size_t i = 0; i < right_used.size(); i++) {
        if (right_used[i])
            right_res.push_back(i);
    }
}

void print(vector<int> &left, vector<int> &right,
           unordered_map<int, pair<pair<int, int>, bool>> &info_l,
           unordered_map<int, pair<pair<int, int>, bool>> &info_r) {
    cout << left.size() + right.size() << endl;
    for (auto i : left) {
        auto ceil = info_l[i];
        if (info_l.find(i) == info_l.end()) {
            cout << "fuck";
        }
        cout << "2 " << ceil.first.first << " " << ceil.first.second;
        cout << " " << (ceil.second ? 'W' : 'B') << '\n';
    }
    for (auto i : right) {
        auto ceil = info_r[i];
        if (info_r.find(i) == info_r.end()) {
            cout << "fuck";
        }
        cout << "1 " << ceil.first.first << " " << ceil.first.second;
        cout << " " << (ceil.second ? 'W' : 'B') << '\n';
    }
    //  mixed up the types of diagonals
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    nm = n + m - 1;
    vector<vector<int>> ss1(nm);
    vector<vector<int>> ss2(nm);
    unordered_map<int, pair<pair<int, int>, bool>> info_l_1;
    unordered_map<int, pair<pair<int, int>, bool>> info_r_1;
    unordered_map<int, pair<pair<int, int>, bool>> info_l_2;
    unordered_map<int, pair<pair<int, int>, bool>> info_r_2;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            bool cur_col = c == 'W';
            if ((i + j) % 2 == cur_col) {
                ss1[get_left(i, j)].push_back(get_right(i, j));
                info_l_1[get_left(i, j)] = {{i + 1, j + 1}, !cur_col};
                info_r_1[get_right(i, j)] = {{i + 1, j + 1}, !cur_col};
            } else {
                ss2[get_left(i, j)].push_back(get_right(i, j));
                info_l_2[get_left(i, j)] = {{i + 1, j + 1}, !cur_col};
                info_r_2[get_right(i, j)] = {{i + 1, j + 1}, !cur_col};
            }
        }
    }
    vector<int> left_res1;
    vector<int> right_res1;
    vector<int> left_res2;
    vector<int> right_res2;
    solve(ss1, left_res1, right_res1);
    solve(ss2, left_res2, right_res2);
    if (left_res1.size() + right_res1.size() < left_res2.size() + right_res2.size())
        print(left_res1, right_res1, info_l_1, info_r_1);
    else
        print(left_res2, right_res2, info_l_2, info_r_2);
    return 0;
}
