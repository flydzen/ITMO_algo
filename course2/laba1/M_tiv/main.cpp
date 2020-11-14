#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

void dfs(int v, vector<vector<int>> &g, vector<int> &used, vector<int> &topsort) {
    used[v] = 1;
    for (auto to : g[v]) {
        if (used[to] == 0) {
            dfs(to, g, used, topsort);
        } else if (used[to] == 1) {
            cout << "NO";
            exit(0);
        }
    }
    used[v] = 2;
    topsort.push_back(v);
}


int main() {
    const int BASE = 26;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>> ss(BASE);
    vector<int> zero(BASE);
    vector<int> inc(BASE);
    string s, last;
    cin >> last;
    if (last.size() > 1)
        zero[last[0] - 'a'] = 1;
    for (int i = 0; i < n - 1; i++) {
        cin >> s;
        zero[s[0] - 'a'] = 1;
        if (s.size() < last.size() || s == last) {
            cout << "NO";
            exit(0);
        }
        if (s.size() > last.size()) {
            last = s;
            continue;
        }
        for (size_t j = 0; j < s.size(); j++) {
            if (last[j] != s[j]) {
                ss[last[j] - 'a'].push_back(s[j] - 'a');
                inc[s[j] - 'a'] = 1;
                break;
            }
        }
        last = s;
    }
    int ind = -1;
    for (int i = 0; i < BASE; i++) {
        if (!zero[i] && !inc[i]) {
            ind = i;
            break;
        }
    }
    if (ind == -1) {
        cout << "NO";
        exit(0);
    }
    vector<int> used(BASE);
    vector<int> topsort;
    for (int i = 0; i < BASE; i++) {
        if (!used[i]) dfs(i, ss, used, topsort);
    }
    vector<int> answer(BASE);
    reverse(topsort.begin(), topsort.end());
    for (int i = 0; i < BASE; i++) {
        if (topsort[i] == ind) {
            topsort.erase(topsort.begin() + i);
            topsort.insert(topsort.begin(), ind);
            break;
        }
    }
    cout << "YES" << endl;
    for (int i = 0; i < BASE - 1; i++) {
        answer[topsort[i + 1]] = answer[topsort[i]] + 1;
    }
    for (int i : answer) {
        cout << i << " ";
    }
    return 0;
}
