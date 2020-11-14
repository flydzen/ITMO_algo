#include <iostream>
#include <vector>
#include <cmath>
#define ll long long
using namespace std;

int gena(int a) {
    return (23 * a + 21563) % 16714589;
}

class SparseTable {
 public:
     explicit SparseTable(vector<int> &v) : size(v.size()) {
         M.resize(v.size());
         for (int i = size - 1; i >= 0; i--) {
             M[i].resize((int) log2(size - i) + 1);
             for (int j = 0; j <= log2(size - i); j++) {
                 if (j == 0) {
                     M[i][j] = v[i];
                 } else {
                     M[i][j] = min(M[i][j - 1], M[i + (1 << (j - 1))][j - 1]);
                 }
             }
         }

         lens.push_back(0);
         for (int i = 1; i <= size; i++) {
             lens.push_back(calcLens(i));
         }
     }

     int get(int l, int r) {
         if (l > r) {
             swap(l, r);
         }
         int x = lens[r - l + 1];
         return min(M[l][x], M[r - (1 << x) + 1][x]);
     }

 private:
     int size;
     vector<vector<int>> M;
     vector<int> lens;

     int calcLens(int len) {
         return len == 1 ? 0 : calcLens(len / 2) + 1;
     }
};

int main() {
    int n, m, a1;
    cin >> n >> m >> a1;
    vector<int> vec(n);
    vec[0] = a1;
    for (int i = 1; i < n; i++)
        vec[i] = gena(vec[i - 1]);
    SparseTable st(vec);
    int u, v;
    cin >> u >> v;
    int ans = 0;
    int _u = 0, _v = 0;
    for (int i = 1; i <= m; i++) {
        ans = st.get(u - 1, v - 1);
        _u = u, _v = v;
        u = ((17 * u + 751 + ans + 2 * i) % n) + 1;
        v = ((13 * v + 593 + ans + 5 * i) % n) + 1;
    }
    cout << _u << " " << _v << " " << ans << endl;
    return 0;
}
