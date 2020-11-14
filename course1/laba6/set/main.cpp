#include <iostream>
#include <random>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

int seed;

mt19937 getRand(seed);

class Set {
 private:
     long long p = 93563;
     vector<int> *_array;
     long long a;
     long long b;

     int hash(int item) {
         if (item < 0) {
             item += 1000000000;
         }
         return (int) ((a * (long long) item + b) % p);
     }

 public:
     Set() {
         _array = new vector<int>[p];
         a = getRand() % p;
         b = getRand() % p;
     }

     void insert(int item) {
         if (exist(item)) return;

         int h = hash(item);
         _array[h].push_back(item);
     }

     int find(int item) {
         auto v = _array[hash(item)];
         for (size_t i = 0; i < v.size(); i++) {
             if (v[i] == item) {
                 return i;
             }
         }
         return -1;
     }

     bool exist(int item) {
         return find(item) != -1;
     }

     bool operator[](int i) {
         return exist(i);
     }

     void remove(int item) {
         int id = find(item);
         if (id == -1) return;
         vector<int> *vec = &_array[hash(item)];
         vec->erase(vec->begin() + id);
     }
};

int main() {
    seed = time(nullptr);
    string command;
    int item;
    Set s;
    ofstream fout("set.out");
    ifstream fin("set.in");
    while (fin >> command) {
        fin >> item;
        if (command == "insert") {
            s.insert(item);
        } else if (command == "exists") {
            fout << (s.exist(item) ? "true" : "false") << endl;
        } else {
            s.remove(item);
        }
    }
    return 0;
}
