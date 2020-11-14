#include <iostream>
#include <vector>

using namespace std;

int part(vector<int> &v, int l, int r) {
    r--;
    int x = v[l + (r - l) / 2];
    while (l <= r) {
        while (v[l] < x) {
            l++;
        }
        while (v[r] > x) {
            r--;
        }
        if (l >= r) {
            break;
        }
        swap(v[l++], v[r--]);
    }
    return l;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k, a, b, c, v1, v2;
    cin >> n >> k >> a >> b >> c >> v1 >> v2;
    k--;
    vector<int> v(n);
    v[0] = v1;
    v[1] = v2;
    for (int i = 2; i < n; i++) {
        v[i] = a * v[i - 2] + b * v[i - 1] + c;
    }
    cout << endl;
    int l = 0;
    int r = n;
    while (true) {
        int m = part(v, l, r);
        if (m == k) {
            cout << v[m];
            break;
        } else if (m < k) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return 0;
}