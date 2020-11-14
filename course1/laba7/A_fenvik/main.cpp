#include <iostream>
#include <vector>
#include <cassert>
#define ll long long
#define ui unsigned int

using namespace std;

ui a, b;
ui cur = 0;

ui nextRand(){
    cur = cur * a + b;
    return cur >> 8;
}

ll mod(ll value){
    return (value+2*4294967296)%4294967296;
}

int F(int i){
    return i&(i+1);
}
int next(int i){
    return i|(i+1);
}

class Fenwick{
 public:
     explicit Fenwick(ui n):size(n){
         mas.resize(n);
         madd.resize(n);
     }
     ll sum(ll l, ll r){
         return mod(sum(r) + 4294967296 - sum(l-1));
     }
     void add(ll value, ll l, ll r){
         add(value, r);
         add(-value, l-1);
     }
 private:
     ui size;
     vector<ll> mas;
     vector<ll> madd;
/*
     ll sum(int r){
         if (r == 0) return 0;
         int r_ = r;
         ll res = 0;
         while (r >= 0) {
             res = mod(res + mas[r] + madd[r] * (r-F(r)+1));
             r = F(r)-1;
         }
         r = next(r_);
         while (r < size){
             res = mod(res + madd[r]*(r-F(r)+1));
             r = next(r);
         }
         return res;
     }

     void add(ll value, int r){
         int r_ = r;
         while(r >= 0){
             madd[r] = mod(madd[r]+value);
             r = F(r)-1;
         }
         r = next(r_);
         while (r < size){
             mas[r] = mod(mas[r] + value*(r-F(r)+1));
             r = next(r);
         }
     }

*/
     ll sum(ll r){
         if(r<0) return 0;
         ll res = 0;
         for(ll i=r;i>=0;i=(i&(i+1))-1) res = mod(res + mas[i] + madd[i]*(i-(i&(i+1))+1));
         for(ll i=r|(r+1);i<size;i|=i+1) res = mod(res + madd[i]*(r-(i&(i+1))+1));
         return res;
     }

     void add(ll d, ll r){
         if(r<0) return ;
         for(ll i=r;i>=0;i=(i&(i+1))-1) madd[i] = mod(madd[i]+d);
         for(ll i=r|(r+1);i<size;i|=i+1) mas[i] = mod(mas[i]+d*(r-(i&(i+1))+1));
     }
};


int main() {
    int n, m, q;
    n = 16777216;
    cin >> m >> q;
    cin >> a >> b;
    Fenwick tree(n);
    for (int i = 0; i < m; i++){
        ll add = nextRand();
        ll l = nextRand();
        ll r = nextRand();
        tree.add(add, l, r);
        cout << tree.sum(0,n) << endl;
    }
    ll res = 0;
    for (int i = 0; i < q; i++){
        ll l = nextRand();
        ll r = nextRand();
        if (l > r) swap(l,r);
        res = mod(res + tree.sum(l, r));
    }
    cout << res;
    return 0;
}