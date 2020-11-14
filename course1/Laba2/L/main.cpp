#include <iostream>
#include <vector>
#include <map>

using namespace std;

template<typename T>
void merge(vector<T> &v, int left, int right, int mid) {
    int u1 = left;
    int u2 = mid;
    vector<T> res((int) right - left);
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
    for (int i = 0; i < right - left; i++) {
        v[left + i] = res[i];
    }
}

template<typename T>
void sort(vector<T> &v, int l, int r) {
    if (r - l <= 1) {
        return;
    }
    int mid = (l + r) / 2;
    sort(v, l, mid);
    sort(v, mid, r);
    merge(v, l, r, mid);
}

int part(vector<pair<double, int>> &v, int l, int r) {
    int m = l;
    for (int i = l; i < r; i++) {
        if (v[i].first < v[r].first) {
            swap(v[m++], v[i]);
        }
    }
    swap(v[m], v[r]);
    return m;
}

void kt(vector<pair<double, int>> &v, int k) {
    int l = 0;
    int r = (int) v.size() - 1;
    while (true) {
        int m = part(v, l, r);
        if (m == k) {
            return;
        } else if (m < k) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; i++) {
        double t1, t2;
        cin >> t1 >> t2;
        v[i] = make_pair(t1, t2);
    }
    vector<pair<double, int>> a(n);
    double l = 0;
    double r = 10000002;
    while (r - l > 0.000000003) {
        double x = l + (r - l) / 2;
        for (int i = 0; i < n; i++) {
            a[i] = make_pair(v[i].first - x * v[i].second, i);
        }
        kt(a, n - k);
        long double sum = 0;
        for (int i = n - k; i < n; i++) {
            sum += a[i].first;
        }
        if (sum < 0) {
            r = x;
        } else {
            l = x;
        }
    }
    vector<int> answer;
    for (int i = n - k; i < n; i++) {
        answer.push_back(a[i].second);
    }
    sort(answer, 0, k);
    for (int el : answer) {
        cout << el + 1 << " ";
    }
    return 0;
}
