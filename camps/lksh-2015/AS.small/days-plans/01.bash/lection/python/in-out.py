import sys

f = open('a.in')
ouf = open('a.out', 'w')
a = sys.stdin.readline()
b = sys.stdin.readlines()
c = f.readline()
d = f.readlines()
ouf.write(str(10) + "\n")
ouf.write(str(20))
print(b)
print(c)
print(d)

ouf.close()
f.close()
