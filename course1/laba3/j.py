class Dsu:
    def __init__(self, n, ranked):
        self.parents = [i for i in range(n)]
        self.ranked = ranked
        self.ranks = [0 for i in range(n)]
        self.messages = [0 for i in range(n)]
        self.read = [0 for i in range(n)]

    def find(self, v):
        if v == self.parents[v]:
            return v
        else:
            head = self.find(self.parents[v])
            if head != self.parents[v]:
                self.messages[v] += self.messages[self.parents[v]]
            self.parents[v] = head
            return self.parents[v]

    def check(self, v):
        self.find(v)
        value = self.messages[v] - self.read[v]
        if self.parents[v] != v:
            value += self.messages[self.parents[v]]
        self.read[v] += value
        return value

    def send(self, v):
        a = self.find(v)
        self.messages[a] += 1

    def union(self, a, b):
        a = self.find(a)
        b = self.find(b)
        if a != b:
            if self.ranked:
                if self.ranks[a] < self.ranks[b]:
                    a, b = b, a
                self.parents[b] = a
                self.messages[b] -= self.messages[a]
                if self.ranks[a] == self.ranks[b]:
                    self.ranks[a] += 1
            else:
                self.parents[a] = b
            return True
        return False


def getX(i):
    # return i
    return (i+zerg)%n


n, m = map(int, input().split())
dsu = Dsu(n, True)
p = int(1e6+3)
zerg = 0
for i in range(m):
    line = input().split()
    if line[0] == '1':
        i = int(line[1])
        dsu.send(getX(i))
        zerg = (30 * zerg + 239) % p
    elif line[0] == '2':
        i = int(line[1])
        j = int(line[2])
        if dsu.union(getX(i), getX(j)):
            zerg = (13*zerg+11) % p
    else:
        i = int(line[1])
        read = dsu.check(getX(i))
        print(read)
        zerg = (100500*zerg+read) % p
