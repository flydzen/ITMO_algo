#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    double a;
    cin >> n >> a;
    double l = 0;
    double r = a;
    double b = 0;
    while (r - l > 0.005 / n) {
        double mid = l + (r - l) / 2;
        double v1 = a;
        double v2 = mid;
        for (int i = 2; i < n; i++) {
            double v3 = 2 * v2 - v1 + 2;
            if (v3 <= 0) {
                l = mid;
                break;
            }
            v1 = v2;
            v2 = v3;
        }
        if (l != mid) {
            r = mid;
            b = v2;
        }
    }
    printf("%.2f", b);
    return 0;
}
