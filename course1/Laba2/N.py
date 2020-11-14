def make16():
    lines = [list() for i in range(10)]
    lines[0] = [(i, i+1) for i in range(0, n-1, 2)]
    for i in range(16):
        if i % 4 == 0:
            lines[1].append((i, i+3))
        if i % 4 == 1:
            lines[1].append((i, i+1))
    lines[2] = [(i, i+1) for i in range(0, n-1, 2)]
    for i in range(4):
        lines[3].append((i, 7 - i))
        lines[3].append((i + 8, 15-i))
    for i in range(16):
        if i % 4 < 2:
            lines[4].append((i, i+2))
    lines[5] = [(i, i+1) for i in range(0, n-1, 2)]
    for i in range(8):
        lines[6].append((i, 15-i))
    for i in range(16):
        if i % 8 < 4:
            lines[7].append((i, i+4))
    for i in range(16):
        if i % 4 < 2:
            lines[8].append((i, i+2))
    lines[9] = [(i, i+1) for i in range(0, n-1, 2)]
    return lines


n = int(input())
cou = 0
x = make16()
newLines = [[] for i in range(10)]
for l in range(len(x)):
    for i, j in x[l]:
        if i < n and j < n:
            cou += 1
            newLines[l].append(i)
            newLines[l].append(j)
print(*(n, cou, 10))
for i in newLines:
    print(len(i)//2, end=" ")
    for j in i:
        print(j+1, end=" ")
    print()