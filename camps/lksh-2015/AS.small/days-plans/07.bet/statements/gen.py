id = 0
for s in open('../list.txt').readlines():
  id += 1
  letter = chr(64 + id)
  dirr = s.split("\\")[0]
  name = s.split("\\")[1].split()[0]
  #print(id, letter, name)
  print('sed -e "s/<dir>/%s/g;s/<id>/%d/g;s/<id1>/%s/g;s/<name1>/%s/g;" < day07.tex_ > day07%c.tex' % (dirr, id, letter, name, chr(96 + id)))
