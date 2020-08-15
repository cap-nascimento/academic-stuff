import os

def read_file():
	s = []
	for x in os.listdir():
		if(x.endswith('.txt')):
			with open(x) as f:
				for l in f:
					s.append(l)
				return s

def middle_index(s):
	for i in range(len(s)):
		if s[i] == 'M' or s[i] == 'T' or s[i] == 'N':
			return i

def offset(c):
	if c == 'T':
		return 5
	if c == 'N':
		return 12
	return 0

def take_indexes(arr):
	ids = []
	for x in arr:
		x = x.upper()
		if len(x) >= 3:
			m = middle_index(x)
			for i in range(m):
				for j in range(m+1, len(x)):
					ids.append([int(x[i])-2, int(x[j])-1+offset(x[m])])
	return ids


def parse_hour(lines):
	dic = []
	for l in lines:
		l = l.replace('\n', '')
		arr = l.split('-')
		if len(arr) > 1:
			obj = {
				'code': arr[0].replace(' ', ''),
				'name': arr[1].rstrip().lstrip(),
				'schedule': take_indexes(arr[2].split(' '))
			}
			dic.append(obj)
	
	return dic

def generate_matrix(dic):
	mtx = ['0']*16
	for i in range(16): mtx[i] = ['0']*6

	for i in range(len(dic)):
		arr = dic[i]['schedule']
		for j in range(len(arr)):
			mtx[arr[j][1]][arr[j][0]] = dic[i]['code']

	return mtx