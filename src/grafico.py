from matplotlib import pyplot
import os


def carregar_csv(n_particulas):
	media = {}
	for n_iteracoes in [20, 50, 100]:
		sums = [0] * n_iteracoes
		for i in range(1, 11):
			arq = open(f"{n_particulas}p_{n_iteracoes}i_{i}exec.csv", "r")
			lines = arq.readlines()
			for j, line in enumerate(lines):
				sums[j] += float(line.split(";")[-1])

		for i, valor in enumerate(sums):
			sums[i] = valor / n_iteracoes

		media[n_iteracoes] = sums

	return media


def main():
	n_particulas = int(input("Digite a quantidade de partículas desejadas: "))

	os.system(f"./PSO {n_particulas}")

	media = carregar_csv(n_particulas)

	val_eixo_x = [i for i in range(1, 51)]
	val_eixo_y = media[50]

	pyplot.plot(val_eixo_x, val_eixo_y, marker='o')
	last_x = val_eixo_x[-1]
	last_y = val_eixo_y[-1]
	pyplot.text(last_x, last_y+0.001, f"{last_y:.2e}", color="red", fontsize=10)
	pyplot.show()
	return 0


main()