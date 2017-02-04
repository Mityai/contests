from tkinter import *
from PIL import Image, ImageDraw, ImageTk

root = Tk()
img = Image.open('image.png')

p = img.load()
width, height = img.size
for y in range(height // 4, 3 * height // 4):
	for x in range(width // 4, 3 * width // 4):
		p[x, y] = (255, 0, 0, 255)

img = ImageTk.PhotoImage(img)
label = Label(root, image=img)
label.grid()
root.mainloop()
