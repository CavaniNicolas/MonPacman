# # -*- coding: utf-8 -*-

from PIL import Image as pil

def ima2fic():
	variableImage = pil.open("plateauAscanner.png")

	pil.Image.show(variableImage)

	taille = 22
	t=[]
	for i in range(taille):
		s="{"
		y=i*40
		for j in range(taille):
			x=j*40
			r,g,b=variableImage.getpixel((x,y))
			# print("r={}, g={}, b={}".format(r,g,b))
			s+=str(int(r==163))+","
		if i==taille-1:
			s=s[:-1]+"}"
		else:
			s=s[:-1]+"},\n"

		t.append(s)
	# print(t)	
	str2fic(t)	
	variableImage.close()


def str2fic(t):
	file = open("plateautest.c","w")
	for k in range(len(t)):
		# print(t[k])
		file.write(t[k])
	file.close()

ima2fic()


# from tkinter import *
# from PIL import Image, ImageTk
# w=880
# h=880
# x=200
# y=50
# root=Tk()
# root.title("Plateau Pacman")

# # root.geometry('880x880')
# # root.geometry('%dx%d' % (w, h))
# root.geometry('%dx%d+%d+%d' % (w, h, x, y))

# load = Image.open("plateauAscanner.png")

# photo = ImageTk.PhotoImage(load)

# label_img = Label(root, image = photo)
# label_img.place(x=0,y=0)
# root.mainloop()