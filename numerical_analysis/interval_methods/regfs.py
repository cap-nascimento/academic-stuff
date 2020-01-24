from __future__ import division
import numpy as np
import matplotlib.pyplot as plt
maxitr = 100

convergence = []

def function(x):
	#return x*x*x - 9*x + 3
	#return np.sin(x)
	return np.sqrt(x) - 2

def regulaFalsi(a, b, eps1, eps2):
	#Se i intervalo for pequeno o suficiente e obedece ao critério de Bolzano, a raiz
	#está no intervalo e pode retornar qualquer valor dentro do intervalo
	if(((b-a) < eps1 and function(a)*function(b) < 0)):
		print("A raiz se encontra no intervalo: "+ str((a+b)/2))
		return True
	#sendo a imagem de a um valor muito proximo a precisão requerida, retorna-se a
	elif(abs(function(a)) < eps2 ):
		print("O limite inferior é a raiz: "+ str(a))
		return True
	#sendo a imagem de b um valor muito proximo a precisao requerida, retorna-se b
	elif(abs(function(b)) < eps2):
		print("O limite superior é a raiz: "+ str(b))
		return True

	#inicializa contagem de iteracoes
	for k in range(1, maxitr+1):
		#estabelece ponto (a, f(a))
		M = function(a)
		#realiza media ponderada para encontrar o ponto que toca o eixo x
		x = (a*function(b) - b*function(a))/(function(b) - function(a))
		convergence.append(x)
		#print(M)
		#print(a)
		#print(b)
		#print(x)

		if(abs(function(x)) < eps2):
			print("Raiz encontrada em " + str(k) + " iterações: "+str(x))
			return True
		else:
			if(M*function(x) > 0):
				a = x
			else:
				b = x

		if(((b-a) < eps1 and function(a)*function(b) < 0)):
			print("Raiz encontrada em " + str(k) + " iterações: "+str((a+b)/2))
			return True

	if(k == 100):
		print("Raiz não encontrada no intervalo dado.")
		return False


a = input("Limite inferior: ")
b = input("Limite superior: ")
eps1 = input("Precisão 1: ")
eps2 = input("Precisão 2: ")

a = float(a)
b = float(b)
eps1 = float(eps1)
eps2 = float(eps2)

if(regulaFalsi(a, b, eps1, eps2)):
	#print(convergence)
	plt.figure()
	plt.plot(convergence)
	#plt.ion()
	plt.show()
else:
	plt.figure()
	plt.plot(convergence)
	#plt.ion()
	plt.show()

