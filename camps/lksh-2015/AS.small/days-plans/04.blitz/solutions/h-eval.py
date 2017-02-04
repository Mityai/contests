import sys
def f(s):
  i = s.find('(')
  if i == -1:
    return eval(s)
  b = 1
  j = i + 1
  while b != 0:
    if s[j] == '(':
      b += 1
    elif s[j] == ')':
      b -= 1
    j += 1
  return f(s[:i] + str(f(s[i+1:j-1])) + s[j:])

print(f(sys.stdin.readline().strip().replace("/", "//")))
