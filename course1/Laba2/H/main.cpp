#include <iostream>
#include <vector>

using namespace std;

unsigned int cur = 0;

unsigned int nextRand24(unsigned int a, unsigned int b) {
    cur = cur * a + b;
    return cur >> 8;
}

void merge(vector<int> &v, unsigned int left, unsigned int right,
        unsigned int mid, unsigned long long &cou) {
    unsigned int u1 = left;
    unsigned int u2 = mid;
    vector<int> res((int) right - left);
    while (u1 < mid && u2 < right) {
        if (v[u1] <= v[u2]) {
            res[u1 + u2 - left - mid] = v[u1];
            u1++;
        } else {
            res[u1 + u2 - left - mid] = v[u2];
            cou += mid - u1;
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

void sort(vector<int> &v, unsigned int l, unsigned int r, unsigned long long &cou) {
    if (r - l <= 1) {
        return;
    }
    unsigned int mid = (l + r) / 2;
    sort(v, l, mid, cou);
    sort(v, mid, r, cou);
    merge(v, l, r, mid, cou);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    unsigned int n, m, a, b;
    cin >> n >> m >> a >> b;
    vector<int> v(n);
    for (unsigned int i = 0; i < n; i++) {
        v[i] = nextRand24(a, b) % m;
    }
    unsigned long long cou = 0;
    sort(v, 0, n, cou);
    cout << cou << endl;
    return 0;
}
