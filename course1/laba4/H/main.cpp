#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long

using namespace std;

int N = 16, n;
vector<int> a;
vector<vector<int>> g;
vector<vector<ll>> c;
vector<int> way;

int gcd(int x, int y) {
    while (y) {
        x %= y;
        swap(x, y);
    }
    return x;
}

ll check(int mask, int v, ll num) {
    if (c[mask][v] == -1 || c[mask][v] >= num) {
        if ((1 << n) - 1 == mask) {
            if (num == 1) {
                for (auto x : way)
                    cout << a[x] << ' ';
                cout << a[v] << endl;
                exit(0);
            }
            return 1;
        }
        c[mask][v] = 0;
        way.push_back(v);
        for (auto x : g[v]) {
            if (!((1 << x) & mask)) {
                ll answer = check(mask ^ (1 << x), x, num);
                c[mask][v] += answer;
                num -= answer;
            }
        }
        way.pop_back();
        return c[mask][v];
    }
    return c[mask][v];
}

int main() {
    ll m, k;
    cin >> n >> m >> k;
    a = vector<int>(N);
    g = vector<vector<int>>(N, vector<int>());
    c = vector<vector<ll>>(1 << N, vector<ll>(N, -1));
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(a.begin(), a.begin() + n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j && gcd(a[i], a[j]) >= k)
                g[i].push_back(j);
    for (int i = 0; i < n; ++i) {
        m -= check(1 << i, i, m);
    }
    cout << -1;
}
