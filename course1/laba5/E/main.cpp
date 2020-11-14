#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


struct node {
    int x, y, idn;
    node *left;
    node *right;
    node *parent;
};

node *make_node(int x, int y, int id) {
    auto *n = new node{};
    n->x = x;
    n->y = y;
    n->idn = id;
    n->left = nullptr;
    n->right = nullptr;
    n->parent = nullptr;
    return n;
}

vector<node *> answer;

void print(node *el) {
    answer[el->idn] = el;
    if (el->left != nullptr)
        print(el->left);
    if (el->right != nullptr)
        print(el->right);
}

bool compare(node *n1, node *n2) {
    return n1->x < n2->x;
}

int id(node *el) {
    if (el == nullptr)
        return 0;
    else return el->idn + 1;
}

int main() {
    int n;
    cin >> n;
    vector<node *> v;
    v.reserve(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        v.push_back(make_node(x, y, i));
    }
    sort(v.begin(), v.end(), compare);

    node *head = v[0];
    node *last = v[0];
    for (int i = 1; i < n; i++) {
        node *el = v[i];
        if (el->y > last->y) {
            last->right = el;
            el->parent = last;
        } else if (el->y == last->y) {
            cout << "NO";
            return 0;
        } else {
            node *temp = last;
            while (temp->y > el->y && temp->parent != nullptr) {
                temp = temp->parent;
            }
            if (temp->y == el->y) {
                cout << "NO";
                return 0;
            }
            if (temp->y < el->y) {
                el->left = temp->right;
                el->left->parent = el;
                temp->right = el;
                el->parent = temp;
            } else {
                el->left = head;
                head->parent = el;
                head = el;
            }
        }
        last = el;
    }
    answer = vector<node *>(n);
    print(head);
    cout << "YES" << endl;
    for (node *el : answer) {
        cout << id(el->parent) << " " << id(el->left) << " " << id(el->right) << endl;
    }
    return 0;
}
