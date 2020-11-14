#include <iostream>
#include <vector>
#include <cassert>
#define ll long long
#define ui unsigned int

using namespace std;

ui a, b;
ui cur = 0;
const int N = 16777216;
const long long MD = 4294967296;

ui nextRand(){
    cur = cur * a + b;
    return cur >> 8;
}


ll mod(ll value){
    return value%4294967296;
}

class Array{
 public:
     Array(){
        mass.resize(N+2);
     }
     void add(ui l, ui r, ui value){
         mass[l] += value;
         mass[r+1] -= value;
     }

     void makePref(){
         for (int i = 1; i < N + 1; i++){
             int xxx = mass[i];
             mass[i+1] += mass[i];
             if (mass[i] < 0) {
                 mass[i] = mod(mass[i]) + MD;
             }
             mass[i] = mod(mass[i - 1] + mass[i]);
         }
     }

     ui get(ui l, ui r){
         if (mass[r+1] < mass[l]){
             return (ui)mod(mass[r] - mass[l-1]) + MD;
         }
         return (ui)mod(mass[r] - mass[l-1]);
     }

 private:
     vector<long long> mass;
};


int main() {
    int m, q;
    cin >> m >> q;
    cin >> a >> b;
    Array A;
    for (int i = 0; i < m; i++){
        ui add = nextRand();
        ui l = nextRand();
        ui r = nextRand();
        A.add(l, r, add);
    }
    A.makePref();
    ll res = 0;
    for (int i = 0; i < q; i++){
        ll l = nextRand();
        ll r = nextRand();
        if (l > r) swap(l,r);
        res = mod(res + A.get(l, r));
    }
    cout << res;
    return 0;
}