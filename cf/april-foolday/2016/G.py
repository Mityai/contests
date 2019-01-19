F, I, T = list(map(int, input().split()))
c = [0] * I
for i in range(F):
    s = input()
    for j in range(I):
        c[j] += s[j] == 'Y'
a = 0
for i in range(I):
    a += c[i] >= T
print(a)
#kitten
