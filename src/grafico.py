from os import system
from io import open
import platform

# Tente importar matplotlib, se falhar, tente instalar
try:
	from matplotlib import pyplot

except ImportError:

	print("Instalando matplotlib, aguarde...")

	# Se for MAC ou Linux, dê o comando, instale e limpe a tela
	if (platform.system().upper() != "WINDOWS"):
		system("pip3 install --user matplotlib 2>&1 >/dev/null")
		system("sudo apt install python3-tk 2>&1 >/dev/null")
		system("clear")

	else:
		system("pip install --user matplotlib /quiet")
		system("cls")

# Se após tentar instalar, o erro ainda persistir, avise e saia
try:
	from matplotlib import pyplot

except:
	print("Falha ao instalar dependências necessárias. Bye.")
	exit(1)


# Lê os arq. de saída do PSO e retorna um dicionário com a média de cada iteração
# formato do dicionário: {indice_da_iteração: valor_da_média}
# exemplo de retorno: { 1: 0.009, 2: 0.06565, 3: 0.04545, ...}
def carregar_csv(n_particulas):
	media = {}

	for n_iteracoes in [20, 50, 100]:
		sums = [0] * n_iteracoes

		# Para cada execução
		for i in range(1, 11):

			# Forme o nome do arquivo a ser lido
			path_arq = "%dp_%di_%dexec.csv" % (n_particulas, n_iteracoes, i)

			# Abra o arquivo em modo de leitura e leia todas suas linhas
			arq = open(path_arq, "r")
			lines = arq.readlines()

			# Para cada linha, acrescente o valor fitness do gbest (de execução i, e
			# iteração j) no somatório
			for j, line in enumerate(lines):
				sums[j] += float(line.split(";")[-1])

		# Para cada iteração, calcule a média:
		# Média = (soma da i-ésima iteração em todas execuções) / número de iterações
		for i, valor in enumerate(sums):
			sums[i] = valor / n_iteracoes

		# Armazene a média no dicionário
		media[n_iteracoes] = sums

	return media


# Cria um arquivo CSV no caminho recebido
def criar_arq_csv(path, dict_it_linhas):

	# Abra um arquivo em modo de escrita
	with open(path, 'w') as arq:

		# Para cada chave no dicionários
		for i_it in dict_it_linhas:

			# Acesse a lista de linhas contida no dicionário na chave atual
			for linha in dict_it_linhas[i_it]:

				# Escreva a linha no arquivo
				arq.write(linha)


# Cria uma tabela com o resultado de cada iteração, execução, grupo de iterações
def tabelar_resultado(n_partic):
	dic_iter_linhas = {}

	# Para cada conjunto de iteração
	for n_iter in [20, 50, 100]:

		# Crie o cabeçalho da tabela com os títulos das colunas
		dic_iter_linhas[0] = ["n_partic;n_iteracao;i_execução;i_iteracao;i_fitness\n"]

		for i_iter in range(1, n_iter + 1):
			dic_iter_linhas[i_iter] = []

		# Para cada execução
		for i in range(1, 11):

			# Gere o nome formatado do arquivo
			path_arq = "%dp_%di_%dexec.csv" % (n_partic, n_iter, i)

			# Abra o arquivo de entrada
			with open(path_arq, mode="r") as arq_entrada:
				linhas = arq_entrada.readlines()

				# Monte a linha a ser escrita no CSV, no formato:
				# Núm. de partículas, núm. de iter., índice da execução atual,
				# índice da iteração atual, valor do fitness do gbest atual
				for j, linha in enumerate(linhas):
					dic_iter_linhas[j + 1].append("%d;%d;%d;%s" % (n_partic, n_iter, i, linha.replace(".", ",")))

		# Crie a tabela (CSV) com o nome no seguinte formato:
		# "TABELA_número-partículas_num-iterações.csv"
		criar_arq_csv("TABELA_%dp_%di.csv" % (n_partic, n_iter), dic_iter_linhas)
		dic_iter_linhas = {}


def main():

	while(1):

		try:
			n_particulas = int(input("Digite o número desejado de partículas: "))

		except KeyboardInterrupt:
			print("\nPrograma finalizado! Bye...\n")
			exit(0)

		except Exception:
			print("\nErro desconhecido, saido...\n")
			exit(1)

		# Compile e execute o PSO em C++
		system("g++ -Wall -o PSO PSO.cpp")

		# Se o SO for MAC ou Linux, execute com "./nome_executável"
		if (platform.system().upper() != "WINDOWS"):
			system("./PSO %d" % n_particulas)

		else: system("PSO %d" % n_particulas)

		# Gere a tabela contendo o fitness de cada iteração e execução
		tabelar_resultado(n_particulas)

		# Carregue o CSV gerado pelo C++, gere e salve as médias p/ plotar no gráfico
		media = carregar_csv(n_particulas)

		# Preencha os valores (50 p/ 50 iterações, definido em sala de aula)
		val_eixo_x = [i for i in range(1, 51)]
		val_eixo_y = media[50]

		# Defina quais dados serão plotados e o símbolo usado p/ marcar cada ponto
		pyplot.plot(val_eixo_x, val_eixo_y, marker='o')
		last_x = val_eixo_x[-1]
		last_y = val_eixo_y[-1]

		# Nomeie os eixos X e Y
		pyplot.xlabel("Número da iteração")
		pyplot.ylabel("Fitness i-ésimo gbest")

		# Marque o melhor Gbest de forma destacada (em vermelho) no gráfico
		pyplot.text(last_x, last_y + 0.0001, f"{last_y:.2e}", color="red", fontsize=10)

		# Exiba o gráfico
		pyplot.show()

	return 0


main()