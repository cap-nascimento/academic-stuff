from __future__ import division
import math
import numpy as np

n = input()

decPlaces = float(n)
initial = math.floor(decPlaces*10)
decPlaces*=10

s = 1
while(decPlaces - initial != 0.0):
	decPlaces*=10
	initial = math.floor(decPlaces)
	s+=1

m = float(n)
x = float(n)

m = math.floor(m)
x = math.floor(x)

m = round(float(n) - m, s)

xi = 0.0
xf = 0.0
exp = 0
while(x > 0):
	xi+= (x%2)*(10**exp)
	x = math.floor(x/2)
	exp+=1

exp = s-1
while(m - math.floor(m) != 0.0):
	m*=2
	if(math.floor(m)):
		xf+=1*(10**exp)
		exp-=1
		m-=1
	else:
		xf+=0*(10**exp)
		exp-=1

xf/=(10**s)

print(xi+xf)