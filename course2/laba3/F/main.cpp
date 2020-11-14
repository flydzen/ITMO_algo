#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int n;
vector<unordered_set<int>> ss;
vector<int> boys;
vector<int> girls;
vector<vector<bool>> reachable;

void dfs(int from, int v, vector<bool> &used) {
    used[v] = true;
    for (auto i : ss[v]) {
        reachable[from][i] = true;
        if (!used[boys[i]])
            dfs(from, boys[i], used);
    }
}

int main() {
    cin >> n;
    int k, a;
    ss = vector<unordered_set<int>>(n);
    boys = vector<int>(n);
    girls = vector<int>(n);
    for (int i = 0; i < n; i++) {
        cin >> k;
        for (int j = 0; j < k; j++) {
            cin >> a;
            ss[i].insert(a - 1);
        }
    }
    for (int i = 0; i < n; i++) {
        cin >> a;
        girls[i] = a - 1, boys[a - 1] = i;
    }
    reachable = vector<vector<bool>>(n, vector<bool>(n));
    for (int i = 0; i < n; i++) {
        vector<bool> used(n);
        dfs(i, i, used);
    }
    for (int i = 0; i < n; i++) {
        vector<int> res;
        for (int j = 0; j < n; j++)
            if (girls[i] == j || (reachable[boys[j]][girls[i]] && ss[i].find(j) != ss[i].end()))
                res.push_back(j);
        cout << res.size() << " ";
        for (auto j : res)
            cout << j + 1 << " ";
        cout << '\n';
    }
    return 0;
}
