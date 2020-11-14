#include <iostream>

using namespace std;


template<typename T>
class vector {
private:
    T *_mass;
    int _massSize;

    void resize(T *newMass) {
        for (int i = begin; i < end; i++) {
            newMass[i] = _mass[i];
        }
        delete[] _mass;
        _mass = newMass;
    }

    void _resizeUp() {
        T *newMass = new T[_massSize * 2];
        resize(newMass);
        _massSize *= 2;
    }

    void _resizeDown() {
        T *newMass = new T[_massSize / 2];
        resize(newMass);
        _massSize /= 2;
    }

public:
    int begin, end;

    vector() {
        _massSize = 2;
        _mass = new T[_massSize];
        begin = 0;
        end = 0;
    }

    void push(T value) {
        if (end == _massSize) {
            _resizeUp();
        }
        _mass[end] = value;
        end++;
    }

    void insert(int index, T value) {
        if (end == _massSize) {
            _resizeUp();
        }
        for (int i = end; i > index; i--) {
            _mass[i] = _mass[i - 1];
        }
        _mass[index] = value;
        ++end;
    }

    void pop_back() {
        end--;
        if (end * 2 < size()) {
            _resizeDown();
        }
    }

    T get(int index) {
        return _mass[index];
    }

    T get() {
        return _mass[end - 1];
    }

    int size() {
        return end - begin;
    }

    void clear() {
        _massSize = 2;
        _mass = new T[_mass];
        end = 0;
    }
};

struct Node {
    Node *next = nullptr;
    int value = 0;
};

class list {
public:
    Node *head;
    Node *tail;

    list() {
        head = nullptr;
        tail = nullptr;
    }

    void add(int v) {
        Node *el = new Node;
        el->value = v;
        el->next = nullptr;
        if (head) {
            head->next = el;
        }
        head = el;
        if (!tail) {
            tail = el;
        }
    }

    void pop_bot() {
        Node *temp = tail->next;
        delete(tail);
        if (tail == head) {
            tail = nullptr;
            head = nullptr;
        } else {
            tail = temp;
        }
    }

    int get_bot(){
        int value = bot();
        pop_bot();
        return value;
    }

    int bot() {
        return tail->value;
    }
};

class quack {
private:
    int reg['z' - 'a' +1];
    list q;
    int labels[2387];

public:
    quack() {
        cout << "started";
    }

    void plus() {
        q.add(q.get_bot() + q.get_bot());
    }

    void minus() {
        q.add(q.get_bot() - q.get_bot());
    }

    void mult() {
        q.add(q.get_bot() * q.get_bot());
    }

    void div() {
        q.add(q.get_bot() / q.get_bot());
    }

    void mod() {
        q.add(q.get_bot() % q.get_bot());
    }

    void putToReg(char r) {
        reg[r-'a'] = q.get_bot();
    }

    void putFromReg(char r) {
        q.add(reg[r-'a']);
    }

    void p() {
        cout << q.get_bot() << endl;
    }

    void p(char r) {
        cout << reg[r - 'a'] << endl;
    }

    void c() {
        cout << (char)(q.get_bot()%256) << endl;
    }

    void c(char r) {
        cout << (char)(reg[r-'a']%256) << endl;
    }

    static int labelToIndex(char* label) {
        int ind = 0;
        while(ind += *label++);
        return ind%2387;
    }

    void addLabel(char *label, int line) {
        labels[labelToIndex(label)] = line;
    }

    int goToLabel(char *label) {
        return labels[labelToIndex(label)];
    }

    int z(char r, char  *label){
        if (reg[r-'a'] == 0) {
            return goToLabel(label);
        } else {
            return -1;
        }
    }

    int e(char r1, char r2, char *label) {
        if(reg[r1-'a'] == reg[r2-'a']) {
            return goToLabel(label);
        } else {
            return -1;
        }
    }

    int g(char r1, char r2, char* label) {
        if(reg[r1-'a'] > reg[r2-'a']) {
            return goToLabel(label);
        } else {
            return -1;
        }
    }

    void put(int num) {
        q.add(num);
    }
};



int main() {
    list q;
    int reg['z' - 'a' + 1];
    vector<int> code;
    quack qk;
    string ch;
    while (cin >> ch) {
        if (isdigit(ch)) {
            code.push(ch);
        }
    }
    for (int i = 0; i < code.size(); i++) {
        string line = code.get(i);
        if (isdigit(line[0])) {
            code.push(line[0]-'0')
        } else {
            char command =
        }
    }


    return 0;
}