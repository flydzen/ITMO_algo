#include <iostream>

using namespace std;

struct Node {
    Node *next = NULL;
    char value;
};


class list {
 public:
     Node *head;
     int size;

     list() {
         head = nullptr;
         size = 0;
     }

     ~list() {
         clear();
     }

     void add(char v) {
         Node *el = new Node;
         el->value = v;
         el->next = head;
         head = el;
         size++;
     }

     bool empty() {
         return size == 0;
     }

     void pop() {
         Node *temp = head->next;
         delete (head);
         head = temp;
         size--;
     }

     char top() {
         if (head != nullptr) {
             return head->value;
         } else {
             return '0';
         }
     }

     char get() {
         char x = top();
         pop();
         return x;
     }

     void clear() {
         for (int j = 0; j < size; j++) {
             pop();
         }
     }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    string inp;
    while (cin >> inp) {
        list s;
        bool b = true;
        for (char ch : inp) {
            if (ch == '(' || ch == '[') {
                s.add(ch);
            } else {
                if ((ch == ')' && s.top() == '(') || (ch == ']' && s.top() == '[')) {
                    s.pop();
                } else {
                    b = false;
                    break;
                }
            }
        }
        if (b && s.empty()) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
