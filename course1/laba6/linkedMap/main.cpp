#include <iostream>
#include <random>
#include <utility>
#include <vector>
#include <ctime>
#include <fstream>
#include <list>

using namespace std;

int seed;

mt19937 getRand(seed);

struct node {
    string key, value;
    node *prev;
    node *next;

    node(string _key, string _value) {
        key = move(_key);
        value = move(_value);
        prev = nullptr;
        next = nullptr;
    }
};

class LinkedMap {
 private:
     long long p = 93563;
     vector<list<node>> _array;
     long long a;
     long long b;
     node *pre;

     int hash(string &item) {
         long long h = 0;
         for (int i = 0; i < (int) item.size(); i++) {
             h = (h + (int) ((a + i) * item[i] + b)) % p;
         }
         return (int) h;
     }

 public:
     LinkedMap() {
         _array = vector<list<node>>((int)p);
         a = getRand() % p;
         b = getRand() % p;
         pre = nullptr;
     }

     void insert(string &key, string &value) {
         node *cur = _insert(key, value);
         if (cur != nullptr) {
             if (pre)
                 pre->next = cur;
             cur->prev = pre;
             pre = cur;
         }
     }

     node *_insert(string &key, string &value) {
         int h = hash(key);
         auto &v = _array[h];
         auto f = find(key, h);
         if (f == v.end()) {
             v.emplace_back(key, value);
             return &v.back();
         } else {
             f->value = value;
             return nullptr;
         }
     }

     list<node>::iterator find(string &key, int h) {
         list<node> &v = _array[h];
         for (auto i = v.begin(); i != v.end(); i++) {
             if (i->key == key) {
                 return i;
             }
         }
         return v.end();
     }

     string prev(string &key) {
         int h = hash(key);
         auto &v = _array[h];
         auto f = find(key, h);
         if (f == v.end() || !f->prev) {
             return "none";
         } else {
             return f->prev->value;
         }
     }

     string next(string &key) {
         int h = hash(key);
         auto &v = _array[h];
         auto f = find(key, h);
         if (f == v.end() || !f->next) {
             return "none";
         } else {
             return f->next->value;
         }
     }

     string get(string &key) {
         int h = hash(key);
         auto f = find(key, h);
         auto &v = _array[h];
         return f == v.end() ? "none" : f->value;
     }

     string operator[](string &key) {
         return get(key);
     }

     void remove(string &key) {
         int h = hash(key);
         auto &v = _array[h];
         auto f = find(key, h);
         if (f == v.end()) return;
         if (f->prev != nullptr)
             f->prev->next = f->next;
         if (f->next != nullptr)
             f->next->prev = f->prev;
         if (&*f == pre) {
             pre = f->prev;
         }
         v.erase(f);
     }
};

int main() {
    seed = time(nullptr);
    string command, key, value;
    LinkedMap m;
    ifstream fin("linkedmap.in");
    ofstream fout("linkedmap.out");
    while (fin >> command) {
        fin >> key;
        if (command == "put") {
            fin >> value;
            m.insert(key, value);
        } else if (command == "get") {
            fout << m[key] << endl;
        } else if (command == "prev") {
            fout << m.prev(key) << endl;
        } else if (command == "next") {
            fout << m.next(key) << endl;
        } else {
            m.remove(key);
        }
    }
    return 0;
}
