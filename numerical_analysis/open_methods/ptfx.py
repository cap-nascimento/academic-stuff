from __future__ import division
import matplotlib.pyplot as plt
import numpy as np
itr = 100

convergence = []

#declaração de funções
def f(x):
	return x**3 - 9*x + 3

#funções phi para pontos fíxos
def phi(x):
	return (x**3)/9 + 1/3

def fixed_point(x, eps):
	#Se a aproximação de x0 da raiz for suficiente, a raiz e x0
	if(abs(f(x)) < eps):
		print("Raiz encontrada: " + str(x))
		return True

	#Inicia as iterações
	for k in range(itr):
		#Inicia o procedimento recursivo para xk = phi(xk-1)
		x1 = phi(x)
		#print(x1)
		convergence.append(x1)

		#O valor de x é baseado na função de ponto fixo e na sua
		#convergência para a raiz csi.
		if( (abs(f(x1)) < eps) or (abs(x1 - x) < eps) ):
			print("Raiz encontrada em " + str(k+1) + " iteracoes: " + str(x1))
			return True

		#Se a raiz não for encontrada, realiza novamente o procedimento
		x = x1

	if(k == itr - 1):
		print("Raiz não encontrada!")
		return False


x0 = input("x0: ")
x0 = float(x0)

eps = input("Insira a precisão: ")
eps = float(eps)

if(fixed_point(x0, eps)):
	plt.figure()
	plt.plot(convergence)
	plt.show()
