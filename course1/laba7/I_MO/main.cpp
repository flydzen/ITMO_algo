#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

int k;
long long F;

struct Q {
    int l;
    int r;
    int id;
    Q(int l, int r, int id) : l(l), r(r), id(id) {}
};

bool comp(Q &a, Q &b) {
    return a.l / k != b.l / k ? a.l < b.l : a.r < b.r;
}

void add(int value, long long count[1000005]) {
    long long cv = count[value];
    count[value]++;
    F += ((cv + 1) * (cv + 1) - cv * cv) * value;
}

void del(int value, long long count[1000005]) {
    long long cv = count[value];
    count[value]--;
    F += ((cv - 1) * (cv - 1) - cv * cv) * value;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    k = (int) sqrt(n);
    vector<Q> q;
    vector<int> v(n);
    int l, r;
    long long count[1000005];
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        count[v[i]] = 0;
    }
    for (int i = 0; i < m; i++) {
        cin >> l >> r;
        q.emplace_back(l - 1, r - 1, i);
    }
    sort(q.begin(), q.end(), comp);
    vector<pair<int, unsigned long long>> res;
    int a = 1, b = 0;
    for (Q i : q) {
        while (a > i.l)
            add(v[--a], count);
        while (b < i.r)
            add(v[++b], count);
        while (a < i.l)
            del(v[a++], count);
        while (b > i.r) {
            del(v[b--], count);
        }
        res.emplace_back(i.id, F);
    }
    sort(res.begin(), res.end());
    for (int i = 0; i < m; i++)
        cout << res[i].second << endl;
    return 0;
}
