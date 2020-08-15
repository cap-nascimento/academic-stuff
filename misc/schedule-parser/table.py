from config import *

def space_line(type):
	if type == 1:
		return '                '
	return '             '

def unique_line():
	return '+---------------'

def line():
	s = ''
	for i in range(6):
		if i == 0:
			s += '+'
		s += '-------------+'
	s += '\n'
	return s

def show_table(mtx):
	
	s = ''

	s += space_line(1)
	s += line()

	for i in range(6):
		if i == 0:
			s += space_line(1)
		s += '+ {0:12s}'.format(WEEK[i])
	s += '+\n'

	for i in range(len(HOUR)):
		s += unique_line()
		s += line()
		s += '+ {0:14s}'.format(HOUR[i]) + '+'
		for j in range(len(mtx[i])):
			if mtx[i][j] != '0':
				s += ' {0:12s}'.format(mtx[i][j])
			else:
				s += space_line(2)
			s += '+'
		s += '\n'

	s += unique_line()
	s += line()

	return s

def show_legend(dic):
	s = ''
	s += '\n\nLEGENDA:\n'
	for d in dic:
		s += d['code']+' - '+d['name']+'\n'
	return s