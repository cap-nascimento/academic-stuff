from __future__ import division
from matrix_utils import *
import numpy as np

#realiza multiplicação para eliminação
#monta a matrix L
def changeLine(a, nl, nla, piv, matrix_l):

	numerator = 0
	ml_position = 0
	for i in range(len(a[0])-1):
		if(a[nl][i] != 0):
			numerator = a[nl][i]
			ml_position = i
			break;

	matrix_l[nl][i] = 1
	matrix_l[nl][i] = numerator*matrix_l[nl][i]/piv
	for i in range(len(a[0])-1):
		a[nl][i] = a[nl][i] - (numerator*a[nla][i]/piv)

	return a

#monta a matriz identidade
def set_identity(a):
	matrix_l = [0]*len(a)
	for i in range(len(a)):
		matrix_l[i] = [0]*len(a)

	for i in range(len(a)):
		for j in range(len(a)):
			if(i == j):
				matrix_l[i][j] = 1

	return matrix_l

#define as matrizes L e U
def lu_decomp(a, matrix_l):
	if(len(a) <= 1):
		print("O sistema já possui solução!")
		return a
	else:
		pivot_line = 0
		pivot_column = 0
		k = 1
		while(pivot_line < len(a)-1):
			for i in range(k, len(a)):
				a = changeLine(a, i, pivot_line, a[pivot_line][pivot_column], matrix_l)

			pivot_line+=1
			pivot_column+=1
			k+=1

		return a

#resolve a equacao Ly = b, onde y = Ux
def solve_y(matrix_u, matrix_l):
	y = [0]*len(matrix_u)
	for i in range(len(matrix_l)):
		if(i == 0):
			y[i] = matrix_u[i][len(matrix_u[i])-1]
		else:
			subs = matrix_u[i][len(matrix_u[i])-1]
			for j in range(len(matrix_l[0])):
					subs -= matrix_l[i][j]*y[j];

			y[i] = subs

	return y

#resolve a equacao Ux = y
def solve_x(matrix_u, y):
	x = [0]*len(matrix_u)
	i = len(matrix_u) - 1
	xindex = len(matrix_u) - 1
	while(i >= 0):
		if(i == len(matrix_u) - 1):
			x[xindex] = y[i]/matrix_u[i][len(matrix_u[i])-2]
			xindex-=1
		else:
			subs = y[i]
			j = len(matrix_u[0])-2
			e_position = 0
			while(j >= 0):
				if(j!=i):
					subs-=matrix_u[i][j]*x[j]
				else:
					e_position = j

				j-=1

			x[xindex] = subs/matrix_u[i][e_position]
			xindex-=1

		i-=1

	return x