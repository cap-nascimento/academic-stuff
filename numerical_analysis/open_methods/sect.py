from __future__ import division
import numpy as np
import matplotlib.pyplot as plt
itr = 100

convergence = []

def f(x):
	return x**3 - 9*x + 3

def secant(x0, x1, eps):
	if(abs(f(x1)) < eps or (abs(x1 - x0) < eps)):
		print("Raiz encontrada: "+str(x1))
		return True

	for k in range(itr):
		x2 = x1 - (f(x1)*(x1 - x0))/(f(x1) - f(x0))
		convergence.append(x2)
		if(abs(f(x2)) < eps or abs(x2 - x1) < eps):
			print("Raiz encontrada em " + str(k+1) + " iterações: "+str(x2))
			return True

		x0 = x1
		x1 = x2

	if(k == itr-1):
		print("Raiz não encontrada!")
		return False


x0 = input("x0: ")
x1 = input("x1: ")
eps = input("Precisão: ")

x0 = float(x0)
x1 = float(x1)
eps = float(eps)

if(secant(x0, x1, eps)):
	plt.figure()
	plt.plot(convergence)
	plt.show()