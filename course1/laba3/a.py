n = int(input())
a = list(map(int, input().split()))
for i in range(1, n+1):
    if 2*i - 1 < n:
        if not a[i-1] <= a[2*i-1]:
            print("NO")
            exit(0)
    if 2*i < n:
        if not a[i-1] <= a[2*i]:
            print("NO")
            exit(0)
print("YES")