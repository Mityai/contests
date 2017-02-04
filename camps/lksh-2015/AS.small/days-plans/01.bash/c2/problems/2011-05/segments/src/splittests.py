#!/usr/bin/python
#Python version: 2.7
import os
s = os.getcwd ()
t = s.split (os.sep)
TASKNAME = t[-2]
TESTSTR = '%02d'
fin = open (TASKNAME + '.in', 'rt')
fout = open (TASKNAME + '.out', 'rt')
test = 0
while True:
	s = fin.readline ()
	if s == '' or s == '\n':
		s = fin.readline ()
		if s == '' or s == '\n':
			break
	test += 1
	f = open (TESTSTR % test, 'wt')
	f.write (s)
	n = int (s)
	for i in range (n):
		s = fin.readline ()
		f.write (s)
	f.close ()
	f = open ((TESTSTR + '.a') % test, 'wt')
	s = fout.readline ()
	f.write (s)
	f.close ()
