#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 1; i <= n; i++) {
        v[i - 1] = i;
    }
    for (int i = 0; i < n; i++) {
        swap(v[i], v[i / 2]);
    }
    for (int i = 0; i < n; i++) {
        cout << v[i] << " ";
    }
    return 0;
}
