#include <iostream>
#include <set>
#include <vector>

using namespace std;

vector<vector<int>> ss;
vector<pair<int, int>> result;
vector<int> stack;
vector<bool> used;

void dfs(int v) {
    used[v] = true;
    if (!stack.empty()) {
        result.emplace_back(stack.back(), v);
        for (size_t j = 0; j < stack.size() - 1; j++) {
            if (stack[j + 1] < v)
                result.emplace_back(stack[j], v);
        }
    }
    stack.push_back(v);
    for (auto i : ss[v]) {
        if (!used[i]) dfs(i);
    }
    stack.pop_back();
}

int main() {
    int n, m, l, c;
    cin >> n >> m;
    cin >> l;
    l--;
    set<pair<int, int>> to;
    ss = vector<vector<int>>(n);
    stack = vector<int>();
    used = vector<bool>(n);
    for (int i = 0; i < m - 1; i++) {
        cin >> c;
        c--;
        if (to.count({c, l}) == 1) {
            ss[c].push_back(l);
        } else {
            to.insert({l, c});
        }
        l = c;
    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) dfs(i);
    }
    cout << result.size() << endl;
    for (auto &i : result) {
        cout << i.first + 1 << " " << i.second + 1 << endl;
    }
    return 0;
}
