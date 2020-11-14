#include <iostream>
#include <vector>
#include <cmath>

#define ll long long

using namespace std;

struct box {
    int t;
    int delay;
};

int m, n, p;


void merge(vector<ll> &vector, unsigned int l, unsigned int r, unsigned int mid);

void sort(vector<ll> &v, unsigned int l, unsigned int r);

ll check(ll time, vector<box> &cash) {
    vector<ll> times(m);
    for (int i = 0; i < m; i++) {
        if (cash[i].t == 0 && cash[i].delay >= time) {
            return LONG_LONG_MAX / 2;
        } else {
            if (cash[i].t == 0) {
                times[i] = 0;
                continue;
            }
            times[i] = max((ll) 0, (time - cash[i].delay) / cash[i].t);
        }
    }
    sort(times, 0, m);
    ll s = 0;
    for (int i = 0; i < n; i++) {
        s += times[i];
    }
    return s;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m;
    vector<box> cashier(m);
    for (int i = 0; i < m; i++) {
        int a, b, t;
        cin >> a >> b >> t;
        box temp{};
        temp.t = a;
        temp.delay = b + t;
        cashier[i] = temp;
    }
    cin >> n >> p;
    n = min(n, p);
    ll l = -1;
    ll r = (ll)2e15;
    while (r - l > 1) {
        ll time = (r + l) / 2;
        ll cou = check(time, cashier);
        if (cou < p) {
            l = time;
        } else {
            r = time;
        }
    }
    cout << r;
    return 0;
}

void merge(vector<ll> &v, unsigned int left, unsigned int right, unsigned int mid) {
    unsigned int u1 = left;
    unsigned int u2 = mid;
    vector<ll> res((int) right - left);
    while (u1 < mid && u2 < right) {
        if (v[u1] > v[u2]) {
            res[u1 + u2 - left - mid] = v[u1];
            u1++;
        } else {
            res[u1 + u2 - left - mid] = v[u2];
            u2++;
        }
    }
    while (u1 < mid) {
        res[u1 + u2 - left - mid] = v[u1];
        u1++;
    }
    while (u2 < right) {
        res[u1 + u2 - left - mid] = v[u2];
        u2++;
    }
    for (unsigned int i = 0; i < right - left; i++) {
        v[left + i] = res[i];
    }
}


void sort(vector<ll> &v, unsigned int l, unsigned int r) {
    if (r - l <= 1) {
        return;
    }
    unsigned int mid = (l + r) / 2;
    sort(v, l, mid);
    sort(v, mid, r);
    merge(v, l, r, mid);
}
