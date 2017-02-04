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

Box = namedtuple('box', 'ix iy')
xcnt = len(x) - 1
ycnt = len(y) - 1
boxes = {}
for ix in range(xcnt):
	for iy in range(ycnt):
		boxes[Box(ix, iy)] = (top(ix, iy), bottom(ix, iy), left(ix, iy), right(ix, iy))

adj = {}
plot = {}
for a in boxes:
	min_diff = []
	for b in boxes:
		bi = (b.ix, b.iy)
		top = (get_diff(boxes[a][0], boxes[b][1]), bi)
		bottom = (get_diff(boxes[a][1], boxes[b][0]), bi)
		left = (get_diff(boxes[a][2], boxes[b][3]), bi)
		right = (get_diff(boxes[a][3], boxes[b][2]), bi)
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

time_stamp("choose corner")

best = ((10**9, 10**9), [])
for ix in range(xcnt):
	for iy in range(ycnt):
		ans = [[0] * ycnt for i in range(xcnt)]
		was = [[0] * ycnt for i in range(xcnt)]
		corner = (ix, iy)
		for cx in range(xcnt):
			for cy in range(ycnt):
				if (cx == 0) and (cy == 0):
					r = (ix, iy)
				elif cx == 0:
					r = adj[ans[cx][cy - 1] + (1,)][1]
				elif cy == 0:
					r = adj[ans[cx - 1][cy] + (3,)][1]
				else:
					a = adj[ans[cx][cy - 1] + (1,)][1]
					b = adj[ans[cx - 1][cy] + (3,)][1]
					sa = get_diff(boxes[ans[cx][cy - 1]][1], boxes[a][0]) + get_diff(boxes[ans[cx - 1][cy]][3], boxes[a][2])
					sb = get_diff(boxes[ans[cx][cy - 1]][1], boxes[b][0]) + get_diff(boxes[ans[cx - 1][cy]][3], boxes[b][2])
					if sa < sb:
						r = a
					else:
						r = b
				ans[cx][cy] = r
		sum_diff = 0
		for cx in range(xcnt):
			for cy in range(ycnt):
				was[ans[cx][cy][0]][ans[cx][cy][1]] = 1
				if cx + 1 < xcnt: sum_diff += get_diff(boxes[ans[cx][cy]][3], boxes[ans[cx + 1][cy]][2])
				if cy + 1 < ycnt: sum_diff += get_diff(boxes[ans[cx][cy]][1], boxes[ans[cx][cy + 1]][0])
		sum_diff = (-sum(map(lambda x : sum(x), was)), sum_diff)
		if sum_diff < best[0]:
			best = (sum_diff, ans)

for ix in range(xcnt):
	print(best[1][ix])
for ix in range(xcnt):
	for iy in range(ycnt):
		put_plot(plot[best[1][ix][iy]], ix, iy)

time_stamp("save")

img.save("_" + sys.argv[1])

time_stamp("draw")

root = Tk()
img = ImageTk.PhotoImage(img)
label = Label(root, image=img)
label.grid()
root.mainloop()
