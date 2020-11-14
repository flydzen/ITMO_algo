import sys


def init(v):
    global parents
    parents[v] = v


def find(v):
    global parents
    if v == parents[v]:
        return v
    else:
        parents[v] = find(parents[v])
        return parents[v]


def union(a, b):
    global parents, ranks
    a = find(a)
    b = find(b)
    if a != b:
        if ranks[a] < ranks[b]:
            a, b = b, a
        parents[b] = a
        if ranks[a] == ranks[b]:
            ranks[a] += 1


n, m, k = map(int, input().split())
parents = [i for i in range(n)]
ranks = [0 for i in range(n)]
for i in range(n):
    init(i)
for i in range(m):
    input()
commands = list()
for i in range(k):
    commands.append(input().split())
answer = list()
for i in commands[::-1]:
    if i[0] == "ask":
        answer.append("YES" if find(int(i[1])-1) == find(int(i[2])-1) else "NO")
    else:
        union(int(i[1])-1, int(i[2])-1)
for i in answer[::-1]:
    print(i)