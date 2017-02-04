from tkinter import *
from PIL import Image, ImageDraw, ImageTk
import sys, time
from collections import namedtuple

def time_stamp(s):
  sys.stderr.write("%.2f: %s\n" % (time.clock(), s));

time_stamp("load")

img = Image.open(sys.argv[1])
draw = ImageDraw.Draw(img)
w, h = img.size
p = img.load()

time_stamp("precalc")

def get_row(x, y, l):
	global p
	return [p[x + i, y] for i in range(l)]
def get_col(x, y, l):
	global p
	return [p[x, y + i] for i in range(l)]
def get_diff(a, b):
	diff = 0
	for i in range(min(len(a), len(b))):
		for k in range(3):
			diff += abs(a[i][k] - b[i][k])
	return diff
def get_plot(ix, iy):
	global p, x, y
	sx, sy, dx, dy = x[ix], y[iy], x[ix + 1] - x[ix], y[iy + 1] - y[iy]
	return [[p[sx + cx, sy + cy] for cy in range(dy)] for cx in range(dx)]
def put_plot(a, ix, iy):
	global p, x, y
	sx, sy, dx, dy = x[ix], y[iy], x[ix + 1] - x[ix], y[iy + 1] - y[iy]
	for cx in range(dx):
		for cy in range(dy):
			p[sx + cx, sy + cy] = a[cx][cy]

ydiff = [((get_diff(get_row(0, y, w), get_row(0, y + 1, w))), y) for y in range(h - 1)]
xdiff = [((get_diff(get_col(x, 0, h), get_col(x + 1, 0, h))), x) for x in range(w - 1)]

def get_cuts(a):
	a.sort()
	i = 0
	while (i + 1 < len(a)) and (a[i + 1][0] / a[i][0] < 1.5):
		i += 1
	return sorted(map(lambda x : x + 1, list(zip(*a))[1][i + 1:]))

x = [0] + get_cuts(xdiff) + [w]
y = [0] + get_cuts(ydiff) + [h]

time_stamp("solve")

def top(ix, iy):
	global x, y
	return get_row(x[ix], y[iy], x[ix + 1] - x[ix])
def bottom(ix, iy):
	global x, y
	return get_row(x[ix], y[iy + 1] - 1, x[ix + 1] - x[ix])
def left(ix, iy):
	global x, y
	return get_col(x[ix], y[iy], y[iy + 1] - y[iy])
def right(ix, iy):
	global x, y
	return get_col(x[ix + 1] - 1, y[iy], y[iy + 1] - y[iy])

print(x)
print(y)

Box = namedtuple('box', 'ix iy top bottom left right')

xcnt = len(x) - 1
ycnt = len(y) - 1
boxes = [Box(ix, iy, top(ix, iy), bottom(ix, iy), left(ix, iy), right(ix, iy)) for ix in range(xcnt) for iy in range(ycnt)]
adj = {}
plot = {}
for a in boxes:
	min_diff = []
	for b in boxes:
		bi = (b.ix, b.iy)
		top = (get_diff(a.top, b.bottom), bi)
		bottom = (get_diff(a.bottom, b.top), bi)
		left = (get_diff(a.left, b.right), bi)
		right = (get_diff(a.right, b.left), bi)
		v = [top, bottom, left, right]
		for k in range(len(v)):
			print("(%d, %d : %d) try go to %d, %d [diff = %d]" % ((a.ix, a.iy, k) + v[k][1] + (v[k][0],)))
		if min_diff == []:
			min_diff = v
		else:
			for k in range(len(v)):
				if v[k][0] < min_diff[k][0]:
					min_diff[k] = v[k]	
	for k in range(len(min_diff)):
		adj[(a.ix, a.iy, k)] = min_diff[k]
		print("(%d, %d : %d) --> %d, %d [diff = %d]" % ((a.ix, a.iy, k) + min_diff[k][1] + (min_diff[k][0],)))
	plot[(a.ix, a.iy)] = get_plot(a.ix, a.iy)

is_top = [(adj[a.ix, a.iy, 0], (a.ix, a.iy)) for a in boxes]
is_top.sort()
is_top.reverse()
top = list(zip(*is_top[:xcnt]))[1]

for tmp in is_top[:xcnt]:
	print("top", tmp)
time_stamp("plot")

#for ix in range(xcnt):
#	put_plot(plot[top[ix]], ix, 0)

is_corner = [(adj[ix, iy, 2], (ix, iy)) for (ix, iy) in top]
for tmp in is_corner:
	print("corner", tmp)
corner = sorted(is_corner)[-1][1]
print(corner)

for ix in range(xcnt):
	cur = corner
	for iy in range(ycnt):
		put_plot(plot[cur], ix, iy)
		cur = adj[cur + (1,)][1]
	corner = adj[corner + (3,)][1]		

time_stamp("save")

img.save("_" + sys.argv[1])

time_stamp("draw")

root = Tk()
img = ImageTk.PhotoImage(img)
label = Label(root, image=img)
label.grid()
root.mainloop()
