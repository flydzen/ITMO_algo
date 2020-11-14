#include <iostream>
#include <random>
#include <ctime>
#include <unordered_map>

using namespace std;

int _hash(string &s) {
    int h = 0;
    size_t n = s.size();
    for (int i = (int) n - 1; i > -1; i--) {
        int a = s[n-1-i];
        int b = (int) pow(31, i);
        h += a * b;
    }
    return h;
}

int main() {
    unordered_map<int32_t, string> set;
    cout << 'a'*(int)pow(31,1) << endl;
    cout << "" << endl;
    for (int i = 'A'; i <= 'z'; i++) {
        for (int j = 'A'; j <= 'z'; j++) {
            if ( (90 < i && i < 97) || (90 < j && j < 97))
                continue;
            string s = "";
            s += (char) (i);
            s += (char) (j);
            if (set.find(_hash(s)) != set.end()) {
                cout << s << endl;
                cout << set[_hash(s)] << endl;
                cout << _hash(s) << endl;
                exit(0);
            } else {
                set[_hash(s)] = s;
            }
        }
    }

    return 0;
}