import os
import sys

NUM_ARRAYS = 1
ARRAY_SEP = "\n"
CHAR_SEP = ""
ARRAY_LEN_ADD = 0

__author__ = 'Pavel Mavrin'

tests_dir = sys.argv[1] if len(sys.argv) > 1 else "tests"
print(tests_dir)

fin = open(tests_dir + ".txt", "r")
tests_n = 0
if not os.path.isdir(tests_dir):
    os.mkdir(tests_dir)


cur = 0
s = ""


def get_item():
    global cur
    global s
    res = ""
    if s[cur] == '"':
        cur += 1
        while s[cur] != '"':
            res += s[cur]
            cur += 1
        cur += 1
        return CHAR_SEP.join(list(res))
    else:
        while s[cur] == '-' or s[cur] == '.' or '0' <= s[cur] <= '9':
            res += s[cur]
            cur += 1
        return res


def print_array(fout):
    global cur
    global s
    global NUM_ARRAYS
    while s[cur] == ' ':
        cur += 1
    res = []
    while s[cur] != '}':
        res.append(get_item())
        if s[cur] == ',':
            cur += 1
        while s[cur] == ' ':
            cur += 1
    if NUM_ARRAYS > 0:
        print(len(res) + ARRAY_LEN_ADD, file=fout)
        NUM_ARRAYS -= 1
    print(*res, sep=ARRAY_SEP, file=fout)


def print_args(fout):
    global cur
    global s
    while s[cur] == ' ':
        cur += 1
    while cur < len(s):
        if s[cur] == '{':
            cur += 1
            print_array(fout)
            cur += 1
        else:
            print(get_item(), file=fout)
        cur += 1
        while cur < len(s) and s[cur] == ' ':
            cur += 1


def print_to_file(fout, ss):
    global cur
    global s
    global NUM_ARRAYS
    kk = NUM_ARRAYS
    s = ss
    cur = 0
    s += ','
    print_args(fout)
    NUM_ARRAYS = kk


texout = open("examples.tex", "w")
was = set()
while tests_n < 200:
    s = fin.readline()
    if len(s) == 0:
        break
    p = [x for x in s.strip().split("\t") if len(x) > 0]
    if len(p) == 1:
        p = [x for x in s.strip().split("   ") if len(x) > 0]
    if len(p) >= 2:
        if p[0] in was:
            continue
        was.add(p[0])
        tests_n += 1
        print(tests_n)
        fout = open(tests_dir + "/{:02d}".format(tests_n), "w")
        print_to_file(fout, p[0])
        fout.close()
        # fout = open(tests_dir + "/{:02d}.a".format(tests_n), "w")
        # print_to_file(fout, p[1])
        # fout.close()
        if tests_n <= 10:
            print("\exmp{", file=texout)
            print_to_file(texout, p[0])
            print("}{", file=texout)
            print_to_file(texout, p[1])
            print("}%", file=texout)
texout.close()
