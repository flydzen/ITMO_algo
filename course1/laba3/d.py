import sys


def init(v):
    global parents, maxi
    parents[v] = v
    maxi[v] = v


def find(v):
    global parents
    if v == parents[v]:
        return v
    else:
        parents[v] = find(parents[v])
        return parents[v]


def union(a, b):
    global parents, ranks, maxi
    a = find(a)
    b = find(b)
    if a != b:
        if ranks[a] < ranks[b]:
            a, b = b, a
        parents[b] = a
        maxi[a] = max(maxi[a], maxi[b])
        if used[a] or used[b]:
            used[a] = True
            used[b] = True
        if ranks[a] == ranks[b]:
            ranks[a] += 1


n = int(input())
if n == 1:
    input()
    print(1)
    exit(0)
parents = [i for i in range(n)]
ranks = [0 for i in range(n)]
maxi = [-1000000000 for i in range(n)]
used = [False for i in range(n)]
for i in range(n):
    init(i)
cars = list(map(lambda x: int(x)-1, input().split()))
for i in cars:
    el = find(i)
    if used[el]:
        nel = maxi[find(0)]
        print(nel + 1, end=" ")
        union(0, nel + 1)
    else:
        print(maxi[el] + 1, end=" ")
        if maxi[el] == n - 1:
            used[el] = True
        else:
            union(i, maxi[el] + 1)
