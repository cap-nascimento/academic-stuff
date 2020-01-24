import numpy as np
import math as m
def euler(n):
	#return (np.power((-1.0), n)*np.power(0.5, (2.0*n+1.0)))/((2.0*n + 1.0)*m.factorial(n))
	return (np.power((-1.0), n)*np.power(0.5, (2.0*n+1.0)))/(((2.0*n + 1.0)*m.factorial(n))*np.power(2.0, n))

sequence = []

soma = 0.0
op4 = 1.0/np.sqrt(2.0*3.14)
for i in range(11):
	eu = euler(float(i))
	soma += eu

print(op4*soma)

