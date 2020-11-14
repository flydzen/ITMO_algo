#include <iostream>

using namespace std;

struct Node {
    Node *next = NULL;
    int value = 0;
};


class list {
 public:
     Node *head;

     list() {
         head = NULL;
     }

     void add(int v) {
         Node *el = new Node;
         el->value = v;
         el->next = head;
         head = el;
     }

     void pop() {
         Node *temp = head->next;
         delete (head);
         head = temp;
     }

     int top() {
         return head->value;
     }

     int get() {
         int val = head->value;
         Node *temp = head->next;
         delete (head);
         head = temp;
         return val;
     }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    list s;
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        char command;
        cin >> command;
        if (command == '-') {
            cout << s.get() << endl;
        } else {
            int value;
            cin >> value;
            s.add(value);
        }
    }
    return 0;
}
