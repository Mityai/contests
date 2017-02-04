from tkinter import *
from PIL import Image, ImageDraw

width = 400
height = 300
center = height//2
white = (255, 255, 255)
green = (0,128,0)

# PIL create an empty image and draw object to draw on
# memory only, not visible
image1 = Image.new("RGB", (width, height), white)
draw = ImageDraw.Draw(image1)

# do the PIL image/draw (in memory) drawings
draw.line([0, center, width, center], green)

# PIL image can be saved as .png .jpg .gif or .bmp file (among others)
image1.save("my_drawing.jpg")
image1.save("my_drawing.png")
