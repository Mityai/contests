from tkinter import *
from time import *

buttonTitle = "Click me"

def t():
  return strftime("%Y-%m-%d %H:%M:%S", gmtime())

def append(msg):
  global myTextArea
  myTextArea.insert(END, msg)

def butEnter(e): 
  global but
  append(t() + "  Enter\n");
  but["text"] = "=)"
def butLeave(e): 
  global but, buttonTitle
  append(t() + "  Leave\n");
  but["text"] = buttonTitle
def butClick(e): 
  append(t() + "  Clicked: " + str(e) + "\n")
  #sys.exit(0)

def handleKey(e): append(t() + "  Key: " + str(e) + "\n")

# create the root window
root = Tk()

# modify the window
root.title("Create a window")
root.geometry("500x500")
root.bind("<Key>", handleKey); 

but = Button(root,
  text=buttonTitle, 
  width=30,height=4,
  bg="white",fg="red"
)

but.bind("<Enter>", butEnter); 
but.bind("<Leave>", butLeave); 
but.bind("<Button-1>", butClick); 
but.pack()

myTextArea = Text(root,
  width=60,
  height=20,
  font="Courier-New 10",
)
          
myTextArea.pack()

w = Canvas(root, width=200, height=100)
w.pack()
w.create_line(0, 0, 200, 100)
w.create_line(0, 100, 200, 0, fill="red", dash=(4, 4))
w.create_rectangle(50, 25, 150, 75, fill="#8888ff", outline="#0000ff")
w.create_oval(10, 10, 30, 30, fill="green", outline="#00aa00")
w.create_text(100, 50, text="Some text", justify=CENTER, font="Courier 14 bold")

# Start the window's event-loop
root.mainloop()
