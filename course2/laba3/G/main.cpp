#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<unordered_multiset<int>> ss(n);
    int first = -1, second = -1;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        if (k % 2 == 1) {
            if (first == -1) {
                first = i;
            } else if (second == -1) {
                second = i;
            } else {
                cout << -1;
                exit(0);
            }
        }
        for (; k > 0; k--) {
            int a;
            cin >> a;
            ss[i].insert(a - 1);
        }
    }
    if (first != -1 && second == -1) {
        cout << -1;
        exit(0);
    }
    if (first != -1) {
        ss[first].insert(second);
        ss[second].insert(first);
    }
    stack<int> stack;
    stack.push(0);
    vector<int> res;
    while (!stack.empty()) {
        int v = stack.top();
        if (ss[v].empty()) {
            res.push_back(v);
            stack.pop();
        } else {
            int to = *ss[v].begin();
            stack.push(to);
            ss[v].erase(ss[v].begin());
            ss[to].erase(ss[to].find(v));
        }
    }
    if (first != -1) {
        vector<int> temp_res;
        cout << res.size() - 2 << "\n";
        for (size_t i = 0; i + 1 < res.size(); i++) {
            if ((res[i] == first && res[i + 1] == second) ||
                (res[i] == second && res[i + 1] == first)) {
                for (size_t j = i + 1; j < res.size(); j++)
                    cout << res[j] + 1 << " ";
                for (size_t j = 1; j <= i; j++)
                    cout << res[j] + 1 << " ";
                break;
            }
        }
    } else {
        cout << res.size() - 1 << "\n";
        for (auto i : res)
            cout << i + 1 << " ";
    }
    return 0;
}
