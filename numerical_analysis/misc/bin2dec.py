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
	s+=1;

m = float(n)
x = float(n);

m = math.floor(m)
x = math.floor(x)

m = round(float(n) - m, s)

left = 0.0
right = 0.0

if(m == 0.0):
	
	exp = 0
	while(x > 0):
		aux = math.floor(x/10)
		aux *= 10
		aux = math.floor(x-aux)
		left += aux*(2**exp)
		exp+=1
		x/=10

else:

	exp = 0
	while(x > 0):
		aux = math.floor(x/10)
		aux *= 10
		aux = math.floor(x-aux)
		left += aux*(2**exp)
		exp+=1
		x/=10
	
	aux = math.floor(m*10)
	m *=10

	size = 1
	while(m - aux != 0.0):
		m*=10
		aux = math.floor(m);
		size+=1

	exp = size
	while(m > 0):
		aux = math.floor(m/10)
		aux *= 10
		aux = math.floor(m - aux)
		right += aux*(1/(2**exp))
		exp-=1
		m/=10

number = left + right
print(number)


