#include <iostream>

using namespace std;

struct vertex {
    int key;
    int height;
    vertex *left;
    vertex *right;
};

vertex *make_v(int value) {
    auto *v = new vertex;
    v->key = value;
    v->left = v->right = nullptr;
    v->height = 1;
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
                 v = v->left;
             } else {
                 v = v->right;
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
                 v = v->right;
             } else {
                 v = v->left;
             }
         }
         return lst;
     }

     void insert(int x) {
         if (head == nullptr)
             head = make_v(x);
         else if (find(x) == nullptr)
             head = insert(head, x);
     }

     void del(int x) {
         if (head != nullptr && find(head, x))
             head = del(head, x);
     }

 private:
     vertex *head;

     static vertex *lowLeftRotate(vertex *v) {
         vertex *temp = v->right;
         v->right = temp->left;
         temp->left = v;
         setHeight(v);
         setHeight(temp);
         return temp;
     }

     static vertex *lowRightRotate(vertex *v) {
         vertex *temp = v->left;
         v->left = temp->right;
         temp->right = v;
         setHeight(v);
         setHeight(temp);
         return temp;
     }

     static vertex *bigLeftRotate(vertex *v) {
         v->right = lowRightRotate(v->right);
         return lowLeftRotate(v);
     }

     static vertex *bigRightRotate(vertex *v) {
         v->left = lowLeftRotate(v->left);
         return lowRightRotate(v);
     }

     static vertex *balance(vertex *v) {
         if (v == nullptr)
             return v;
         setHeight(v);
         int b = getBalance(v);
         if (b == -2) {
             if (getBalance(v->right) > 0)
                 return bigLeftRotate(v);
             else
                 return lowLeftRotate(v);
         } else if (b == 2) {
             if (getBalance(v->left) < 0)
                 return bigRightRotate(v);
             else
                 return lowRightRotate(v);
         }
         return v;
     }

     static void setHeight(vertex *v) {
         v->height = max(getHeight(v->left), getHeight(v->right)) + 1;
     }

     static int getBalance(vertex *v) {
         return getHeight(v->left) - getHeight(v->right);
     }

     static int getHeight(vertex *v) {
         return v != nullptr ? v->height : 0;
     }

     static void print(vertex *v) {
         if (v != nullptr) {
             cout << v->key << endl;
             print(v->left);
             print(v->right);
         }
     }

     static vertex *find(vertex *v, int x) {
         if (v == nullptr || v->key == x)
             return v;
         if (x < v->key)
             return find(v->left, x);
         else
             return find(v->right, x);
     }

     static vertex *mini(vertex *v) {
         if (v->left == nullptr)
             return v;
         return mini(v->left);
     }

     static vertex *maxi(vertex *v) {
         if (v->right == nullptr)
             return v;
         return maxi(v->right);
     }

     static vertex *del(vertex *v, int x) {
         if (v == nullptr) {
             return v;
         }
         if (x < v->key) {
             v->left = del(v->left, x);
         } else if (x > v->key) {
             v->right = del(v->right, x);
         } else if (v->left != nullptr && v->right != nullptr) {
             v->key = mini(v->right)->key;
             v->right = del(v->right, v->key);
         } else {
             if (v->left != nullptr)
                 v = v->left;
             else if (v->right != nullptr)
                 v = v->right;
             else
                 v = nullptr;
         }
         return balance(v);
     }

     static vertex *insert(vertex *v, int x) {
         if (v == nullptr)
             return make_v(x);
         else if (x < v->key)
             v->left = insert(v->left, x);
         else
             v->right = insert(v->right, x);
         return balance(v);
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