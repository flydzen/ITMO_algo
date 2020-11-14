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

class LinkedSet {
 private:
     long long p = 93563;
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

 public:
     LinkedSet() {
         _array = vector<list<node>>((int) p);
         a = getRand() % p;
         b = getRand() % p;
         prev = nullptr;
         head = nullptr;
     }

     explicit LinkedSet(string &item) {
         _array = vector<list<node>>((int) p);
         a = getRand() % p;
         b = getRand() % p;
         prev = nullptr;
         head = nullptr;
         insert(item);
     }

     void insert(string &item) {
         auto cur = _insert(item);  // указатель на добавленный элемент (или нулл)
         if (cur) {  // если добавили
             if (prev)  // если последний добавленный есть
                 prev->next = cur;  // следующий для последгого это новый
             cur->prev = prev;  // прошлый для нового это последний добавленынй
             prev = cur;  // говорим, что прошлый это теперь новый
             if (!head) {  // если нет головы, то новый это голова
                 head = cur;
             }
         }
     }

     node *_insert(string &item) {
         if (exist(item)) return nullptr;

         int h = hash(item);
         _array[h].emplace_back(item);
         return &_array[h].back();
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
         v.insert(v.begin(), to_string(v.size()));
         return v;
     }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    seed = time(nullptr);
    string command;
    string item;
    LinkedSet s;
    ofstream fout("set.out");
    ifstream fin("set.in");
    while (fin >> command) {
        fin >> item;
        if (command == "insert") {
            s.insert(item);
        } else if (command == "exists") {
            fout << (s.exist(item) ? "true" : "false") << endl;
        } else if (command == "print") {
            auto p = s.print();
            for (const auto &i : p) {
                fout << i << " ";
            }
            fout << endl;
        } else {
            s.remove(item);
        }
    }
    fout.close();
    fin.close();
    return 0;
}
