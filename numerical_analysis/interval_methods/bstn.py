from __future__ import division
import numpy as np
import matplotlib.pyplot as plt

convergence = []

#definicao de funcoes
def function(x):
	#return x**2 - 2
	#return x**3 - 9*x + 3
	return x**5 + 22*x**3 - 8*x**2 - 18*x

#metodo de bisseccao
def bisection(a, b, eps):

	#x-barra inicial
	xapr = (a+b)/2
	#Se ja estiver no intervalo com a precisao desejada
	if((abs(b-a) < eps) and (function(a)*function(b)) < 0):
		print("Raiz encontrada em 0 iteracoes! x = "+str(xapr)+".")
		return True
	#caso contrario estabelece os limites inferiores e superiores
	else:
		for k in range(100):

			#calcula o valor do limite inferior
			pr = function(a)
			xapr = (a+b)/2

			#adiciona elementos para plotagem do grafico de convergencia para a raiz 
			convergence.append(xapr)
			#Se o produto das imagens dos limites for positivo, ou a raiz nao esta
			#no intervalo ou ele tem mais de uma raiz e deve diminuir para convergir
			if(pr*function(xapr) > 0):
				a = xapr
			#Se for negativo, a raiz esta no intervalo e deve diminuir seu limite
			#superior
			else:
				b = xapr

			#Se o intervalo chegou a um tamanho proximo do epsilon a raiz esta
			#aproximada o suficiente
			if(abs(b-a) < eps):
				xapr = (a+b)/2
				#inclui a ultima aproximacao de x necessaria
				convergence.append(xapr)
				print("Raiz encontrada em "+str(k+1)+" iteracoes! x = "+str(xapr)+".")
				return True

		if(k == 99):
			#Ou o numero de iteracoes nao foi o suficiente para chegar na aproximacao
			#desejada ou a raiz nao esta no intervalo
			if(function(a)*function(b) > 0):
				print("Raiz nao encontrada no intervalo dado!")
			else:
				print("N de iteracoes insuficiente!")
			
			return False

a = input()
b = input()
eps = input()

a = float(a)
b = float(b)
eps = float(eps)

it = np.log(a+b) - np.log(eps)
itI = int(np.floor(it))
print("N de iteracoes prevista: maior ou igual a "+str(itI)+".")

#if(bisection(a, b, eps)):
bisection(a, b, eps)
plt.plot(convergence)
plt.show()
