from matplotlib import pyplot
from random import randint

def carregar_csv():
	#TODO desenvolver função
	pass

def main():

	val_eixo_x = [i for i in range(1, 11)]
	val_eixo_y = [randint(1, 4*i) for i in range(1, 11)]

	pyplot.plot(val_eixo_x, val_eixo_y)
	pyplot.show()
	return 0

main()