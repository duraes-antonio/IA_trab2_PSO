try:
	from matplotlib import pyplot

except ImportError:

	print("Instalando matplotlib...")

	if (platform.system().upper() != "WINDOWS"):
		system("pip install --user matplotlib 2>&1 >/dev/null")
		system("cls")

	else:
		try:
			system("pip install matplotlib /quiet")

		except:
			system("pip3 install matplotlib /quiet")

		system("ls")


from matplotlib import pyplot
import os


def carregar_csv(n_particulas):
	media = {}
	for n_iteracoes in [20, 50, 100]:
		sums = [0] * n_iteracoes
		for i in range(1, 11):
			path_arq = "%dp_%di_%dexec.csv" %(n_particulas, n_iteracoes, i)
			arq = open(path_arq, "r")
			lines = arq.readlines()
			for j, line in enumerate(lines):
				sums[j] += float(line.split(";")[-1])

		for i, valor in enumerate(sums):
			sums[i] = valor / n_iteracoes

		media[n_iteracoes] = sums

	return media

def criar_arq_csv(path, dict_it_linhas):

	with open(path, 'w') as arq:
		for i_it in dict_it_linhas:
			for linha in dict_it_linhas[i_it]:
				arq.write(linha)

def tabelar_resultado(n_partic):

	dic_iter_linhas = {}

	#Para cada conjunto de iteração
	for n_iter in [20, 50, 100]:

		#Crie o cabeçalho da tabela com os títulos das colunas
		dic_iter_linhas[0] = ["n_partic;n_iteracao;i_execução;i_iteracao;i_fitness\n"]

		for i_iter in range(1, n_iter+1):
			dic_iter_linhas[i_iter] = []

		#Para cada execução
		for i in range(1, 11):

			path_arq = "%dp_%di_%dexec.csv" %(n_partic, n_iter, i)

			#Abra o arquivo de entrada
			with open(path_arq, "r") as arq_entrada:
				linhas = arq_entrada.readlines()

				for j, linha in enumerate(linhas):
					dic_iter_linhas[j+1].append("%d;%d;%d;%s" %(n_partic, n_iter, i, linha.replace(".", ",")))

		criar_arq_csv("TABELA_%dp_%di.csv" %(n_partic, n_iter), dic_iter_linhas)
		dic_iter_linhas = {}

def main():
	n_particulas = int(input("Digite a quantidade de partículas desejadas: "))

	#Compile e execute o PSO em C++
	os.system("g++ -Wall -o PSO PSO.cpp")
	os.system("./PSO %d" %n_particulas)

	tabelar_resultado(n_particulas)
	media = carregar_csv(n_particulas)

	val_eixo_x = [i for i in range(1, 51)]
	val_eixo_y = media[50]

	pyplot.plot(val_eixo_x, val_eixo_y, marker='o')
	last_x = val_eixo_x[-1]
	last_y = val_eixo_y[-1]

	#Nomeie os eixos X e Y
	pyplot.xlabel("Número de iterações")
	pyplot.ylabel("Fitness média iteração i")

	pyplot.text(last_x, last_y+0.0001, "{last_y:.2e}", color="red", fontsize=10)
	pyplot.show()
	return 0


main()