#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;

int main(){
    int n,m,v1,v2;
    cin >> n >> m;
    unordered_set<pair<int,int>> s;
    for (int i = 0; i<m ;i++) {
        cin >> v1 >> v2;
        if (v1 == v2) continue;
        if (v1 > v2) swap(v1,v2);
        s.insert(make_pair(v1,v2));
    }
    cout << n << ' ' << s.size() << endl;
    for(pair<int,int> a : s){
        cout << a.first << ' ' << a.second << endl;
    }
    return 0;
}