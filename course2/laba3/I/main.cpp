#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

vector<size_t> it;
vector<vector<size_t>> ss;
size_t d, k, mod;

void dfs(size_t v, stringstream &res) {
    while (it[v] < ss[v].size()) {
        dfs(ss[v][it[v]++], res);
    }
    res << v % d;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> d >> k;
    if (k == 1) {
        for (size_t i = 0; i < d; i++)
            cout << i;
        return 0;
    }
    it = vector<size_t>((size_t) pow(d, k - 1));
    mod = (size_t) pow(d, k - 1);
    ss = vector<vector<size_t>>(mod);
    for (size_t i = 0; i < mod * d; i++) {
        ss[i / d].push_back(i % mod);
    }
    stringstream result;
    for (size_t i = 0; i < k - 2; i++)
        cout << 0;
    dfs(0, result);
    string str = result.str();
    reverse(str.begin(), str.end());
    cout << str;
    return 0;
}
