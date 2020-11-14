#include <iostream>
#include <vector>
#define ll long long
using namespace std;

class Fenwick {
 public:
     explicit Fenwick(vector<ll> &v, int n) : size(n), v(v) {
         mas.resize(n);
         for (int i = 0; i < n; i++)
             for (int j = i; j < n; j = (j | (j + 1)))
                 mas[j] += v[i];
     }
     ll sum(int l, int r) {
         return sum(r) - sum(l - 1);
     }
     void set(ll value, int i) {
         ll delta = value - v[i];
         v[i] = value;
         while (i < size) {
             mas[i] += delta;
             i |= (i + 1);
         }
     }

 private:
     int size;
     vector<ll> mas;
     vector<ll> v;

     ll sum(int r) {
         ll res = 0;
         while (r > -1) {
             res += mas[r];
             r = (r & (r + 1)) - 1;
         }
         return res;
     }
};

int main() {
    int n;
    cin >> n;
    vector<ll> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    Fenwick tree(v, n);
    string oper;
    while (cin >> oper) {
        if (oper == "sum") {
            int l, r;
            cin >> l >> r;
            cout << tree.sum(l - 1, r - 1) << endl;
        } else {
            int i, data;
            cin >> i >> data;
            tree.set(data, i - 1);
        }
    }
    return 0;
}
