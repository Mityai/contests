from tkinter import *
from PIL import Image, ImageDraw, ImageTk

root = Tk()
img = Image.open('image.png')
draw = ImageDraw.Draw(img)
w, h = img.size
draw.rectangle([w // 4, h // 4, 3 * w // 4, 3 * h // 4], (0, 128, 0))
img.save('image2.png')

img = ImageTk.PhotoImage(img)
label = Label(root, image=img)
label.grid()
root.mainloop()
