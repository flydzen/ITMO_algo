#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int> &v, unsigned int left, unsigned int right, unsigned int mid) {
    unsigned int u1 = left;
    unsigned int u2 = mid;
    vector<int> res((int)right - left);
    while (u1 < mid && u2 < right) {
        if (v[u1] < v[u2]) {
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

void sort(vector<int> &v, unsigned int l, unsigned int r) {
    if (r - l <= 1) {
        return;
    }
    unsigned int mid = (l + r) / 2;
    sort(v, l, mid);
    sort(v, mid, r);
    merge(v, l, r, mid);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    unsigned int n;
    cin >> n;
    vector<int> v(n);
    for (unsigned int i = 0; i < n; i++) {
        cin >> v[i];
    }
    sort(v, 0, n);
    for (int el : v) {
        cout << el << " ";
    }
    return 0;
}