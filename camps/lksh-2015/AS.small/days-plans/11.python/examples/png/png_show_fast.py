import time

def time_stamp(s):
  sys.stderr.write("%.2f: %s\n" % (time.clock(), s));

from tkinter import *
import png

time_stamp("create objects..")

reader = png.Reader(filename="image.png")
width, height, pixels, properties = reader.asRGBA();
pixels = list(pixels)
root = Tk()
image = PhotoImage(width=width, height=height)

time_stamp("make string")

ss = []
y = 0
for row in pixels:
    ss.append('{')
    for x in range(width):
        r, g, b = [row[4 * x + i] for i in range(3)]
        ss.append("#%02x%02x%02x" % (r, g, b))
    ss.append('}')
    y += 1

time_stamp("draw pixels.. (%d,%d)" % (len(pixels), width))

image.put(" ".join(ss), (0, 0))

time_stamp("draw window..")

label = Label(root, image=image)
label.grid()
root.mainloop()
