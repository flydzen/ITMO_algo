#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

#include <cstdio>

/** Interface */

inline int readChar();

template<class T = int>
inline T readInt();

template<class T>
inline void writeInt(T x, char end = 0);

inline void writeChar(int x);

inline void writeWord(const char *s);

/** Read */

static const int buf_size = 4096;

inline int getChar() {
    static char buf[buf_size];
    static int len = 0, pos = 0;
    if (pos == len)
        pos = 0, len = fread(buf, 1, buf_size, stdin);
    if (pos == len)
        return -1;
    return buf[pos++];
}

inline int readChar() {
    int c = getChar();
    while (c <= 32)
        c = getChar();
    return c;
}

template<class T>
inline T readInt() {
    int s = 1, c = readChar();
    T x = 0;
    if (c == '-')
        s = -1, c = getChar();
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = getChar();
    return s == 1 ? x : -x;
}

/** Write */

static int write_pos = 0;
static char write_buf[buf_size];

inline void writeChar(int x) {
    if (write_pos == buf_size)
        fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
    write_buf[write_pos++] = (char)x;
}

template<class T>
inline void writeInt(T x, char end) {
    if (x < 0)
        writeChar('-'), x = -x;

    char s[24];
    int n = 0;
    while (x || !n)
        s[n++] = '0' + x % 10, x /= 10;
    while (n--)
        writeChar(s[n]);
    if (end)
        writeChar(end);
}

inline void writeWord(const char *s) {
    while (*s)
        writeChar(*s++);
}

struct Flusher {
    ~Flusher() {
        if (write_pos)
            fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
    }
} flusher;


using namespace std;


class Dsu {
 private:
     vector<int> parents;
     bool ranked;
     vector<int> ranks;

 public:
     explicit Dsu(int n, bool rnkd = true) {
         n++;
         parents = vector<int>(n);
         ranked = rnkd;
         ranks = vector<int>(n);
         for (int i = 0; i < n; i++) {
             init(i);
         }
     }

     void init(int v) {
         parents[v] = v;
         ranks[v] = 0;
     }

     int find(int v) {
         if (v == parents[v]) {
             return v;
         } else {
             parents[v] = find(parents[v]);
             return parents[v];
         }
     }

     void onion(int a, int b) {
         a = find(a);
         b = find(b);
         if (a != b) {
             if (ranked) {
                 if (ranks[a] < ranks[b]) {
                     swap(a, b);
                 }
                 parents[b] = a;
                 if (ranks[a] == ranks[b]) {
                     ranks[a] += 1;
                 }
             } else {
                 parents[a] = b;
             }
         }
     }
};

struct edge {
    int from;
    int to;
    int w;

    edge(int from, int to, int x1, int y1, int x2, int y2) {
        this->from = from;
        this->to = to;
        this->w = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    }
};

bool comp(edge &e1, edge &e2) {
    return e1.w < e2.w;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n = readInt();
    vector<pair<int, int>> g;
    vector<edge> e;

    for (int i = 0; i < n; i++) {
        int a = readInt(), b = readInt();
        for (int j = 0; j < i; j++) {
            e.emplace_back(j, i, g[j].first, g[j].second, a, b);
        }
        g.emplace_back(a, b);
    }
    sort(e.begin(), e.end(), comp);
    int cou = 0;
    double result = 0;
    Dsu dsu(n);
    for (size_t i = 0; i < e.size() && cou < n - 1; i++) {
        edge &uv = e[i];
        if (dsu.find(uv.from) != dsu.find(uv.to)) {
            dsu.onion(uv.from, uv.to);
            cou++;
            result += sqrt(uv.w);
        }
    }
    cout << setprecision(20) << result;
    return 0;
}
