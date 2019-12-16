#executer avec : python3 imagePIL.py

def main():
	bool=False
	if not bool:
		print("hello world")
		print("héhé")
		bon="bon"
		a=5
		b=3
		blablou="46"
		print(bon,"voici des chiffres :",a," :",b," et du texte :",blablou)
	else:
		print("gnarc")

	Value=0
	while (Value<=0) or (Value>10):
		Value=int(input("Tapez un nbr entre 1 et 10: "))
		if (Value<=0) or (Value>10):
			print("\tHEINNNN erreur")
		elif Value==10:
			print("cest 10, a la limite")
		else:
			print("OK")

def argvariable(nbrargs, *ArgVar):
	print(nbrargs," arguments:")
	for arg in ArgVar:
		print(arg)

def compareType(a,b):
	if a==b:
		print("Egaux")
	else:
		print("pas egaux")

def printLettre(mot):
	LettreNum=1
	for Letter in mot:
		if Letter=="v":
			pass
			print(LettreNum," : \tici etait present un v")
			LettreNum+=1
		if Letter!=" ":
			print(LettreNum," : ",Letter)
			LettreNum+=1
		else:
			print("on entre dans l'hyper espace")
			continue
			print("et on bouffe des gnakis en musique\a")
			print("ces instructions ne sont pas effectuées")
		if LettreNum>12:
			print("mot trop long")
			break


main()
print()
argvariable(4,"le 1", "le 22222", 33333, "dernier")
print()
compareType(0,int("0"))
print()
printLettre("BLA  bo nju  te fvyG")