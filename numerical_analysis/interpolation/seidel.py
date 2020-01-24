# -*- coding: utf-8 -*-
from utils_iter import *

#implementação do método de Gauss-Seidel comentada
def gauss_seidel(m, v_approx, eps):

	convergence = False
	itrs = 0
	while(not convergence):

		#cópia da matriz de coeficientes
		m_itr = [0]*(len(m[0])-1)
		for i in range((len(m[0])-1)):
			m_itr[i] = [0]*len(m[0])

		for i in range(len(m[0])-1):
			for j in range(len(m[0])):
				m_itr[i][j] = m[i][j]

		#cópia da lista de aproximações
		x_itr = []
		for i in range(len(v_approx)): x_itr.append(v_approx[i])

		#Dividimos os coeficientes e o valor
		#do vetor constante da respectiva linha pelo
		#coeficiente do elemento da diagonal principal
		for i in range(len(m_itr[0])-1):
			divider = m_itr[i][i]
			for j in range(len(m_itr[0])):
				if(i!=j):
					m_itr[i][j] /= divider


		#Efetuamos a multiplicação do valor da lista de
		#aproximações pelo valor correspondente na linha
		#da matriz de coeficientes, com exceção do valor do
		#vetor constante. Ainda na mesma linha efetuamos a
		#subtração de todos os valores da linha da matriz do
		#valor do vetor constante e atualizamos o valor na
		#lista de aproximações com o resultado da subtração.
		for i in range(len(m_itr[0])-1):
			for j in range(len(m_itr[0])-1):
				if(i!=j):
					m_itr[i][j] *= v_approx[j]

			for j in range(len(m_itr[0])-1):
				if(i!=j):
					m_itr[i][len(m_itr[0])-1] -= m_itr[i][j]

			v_approx[i] = m_itr[i][len(m_itr[0])-1]

		#verifica o número de iterações levadas
		itrs+=1

		#realiza o teste do erro relativo
		max_abs = max(v_approx, key=abs)
		diff = []
		for i in range(len(m[0])-1):
			diff.append(v_approx[i] - x_itr[i])

		if(abs(max(diff, key=abs))/abs(max_abs) < eps):
			convergence = True

	if(convergence):
			return v_approx
	else:
		print("Número de iterações ultrapassado!\n")
		return v_approx


def gauss_seidel_mod(m, v_approx, eps, index, toAbel):

	#dados para o gráfico de magnitude do vetor resposta
	#por iteração
	x_mag = []

	#implementação do método segue como em def gauss_seidel
	convergence = False
	itrs = 0
	while(not convergence):

		x_mag.append(vect_mag(v_approx))

		m_itr = [0]*(len(m[0])-1)
		for i in range((len(m[0])-1)):
			m_itr[i] = [0]*len(m[0])

		for i in range(len(m[0])-1):
			for j in range(len(m[0])):
				m_itr[i][j] = m[i][j]

		x_itr = v_approx.copy()

		for i in range(len(m_itr[0])-1):
			divider = m_itr[i][i]
			for j in range(len(m_itr[0])):
				if(i!=j):
					m_itr[i][j] /= divider

		for i in range(len(m_itr[0])-1):
			for j in range(len(m_itr[0])-1):
				if(i!=j):
					m_itr[i][j] *= v_approx[j]

			for j in range(len(m_itr[0])-1):
				if(i!=j):
					m_itr[i][len(m_itr[0])-1] -= m_itr[i][j]

			v_approx[i] = m_itr[i][len(m_itr[0])-1]

		itrs+=1
		if(toAbel):
			if(itrs >= (iterations)/10):
				break
		else:
			if(itrs >= iterations):
				break

		max_abs = max(v_approx, key=abs)
		diff = []
		for i in range(len(m[0])-1):
			diff.append(v_approx[i] - x_itr[i])

		if(abs(max(diff, key=abs))/abs(max_abs) < eps):
			convergence = True

	if(convergence):
		x_mag.append(vect_mag(v_approx))
		itrs+=1
		print("Gerando gráfico...\n")
		mag_itr_graph(x_mag, itrs, index)
	else:
		print("O método ultrapassou o número de iterações ou não chegou em uma solução.\nGerando gráfico...\n")
		mag_itr_graph(x_mag, itrs, index)