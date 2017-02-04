left = {}
right = {}

def ask(v):
    if (left.get(v, 0) != 0):
        return left.get(v, 0)
    print(v)
    left[v], right[v] = list(map(int, input().split()))
    if left[v] == 0:
        left[v] -= 1
    if right[v] == 0:
        right[v] -= 1

def ans(ret):
    print(-ret)
    exit(0)

def has(k, H):
    v = 1
    for h in range(H):
        ask(v)
        if k % 2 == 1:
            v = right[v]
        else:
            v = left[v]
        k = k // 2;
    ask(v)
    if (k == 0) and (left[v] != -1):
        return True
    if (k == 1) and (right[v] != -1):
        return True
    return False

def main():
    v = 1
    H = 0
    while True:
        ask(v)
        if right[v] == -1:
            break
        H += 1
        v = right[v]

    maxH = 0
    v = 1
    while True:
        ask(v)
        if left[v] == -1:
            break
        maxH += 1
        v = left[v]

    if H == maxH:
        ans(2 ** (H + 1) - 1)

    lb = 1
    rb = (2 ** maxH) + 1
    while lb + 1 < rb:
        mb = (lb + rb) // 2
        if has(mb - 1, H):
            lb = mb
        else:
            rb = mb

    ans(2 ** (H + 1) - 1 + lb)

main()
