#include <iostream>

using namespace std;

struct Node {
    Node *next = NULL;
    int value = 0;
};

class list {
 public:
     Node *tail;
     Node *head;

     list() {
         tail = nullptr;
         head = nullptr;
     }

     void add(int v) {
         Node *el = new Node;
         el->value = v;
         el->next = nullptr;
         if (tail) {
             tail->next = el;
         }
         tail = el;
         if (!head) {
             head = el;
         }
     }

     void pop_bot() {
         Node *temp = head->next;
         delete(head);
         if (head == tail) {
             head = nullptr;
             tail = nullptr;
         } else {
             head = temp;
         }
     }

     int bot() {
         return head->value;
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
            cout << s.bot() << endl;
            s.pop_bot();
        } else {
            int value;
            cin >> value;
            s.add(value);
        }
    }
    return 0;
}
