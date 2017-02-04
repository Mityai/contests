from tkinter import *
root = Tk()
cv = Canvas(root)
cv.create_rectangle(10,10,50,50)
cv.pack()
#root.mainloop()

cv.update()
cv.postscript(file="file_name.ps", colormode='color')

root.mainloop()
