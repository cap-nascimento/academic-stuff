from table import *
from parser import *

info = parse_hour(read_file())
matrix = generate_matrix(info)

schedule_table = ''

schedule_table += show_table(matrix)
schedule_table += show_legend(info)

with open('tabela.txt', 'w') as f:
	f.write(schedule_table)