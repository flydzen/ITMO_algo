#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<int>> ss;
vector<int> ind;
vector<pair<int, int>> ht;
vector<bool> used;

void dfs(int v, int h) {
    used[v] = true;
    ind[v] = ht.size();
    ht.emplace_back(h, v);
    for (auto to : ss[v]) {
        if (!used[to]) {
            dfs(to, h + 1);
            ht.emplace_back(h, v);
        }
    }
}

class SparseTable {
 public:
     explicit SparseTable(vector<pair<int, int>> &v) : size(v.size()) {
         lens = vector<int>(size);
         lens[0] = 0;
         lens[1] = 0;
         for (int i = 2; i <= size; i++) {
             lens[i] = lens[i / 2] + 1;
         }
         M.resize(v.size());
         for (int i = size - 1; i >= 0; i--) {
             M[i].resize(lens[size - i] + 1);
             for (int j = 0; j <= lens[size - i]; j++) {
                 if (j == 0) {
                     M[i][j] = v[i];
                 } else {
                     M[i][j] = min(M[i][j - 1], M[i + (1 << (j - 1))][j - 1]);
                 }
             }
         }
     }

     pair<int, int> get(int l, int r) {
         if (l > r)
             swap(l, r);
         int x = lens[r - l + 1];
         return min(M[l][x], M[r - (1 << x) + 1][x]);
     }

 private:
     int size;
     vector<vector<pair<int, int>>> M;
     vector<int> lens;

     int calcLens(int len) {
         return len == 1 ? 0 : calcLens(len / 2) + 1;
     }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, a, m;
    cin >> n >> m;
    ss = vector<vector<int>>(n);
    ind = vector<int>(n);
    used = vector<bool>(n);
    for (int i = 1; i < n; i++) {
        cin >> a;
        ss[a].push_back(i);
    }
    dfs(0, 0);
    SparseTable tree(ht);
    pair<int, int> mi;
    long long a1, a2, x, y, z;
    cin >> a1 >> a2 >> x >> y >> z;
    long long answer = 0;
    int v = 0;
    for (int i = 0; i < m; i++) {
        int first = (int) (a1 + v) % n;
        int second = (int) a2;
        if (ind[first] > ind[second]) swap(first, second);
        mi = tree.get(ind[first], ind[second]);
        a1 = (x * a1 + y * a2 + z) % n;
        a2 = (x * a2 + y * a1 + z) % n;
        answer += mi.second;
        v = mi.second;
    }
    cout << answer;
    return 0;
}