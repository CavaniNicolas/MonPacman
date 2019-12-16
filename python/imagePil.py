# -*- coding: utf-8 -*-
from tkinter import *
from PIL import Image, ImageTk
w=880
h=880
x=200
y=50
root=Tk()
root.title("Plateau Pacman")

# root.geometry('880x880')
# root.geometry('%dx%d' % (w, h))
root.geometry('%dx%d+%d+%d' % (w, h, x, y))

load = Image.open("plateauAscanner.png")

photo = ImageTk.PhotoImage(load)

label_img = Label(root, image = photo)
label_img.place(x=0,y=0)
root.mainloop()