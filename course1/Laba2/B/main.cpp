#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int m;
        cin >> m;
        int l = -1;
        int r = n;
        while (r - l > 1) {
            int mid = l + (r - l) / 2;
            if (v[mid] < m) {
                l = mid;
            } else {
                r = mid;
            }
        }
        int _r = r + 1;
        l = r - 1;
        r = n;
        while (r - l > 1) {
            int mid = l + (r - l) / 2;
            if (v[mid] <= m) {
                l = mid;
            } else {
                r = mid;
            }
        }
        l += 1;
        if (l < _r) {
            cout << "-1 -1" << endl;
        } else {
            cout << _r << " " << l << endl;
        }
    }
    return 0;
}
