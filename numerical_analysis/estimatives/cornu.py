from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import math as m
import matplotlib.pyplot as plt
it = 20

def xs(s):
	sequence = []
	for i in range(it):
		op1 = np.power(-1.0, i)*np.power(s, (4.0*i + 1.0))
		op2 = 1.0/m.factorial(2.0*i)
		op3 = op1/(4.0*i + 1.0)
		sequence.append(op2*op3)

	#print(sequence)
	return np.sum(sequence)

def ys(s):
	sequence = []
	for i in range(it):
		op1 = np.power(-1.0, i)*np.power(s, (4.0*i + 3.0))
		op2 = 1.0/m.factorial(2.0*i + 1.0)
		op3 = op1/(4.0*i + 3.0)
		sequence.append(op2*op3)

	#print(sequence)
	return np.sum(sequence)

fig = plt.figure()
ax = fig.gca(projection='3d')

x = np.arange(-np.pi, np.pi, 0.01)
y = np.arange(-np.pi, np.pi, 0.01)
z = np.arange(-np.pi, np.pi, 0.01)
absc = []
orde = []
for i in x:
	absc.append(xs(i))

for i in y:
	orde.append(ys(i))

ax.plot(absc, orde, z, label='Espiral de Cornu')
ax.legend()

plt.show()