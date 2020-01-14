# # -*- coding: utf-8 -*-

from PIL import Image as pil

def ima2fic():
	variableImage = pil.open("plateauHitbox.png")

	pil.Image.show(variableImage)

	tailleHitbox = 22
	coteCube = 880/tailleHitbox
	mur = 1
	chemin = 0
	portail = 2

	t=[]
	for i in range(tailleHitbox):
		s="{"
		y=i*coteCube
		for j in range(tailleHitbox):
			x=j*coteCube
			r,g,b=variableImage.getpixel((x,y))
			# print("r={}, g={}, b={}".format(r,g,b))
			#s+=str(int(r==163))+","
			if r==163:
				s+=str(mur)
			elif r==255:
				s+=str(chemin)
			elif r==216:
				s+=str(portail)
			s+=","
		if i==tailleHitbox-1:
			s=s[:-1]+"}"
		else:
			s=s[:-1]+"},\n"

		t.append(s)
	# print(t)	
	str2fic(t)	
	variableImage.close()


def str2fic(t):
	file = open("plateauHitbox.c","w")
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