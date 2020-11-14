#include <iostream>
#include <random>
#include <vector>
#include <ctime>
#include <fstream>
#include <list>

using namespace std;

int seed;

mt19937 getRand(seed);

struct node {
    node *next;
    node *prev;
    string value;
    explicit node(string &_value) {
        value = move(_value);
        next = nullptr;
        prev = nullptr;
    }
};

class Set {
 private:
     long long p = 101;
     vector<list<node>> _array;
     long long a;
     long long b;
     node *prev;
     node *head;

     int hash(string &item) {
         long long h = 0;
         for (int i = 0; i < (int) item.size(); i++) {
             h = (h + (int) ((a + i) * item[i] + b)) % p;
         }
         return (int) h;
     }

     node *_insert(string &item) {
         if (exist(item)) return nullptr;

         int h = hash(item);
         _array[h].emplace_back(item);
         return &_array[h].back();
     }

 public:
     Set() {
         _array = vector<list<node>>((int) p);
         a = getRand() % p;
         b = getRand() % p;
         prev = nullptr;
         head = nullptr;
     }

     explicit Set(string &item) {
         _array = vector<list<node>>((int) p);
         a = getRand() % p;
         b = getRand() % p;
         prev = nullptr;
         head = nullptr;
         insert(item);
     }

     void insert(string &item) {
         auto cur = _insert(item);
         if (cur) {
             if (prev)
                 prev->next = cur;
             cur->prev = prev;
             prev = cur;
             if (!head) {
                 head = cur;
             }
         }
     }

     list<node>::iterator find(string &item, int h) {
         list<node> &v = _array[h];
         for (auto i = v.begin(); i != v.end(); i++) {
             if (i->value == item) {
                 return i;
             }
         }
         return v.end();
     }

     bool exist(string &item) {
         int h = hash(item);
         bool exists = find(item, h) != _array[h].end();
         return exists;
     }

     void remove(string &item) {
         int h = hash(item);
         auto it = find(item, h);
         if (it == _array[h].end()) return;
         node *el = &*it;
         if (el->prev) {
             el->prev->next = el->next;
         } else {
             head = el->next;
         }
         if (el->next) {
             el->next->prev = el->prev;
         }
         if (el == prev) {
             prev = el->prev;
         }
         _array[h].erase(it);
     }

     vector<string> print() {
         node *cur = head;
         vector<string> v;
         while (cur) {
             v.push_back(cur->value);
             cur = cur->next;
         }
         return v;
     }
};

struct mNode {
    string key;
    Set set;
    explicit mNode(string &_key, string &value) {
        key = move(_key);
        set.insert(value);
    }
};

class Map {
 private:
     long long p = 93563;
     vector<list<mNode>> _array;
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
         _array = vector<list<mNode>>((int)p);
         a = getRand() % p;
         b = getRand() % p;
     }

     // возвращает массив ключ - сет значений
     list<mNode>::iterator find(string &key, int h) {
         auto &v = _array[h];
         for (auto i = v.begin(); i != v.end(); i++) {
             if (i->key == key) {
                 return i;
             }
         }
         return v.end();
     }

     void insert(string &key, string &value) {
         int h = hash(key);
         auto &v = _array[h];
         auto f = find(key, h);
         if (f == v.end()) {
             v.emplace_back(key, value);
         } else {
             f->set.insert(value);
         }
     }

     vector<string> get(string &key) {
         int h = hash(key);
         auto &v = _array[h];
         auto f = find(key, h);
         if (f == v.end()) {
             return {};
         } else {
             return f->set.print();
         }
     }

     void removeAll(string &key) {
         int h = hash(key);
         auto &v = _array[h];
         auto f = find(key, h);
         if (f == v.end()) return;
         v.erase(f);
     }

     void remove(string &key, string &value) {
         int h = hash(key);
         auto &v = _array[h];
         auto f = find(key, h);
         if (f == v.end()) return;
         f->set.remove(value);
     }
};

int main() {
    seed = time(nullptr);
    string command, key, value;
    Map m;
    ifstream fin("multimap.in");
    ofstream fout("multimap.out");
    while (fin >> command) {
        fin >> key;
        if (command == "put") {
            fin >> value;
            m.insert(key, value);
        } else if (command == "get") {
            auto t = m.get(key);
            fout << t.size() << " ";
            for (const string &i : t) {
                fout << i << " ";
            }
            fout << endl;
        } else if (command == "delete") {
            fin >> value;
            m.remove(key, value);
        } else {
            m.removeAll(key);
        }
    }
    return 0;
}
