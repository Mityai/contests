#!/usr/bin/python
#Python version: 2.7
TASKNAME = 'segments'
TESTSTR = '%02d'
SMALLTESTS = 7
TOFILES = False

import random, sys
random.seed (hash (TASKNAME))
try:
	import psyco
	psyco.full ()
	sys.stderr.write ('(using psyco)\n')
except:
	sys.stderr.write ('(psyco not available)\n')

MinN, MaxN = 1, 100000
MinC, MaxC = 1, 10 ** 9

test = SMALLTESTS
shuffle = False

def out (a):
	global test, shuffle
	test += 1
	sys.stderr.write ('Test ' + TESTSTR % test + '\n')
	n = len (a)
	assert MinN <= n <= MaxN
	for i in range (n):
		assert MinC <= a[i][0] < a[i][1] <= MaxC
	if shuffle:
		random.shuffle (a)
	if TOFILES:
		f = open (TESTSTR % test, 'wt')
	else:
		f = sys.stdout
	f.write ('\n%d\n' % n)
	for i in range (n):
		f.write ('%d %d\n' % (a[i][0], a[i][1]))
	if TOFILES:
		f.close ()

def genrandom (n, lo, hi):
        assert lo < hi
	a = []
	for i in range (n):
		while True:
			x = random.randint (lo, hi - 1)
			y = random.randint (lo + 1, hi)
			if x < y:
				break
		a.append ([x, y])
	return a

# Small tests

# Medium tests

# Large tests
out (genrandom (MaxN, MinC, MaxC))
shuffle = True

a = []
for i in range (MaxN):
	a.append ([i + 1, i + MaxN])
out (a)

a = []
for i in range (MaxN):
	a.append ([i * 2 + 1, i * 2 + 2])
out (a)
