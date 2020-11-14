class Dsu:
    def __init__(self, n, ranked):
        self.parents = [i for i in range(n)]
        self.ranked = ranked
        self.ranks = [0 for i in range(n)]

    def init(self, v):
        self.parents[v] = v
        return v

    def find(self, v):
        if v == self.parents[v]:
            return v
        else:
            self.parents[v] = self.find(self.parents[v])
            return self.parents[v]

    def union(self, a, b):
        a = self.find(a)
        b = self.find(b)
        if a != b:
            if self.ranked:
                if self.ranks[a] < self.ranks[b]:
                    a, b = b, a
                self.parents[b] = a
                if self.ranks[a] == self.ranks[b]:
                    self.ranks[a] += 1
            else:
                self.parents[a] = b


n, q = map(int, input().split())

dsu = Dsu(n, ranked=True)
lines = Dsu(n, ranked=False)
for i in range(n):
    dsu.init(i)
    lines.init(i)
for i in range(q):
    t, x, y = map(lambda z: int(z)-1, input().split())
    if t == 0:
        dsu.union(x, y)
    elif t == 1:
        while x < y:
            x = lines.find(x)
            if x >= y:
                break
            lines.union(x, x+1)
            dsu.union(x, x+1)
    else:
        print("YES" if dsu.find(x) == dsu.find(y) else "NO")
