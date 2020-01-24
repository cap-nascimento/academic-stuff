# -*- coding: utf-8 -*-
"""
Created on Sat Aug  4 11:26:29 2018

@author: anderson v. do nascimento
"""

#bibliotecas necessarias
import math as m
import matplotlib.pyplot as plt

n = input()

sequence = []

for i in range(int(n)+1):
	sequence.append(m.e**i - m.sin(i))

#print(sequence)

plt.figure()
plt.plot(sequence)
plt.ion()
plt.show()