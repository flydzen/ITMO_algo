#include <iostream>
#include <random>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

int seed;

mt19937 getRand(seed);

class Map {
 private:
     long long p = 93563;
     vector<pair<string, string>> *_array;
     long long a;
     long long b;

     int hash(string &item) {
         long long h = 0;
         for (int i = 0; i < (int) item.size(); i++) {
             h = (h + (int) ((a + i) * item[i] + b)) % p;
         }
         return (int) h;
     }

 public:
     Map() {
         _array = new vector<pair<string, string>>[p];
         a = getRand() % p;
         b = getRand() % p;
     }

     void insert(string &key, string &value) {
         auto f = find(key);
         if (f.second == -1) {
             f.first.emplace_back(key, value);
         } else {
             f.first[f.second].second = value;
         }
     }

     pair<vector<pair<string, string>> &, int> find(string &key) {
         vector<pair<string, string>> &v = _array[hash(key)];
         for (size_t i = 0; i < v.size(); i++) {
             if (v[i].first == key) {
                 return {v, i};
             }
         }
         return {v, -1};
     }

     string get(string &key) {
         auto f = find(key);
         return f.second == -1 ? "none" : f.first[f.second].second;
     }

     string operator[](string &key) {
         return get(key);
     }

     void remove(string &key) {
         auto f = find(key);
         if (f.second == -1) return;
         f.first.erase(f.first.begin() + f.second);
     }
};

int main() {
    seed = time(nullptr);
    string command, key, value;
    Map m;
    ifstream fin("map.in");
    ofstream fout("map.out");
    while (fin >> command) {
        fin >> key;
        if (command == "put") {
            fin >> value;
            m.insert(key, value);
        } else if (command == "get") {
            fout << m[key] << endl;
        } else {
            m.remove(key);
        }
    }
    return 0;
}
