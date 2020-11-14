import sys


def init(v):
    global parents, maxi, mini, count
    parents[v] = v
    maxi[v] = v
    mini[v] = v
    count[v] = 1
    return v


def find(v):
    global parents
    if v == parents[v]:
        return v
    else:
        parents[v] = find(parents[v])
        return parents[v]


def union(a, b):
    global parents, ranks, maxi, mini, count
    a = find(a)
    b = find(b)
    if a != b:
        if ranks[a] < ranks[b]:
            a, b = b, a
        parents[b] = a
        maxi[a] = max(maxi[a], maxi[b])
        mini[a] = min(mini[a], mini[b])
        count[a] += count[b]
        if ranks[a] == ranks[b]:
            ranks[a] += 1


n = int(input())
parents = [i for i in range(n)]
ranks = [0 for i in range(n)]
maxi = [-1000000000 for i in range(n)]
mini = [1000000000 for i in range(n)]
count = [1 for i in range(n)]
for i in range(n):
    init(i)
cou = 0
for command in sys.stdin:
    command = command.split()
    if command[0] == 'union':
        union(int(command[1]) - 1, int(command[2]) - 1)
    else:
        cou += 1
        el = find(int(command[1]) - 1)
        print(mini[el] + 1, maxi[el] + 1, count[el])
