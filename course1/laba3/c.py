import sys


class PriorityQueue:
    def __init__(self):
        self.index = {}
        self.heap = list()
        self.last = 0
        self.count = 0

    def siftUp(self, i):
        while self.heap[i][0] < self.heap[(i-1)//2][0] and i != 0:
            self.heap[i], self.heap[(i-1)//2] = self.heap[(i-1)//2], self.heap[i]
            self.index[self.heap[i][1]] = i
            self.index[self.heap[(i-1)//2][1]] = (i-1)//2
            i = (i-1)//2

    def siftDown(self, i):
        while 2 * i + 1 < self.last:
            left = 2 * i + 1
            right = 2 * i + 2
            j = left
            if right < self.last and self.heap[right][0] < self.heap[left][0]:
                j = right
            if self.heap[i][0] <= self.heap[j][0]:
                break
            self.heap[i], self.heap[j] = self.heap[j], self.heap[i]
            self.index[self.heap[i][1]] = i
            self.index[self.heap[j][1]] = j
            i = j

    def push(self, item):
        if self.last >= len(self.heap):
            self.heap.append((item, self.count))
        else:
            self.heap[self.last] = (item, self.count)
        self.index[self.count] = self.last
        self.count += 1
        self.siftUp(self.last)
        self.last += 1

    def pop(self):
        self.count += 1
        if self.last == 0:
            return "*", ""
        self.heap[0], self.heap[self.last-1] = self.heap[self.last-1], self.heap[0]
        self.index[self.heap[0][1]] = 0
        self.index[self.heap[self.last-1][1]] = -1
        self.last -= 1
        self.siftDown(0)
        return self.heap[self.last][0], self.heap[self.last][1] + 1

    def decreaseKey(self, item, value):
        self.count += 1
        ind = self.index[item]
        if ind == -1:
            return
        if value > self.heap[ind][0]:
            self.heap[ind] = (ind, self.heap[ind][1])
            self.siftDown(ind)
        else:
            self.heap[ind] = (value, self.heap[ind][1])
            self.siftUp(ind)


heap = PriorityQueue()
for command in sys.stdin:
    command = command.strip().split()
    if command[0] == "push":
        heap.push(int(command[1]))
    elif command[0] == "extract-min":
        print(*heap.pop())
    else:
        heap.decreaseKey(int(command[1])-1, int(command[2]))
