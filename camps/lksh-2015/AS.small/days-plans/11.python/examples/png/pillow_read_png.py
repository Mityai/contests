from tkinter import *
from PIL import Image, ImageDraw, ImageTk

root = Tk()
img = Image.open('image.png')
img.show()

img = ImageTk.PhotoImage(img)
label = Label(root, image=img)
label.grid()
root.mainloop()
