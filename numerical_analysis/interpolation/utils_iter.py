# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt

iterations = 3000 

#função para plotar o gráfico de convergência para o caso 2x2
def conv_graph(x, eq1, eq2):
	eq1_x = np.arange(-5, 5, 0.1)
	eq1_y = (-2)*eq1_x

	eq2_x = np.arange(-5, 5, 0.1)
	eq2_y = ((-3)*(eq2_x))/2

	conv_x = []
	conv_y = []

	for i in range(len(x)):
		if(i%2 == 0):
			conv_x.append(x[i])
		else:
			conv_y.append(x[i])

	fig, ax = plt.subplots()
	ax.plot(eq1_x, eq1_y)
	ax.plot(eq2_x, eq2_y)
	ax.plot(conv_x, conv_y)

	plt.show()

#função para imprimir matrizes c/ vetor constante
# def print_matrix(m):
# 	for i in range(len(m[0])-1):
# 		for j in range(len(m[0])):
# 			print(m[i][j], end=' ')
# 		print()


def mag_itr_graph(x_mag, itrs, index):
	x = np.arange(0, itrs, 1)
	y = x_mag

	fig, ax = plt.subplots()

	ax.plot(x, y)
	ax.grid()

	if index == 0 :
		ax.set(title='f: iterações ->  ∥x̄∥, Hilbert 2x2',
			xlabel='Iterações', ylabel='∥x̄∥')
		'''
		fig.savefig("/home/anderson/Documentos/trabalhos/calculo_numerico/"+
					"implementacao_2/main/questao_1/graficos/magperiter2x2.png")
		'''
	elif index == 1:
		ax.set(title='f: iterações ->  ∥x̄∥, Hilbert 32x32',
			xlabel='Iterações', ylabel='∥x̄∥')
		'''
		fig.savefig("/home/anderson/Documentos/trabalhos/calculo_numerico/"+
					"implementacao_2/main/questao_1/graficos/magperiter32x32.png")
		'''	
	elif index == 2:
		ax.set(title='f: iterações ->  ∥x̄∥, Hilbert 64x64',
			xlabel='Iterações', ylabel='∥x̄∥')
		'''
		fig.savefig("/home/anderson/Documentos/trabalhos/calculo_numerico/"+
					"implementacao_2/main/questao_1/graficos/magperiter64x64.png")
		'''
	elif index == 3:
		ax.set(title='f: iterações ->  ∥x̄∥, Hilbert 128x128',
			xlabel='Iterações', ylabel='∥x̄∥')
		'''
		fig.savefig("/home/anderson/Documentos/trabalhos/calculo_numerico/"+
					"implementacao_2/main/questao_1/graficos/magperiter128x128.png")
		'''
	elif index == 5:
		ax.set(title='f: iterações ->  ∥x̄∥, Matriz BURDEN (converge)',
			xlabel='Iterações', ylabel='∥x̄∥')
		'''
		fig.savefig("/home/anderson/Documentos/trabalhos/calculo_numerico/"+
					"implementacao_2/main/questao_2/graficos/magperiterBurdenConv.png")
		'''
	elif index == 6:
		ax.set(title='f: iterações ->  ∥x̄∥, Matriz BURDEN (diverge)',
			xlabel='Iterações', ylabel='∥x̄∥')
		'''
		fig.savefig("/home/anderson/Documentos/trabalhos/calculo_numerico/"+
					"implementacao_2/main/questao_2/graficos/magperiterBurdenDivr.png")
		'''

	plt.show()

def vect_mag(v):
	mag = 0
	for i in range(len(v)):
		mag+=np.power(v[i], 2)

	return np.sqrt(mag)