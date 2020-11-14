#include <iostream>

using namespace std;

struct vertex {
    int key;
    vertex *l;
    vertex *r;
    vertex *p;
};

vertex *make_v(int value, vertex *left = nullptr,
               vertex *right = nullptr, vertex *parent = nullptr) {
    auto *v = new vertex;
    v->key = value;
    v->l = left;
    v->r = right;
    v->p = parent;
    return v;
}

class binaryTree {
 public:
     void print() {
         print(head);
     }

     vertex *find(int x) {
         return find(head, x);
     }

     vertex *next(int x) {
         if (head == nullptr)
             return nullptr;
         if (maxi(head)->key <= x)
             return nullptr;
         vertex *v = head;
         vertex *lst = nullptr;
         while (v != nullptr) {
             if (v->key > x) {
                 lst = v;
                 v = v->l;
             } else {
                 v = v->r;
             }
         }
         return lst;
     }
     vertex *prev(int x) {
         if (head == nullptr)
             return nullptr;
         if (mini(head)->key >= x)
             return nullptr;
         vertex *v = head;
         vertex *lst = nullptr;
         while (v != nullptr) {
             if (v->key < x) {
                 lst = v;
                 v = v->r;
             } else {
                 v = v->l;
             }
         }
         return lst;
     }

     void insert(int x) {
         if (head == nullptr)
             head = make_v(x);
         else if (find(x) == nullptr)
             insert(head, nullptr, x);
     }

     void del(int x) {
         if (head != nullptr && find(head, x))
             head = del(head, x);
     }

 private:
     vertex *head;

     static void print(vertex *v) {
         if (v != nullptr) {
             cout << v->key << endl;
             print(v->l);
             print(v->r);
         }
     }

     static vertex *find(vertex *v, int x) {
         if (v == nullptr || v->key == x)
             return v;
         if (x < v->key)
             return find(v->l, x);
         else
             return find(v->r, x);
     }

     static vertex *mini(vertex *v) {
         if (v->l == nullptr)
             return v;
         return mini(v->l);
     }

     static vertex *maxi(vertex *v) {
         if (v->r == nullptr)
             return v;
         return maxi(v->r);
     }

     static vertex *del(vertex *v, int x) {
         if (v == nullptr) {
             return v;
         }
         if (x < v->key) {
             v->l = del(v->l, x);
         } else if (x > v->key) {
             v->r = del(v->r, x);
         } else if (v->l != nullptr && v->r != nullptr) {
             v->key = mini(v->r)->key;
             v->r = del(v->r, v->key);
         } else {
             if (v->l != nullptr)
                 v = v->l;
             else if (v->r != nullptr)
                 v = v->r;
             else
                 v = nullptr;
         }
         return v;
     }

     static vertex *insert(vertex *v, vertex *p, int x) {
         if (v == nullptr)
             return make_v(x, nullptr, nullptr, p);
         else if (x < v->key)
             v->l = insert(v->l, v, x);
         else
             v->r = insert(v->r, v, x);
         return v;
     }
};

int main() {
    binaryTree bt{};
    string inp;
    while (cin >> inp) {
        int value;
        cin >> value;
        if (inp == "insert") {
            bt.insert(value);
        } else if (inp == "exists") {
            cout << (bt.find(value) != nullptr ? "true" : "false") << endl;
        } else if (inp == "delete") {
            bt.del(value);
        } else if (inp == "next") {
            auto nxt = bt.next(value);
            if (nxt == nullptr)
                cout << "none" << endl;
            else
                cout << nxt->key << endl;
        } else if (inp == "prev") {
            auto prv = bt.prev(value);
            if (prv == nullptr)
                cout << "none" << endl;
            else
                cout << prv->key << endl;
        } else {
            bt.print();
        }
    }
    return 0;
}
