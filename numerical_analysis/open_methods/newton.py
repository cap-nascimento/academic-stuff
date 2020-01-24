from __future__ import division
import matplotlib.pyplot as plt
import numpy as np
itr = 100

convergence = []

#definicao das funções
def f(x):
	#return x**3 - 9*x +3
	#return x**(1/3) - x
	#return np.sin(x)
	return x - np.sqrt(2)

#definição das derivadas
def df(x):
	#return 3*(x**2) - 9
	#return 1/(3 * (x**(2/3))) - 1
	#return np.cos(x)
	return 1

#implementação do método
def newton_rhapson(x, eps):
	#Se o x0 fornecido for suficientemente próximo da raiz, escolha-o
	if(abs(f(x)) < eps):
		print("Raiz encontrada: " + str(x))
		return True

	#inicia iteração para determinar a raiz
	for k in range(itr):
		
		#x recebe o valor da função definida pelo método
		#a ideia é a mesma do ponto fixo
		x1 = x - ((f(x))/(df(x)))
		convergence.append(x1)

		#determina se o x obtido é próximo ou não da raiz
		if(abs(f(x1)) < eps or abs(x1 - x) < eps):
			print("Raiz encontrada em " + str(k+1) + " iteracoes: " + str(x1))
			return True

		#continua o procedimento
		x = x1

	if(k == itr-1):
		print("Raiz não encontrada!")
		return False



x0 = input("x0: ")
eps = input("Precisao inicial: ")

x0 = float(x0)
eps = float(eps)

if(newton_rhapson(x0, eps)):
	plt.figure()
	plt.plot(convergence)
	plt.show()