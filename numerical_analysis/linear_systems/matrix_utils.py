from __future__ import division
import numpy as np
import matplotlib.pyplot as plt

#função que retorna uma matriz para a aplicação do método
def entryMatrix():
	#dimensoes da matriz
	line = int(input("Quantidade de linhas: "))
	column = int(input("Quantidade de colunas: "))

	if (column-1 != line):
		print("Apenas matrizes quadradas!")
		return False

	#inicialização da matriz
	m = [0]*line
	for i in range(line):
		m[i] = [0]*column

	#inserção dos elementos da matriz
	#coeficientes (matriz A)
	print("Matriz de coeficientes (A):")
	a = []
	reg = 0

	while(reg < line):
		arow = list(map(int, input().split()))
		for i in range(line):
			m[reg][i] = arow[i]
		reg+=1

	#conjunto b
	print("Conjunto imagem (b):")

	b = list(map(int, input().split()))

	for i in range(line):
		m[i][column-1] = b[i]

	return m
	#fim da entrada

#multiplicacao de matrizes
def matrixMul(a, b):
	if(len(a[0]) != len(b)):
		#Se o número de colunas da matriz a for diferente do número
		#de linhas da matriz b
		print("Impossível realizar a multiplicação de matrizes!")
		return False
	else:
		#inicializa matriz resultado
		mr = [0]*len(a)
		for i in range(len(a)):
			mr[i] = [0]*len(b[0])

		#realiza multiplicação
		k=0
		while(k < len(mr)):
			for i in range(len(b[0])):
				soma = 0
				for j in range(len(a[0])):
					soma += a[k][j]*b[j][i];

				mr[k][i] = soma

			k+=1

		return mr

#soma de matrizes
def matrixSum(a, b):
	if((len(a) == len(b)) and (len(a[0]) == len(b[0]))):
		for i in range(len(a)):
			for j in range(len(a[0])):
				a[i][j] = a[i][j] + b[i][j]

		return a
	else:
		print("Impossível realizar a soma de matrizes!")
		return False

#subtracao de matrizes
def matrixSub(a, b):
	if((len(a) == len(b)) and (len(a[0]) == len(b[0]))):
		for i in range(len(a)):
			for j in range(len(a[0])):
				a[i][j] = a[i][j] - b[i][j]

		return a
	else:
		print("Impossível realizar a subtracao de matrizes!")
		return False

#impressão de matriz
def printMatrix(m):
	for i in range(len(m)):
		print(m[i])