#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


int main() {
    int n,k;
    cin >> n >> k;
    vector<int> x(n);
    for(int i=0;i<n;i++){
        cin >> x[i];
    }
    int prev[n];
    prev[0] = x[0];
    for(int i=1;i<n;i++){
        prev[i] = prev[i-1] + x[i];
    }
    vector<vector<int>> cost(n, vector<int>(n, 0));
    vector<vector<int>> m(n, vector<int>(n, 0));
    int i=0;
    for(int l=0;l<n;l++){
        i=l;
        for(int r=l;r<=n;r++){
            while((prev[i] - prev[l]) < (prev[r] - prev[i+1])) i++;
            m[l][r] = i;
            for(int z = l;z<=r;z++){
                cost[l][r] += abs(x[i] - x[z]);
            }
            //cost[l][r] = abs(prev[i] - prev[l]) + abs(prev[r] - prev[i+1]);
        }
    }
    vector<vector<int>> f(k+1, vector<int>(n+1, 0));
    vector<vector<int>> p(k+1, vector<int>(n+1, 0));
    for(int k1 = 2;k1<=k;k1++){
        for(int n1=n;n1>=k1;n1--){
            f[k1][n1] = INT_MAX;
            for(int i=0;i<n;i++){
                int temp = f[k1-1][i] + cost[i+1][n1];
                if(temp<f[k1][n1]){
                    f[k1][n1] = temp;
                    p[k1][n1] = i;
                }

            }
        }
    }
    cout << f[k][n];

    return 0;
}