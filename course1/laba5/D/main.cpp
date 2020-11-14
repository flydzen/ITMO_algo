#include <iostream>

using namespace std;

struct vertex {
    int key;
    int height;
    int cLeft, cRight;
    vertex *left, *right;
};

vertex *make_v(int value) {
    auto *v = new vertex;
    v->key = value;
    v->left = v->right = nullptr;
    v->height = 1;
    v->cLeft = v->cRight = 0;
    return v;
}

class binaryTree {
 public:
     void print() {
         print(head);
     }

     int kMax(int x) {
         return kMax(x - 1, head, 0);
     }

     vertex *find(int x) {
         return find(head, x);
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

     static int kMax(int k, vertex *v, int w) {
         if (v->cRight + w > k) {
             return kMax(k, v->right, w);
         } else if (v->cRight + w < k) {
             return kMax(k, v->left, 1 + w + v->cRight);
         } else {
             return v->key;
         }
     }

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
         v->cLeft = v->left ? v->left->cLeft + v->left->cRight + 1 : 0;
         v->cRight = v->right ? v->right->cLeft + v->right->cRight + 1 : 0;
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
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int value;
        cin >> inp;
        cin >> value;
        if (inp == "+1" || inp == "1") {
            bt.insert(value);
        } else if (inp == "0") {
            cout << bt.kMax(value) << endl;
        } else if (inp == "-1") {
            bt.del(value);
        } else {
            bt.print();
        }
    }
    return 0;
}
