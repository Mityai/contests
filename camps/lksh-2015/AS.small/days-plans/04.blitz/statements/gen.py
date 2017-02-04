f = open('pairs.txt').readlines()
id = 0
for i in range(0, len(f), 2):
  id += 1
  id1, name1 = f[i+0].strip().split()
  id2, name2 = f[i+1].strip().split()
  print('sed -e "s/<id>/%d/g;s/<id1>/%s/g;s/<name1>/%s/g;s/<id2>/%s/g;s/<name2>/%s/g;" < day04.tex_ > day04%c.tex' % (id, id1, name1, id2, name2, chr(id + 96)))
