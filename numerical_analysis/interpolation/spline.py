# -*- coding: utf-8 -*-
import numpy as np
import math as m
import matplotlib.pyplot as plt
from seidel import gauss_seidel as gs

file = open('data_pele.txt', 'r')
txt = file.read().split('\n')

x = []
y = []

for i in range(len(txt)):
	tsp = txt[i].split(' ')
	x.append(float(tsp[0]))
	y.append(float(tsp[1]))

file.close()

n = len(x)-1

h = []

for i in range(1, n+1):
	h.append(x[i] - x[i-1])

c = [0]*(n-1)

for i in range(n-1):
	c[i] = [0]*3

for i in range(n-1):
	c[i][0] = h[i]
	c[i][1] = 2*(h[i] + h[i+1])
	c[i][2] = h[i+1]

A = [0]*(n-1)
for i in range(n-1):
	A[i] = [0]*(n-1)


#matriz de coeficientes para o spline natural
for i in range(n-1):
	k = i
	if(i == 0):

		for j in range(1, 3):
			A[i][k] = c[i][j]
			k+=1

	elif(i == n-2):
		k-=1
		for j in range(2):
			A[i][k] = c[i][j]
			k+=1

	else:
		k-=1
		for j in range(3):
			A[i][k] = c[i][j]
			k+=1

#vetor constante

b = []

for i in range(1, n):
	b.append(6*((y[i+1] - y[i])/(x[i+1] - x[i]) - ((y[i] - y[i-1])/(x[i] - x[i-1]))))

for i in range(n-1):
	A[i].append(b[i])

v_approx = []
for i in range(n-1):
	v_approx.append(1)

g = gs(A, v_approx, 0.00001)

a = []
b = []
c = []
d = []

#g[0] e g[4] devem ser 0
g.insert(0, 0.0)
g.append(0.0)

#print(g)

for i in range(1, n+1):
	#a:
	a.append((g[i] - g[i-1])/(6*(x[i] - x[i-1])))
	#b:
	b.append((g[i])/2)
	#c:
	c.append(((y[i] - y[i-1])/(x[i] - x[i-1])) + ((2*(x[i] - x[i-1])*(g[i])) + g[i-1]*(x[i] - x[i-1]))/6)
	#d:
	d.append(y[i])


x_plot = []
y_plot = []

i = x[0]
while(i <= x[n]):
	x_plot.append(i)
	for j in range(1, n+1):
		if(i <= x[j] and i >= x[j-1]):
			y_plot.append(a[j-1]*np.power((i - x[j]), 3) +
					b[j-1]*np.power((i - x[j]), 2) +
					c[j-1]*(i - x[j]) + d[j-1])
			break
	i+=0.1
	i = round(i, 1)
	#print(i)

fig, ax = plt.subplots()
ax.set(xlabel='x', ylabel='f(x)')
ax.grid()

ax.plot(x, y, color='red')
ax.plot(x_plot, y_plot, color='green')
plt.show()