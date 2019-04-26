# Inteligência Artificial - Trabalho 2 - PSO

## EXPLICAÇÃO TEÓRICA DO ALGORITMO
<p align="justify"/>
Semelhante a técnicas como Algorítimo Genético, Otimização por Colônia de Formigas, Otimização por Enxame de Vaga-lumes, o desenvolvimento deste algorítimo foi inspirado na observação do comportamento de um indivíduo em seu meio natural e atuação no coletivo.

<p align="justify"/>
O PSO simula o comportamento de um ou mais grupos (enxames) de uma espécie qualquer em busca de encontrar o máximo possível de alimento.

<p align="justify"/>
Sempre que uma partícula encontra uma quantidade de alimento, verifica-se se este número é superior ao máximo já encontrado, se assim for, a quantidade máxima é atualizada, e a localização em que essa partícula encontrou o alimento é armazenada.

<p align="justify"/>
As demais partículas ao se movimentarem em busca de alimento levarão em conta a localização que trouxe maior quantidade de alimento até então, dessa forma, tendem a seguir a partícula mais “bem-sucedida”.
<br>

## 1 PROBLEMA PROPOSTO
<p align="justify"/>
O problema que este trabalho propõe para compreensão de aplicação do algorítimo de Otimização por Enxame de Partículas é a minimização do resultado de uma fórmula matemática, a sexta fórmula de Schaffer[2].

<p align="justify"/>
A ideia é atingir o resultado mais próximo de zero com a execução da função por cada uma das partículas.

## 2. IMPLEMENTAÇÃO
<p align="justify"/>

## 3. EXEMPLO DE CHAMADA

As instruções abaixo foram testadas em distribuições Linux (Ubuntu 18.04 LTS).

Para executar o código é necessário ter instalado:
* Python 3
* g++ (Compilador para C++)

1. Compile o código com o seguinte comando (se estiver em um terminal com suporte ao compilador g++):
```shell
g++ -Wall -o nome_executavel PSO.cpp
```

2. Execute o código com o seguinte comando:
```shell
./nome_executavel
```

### 3.1 ENTRADAS

O algoritimo recebe como entrada um parâmetro:
* Número de partículas: Quantidade de partículas que buscarão a minimização do resultado da função fitness.

### 3.2 SAÍDA
<p align="justify"/>

## 4. FERRAMENTAS UTILIZADAS
* g++: Compilador que integra o pacote de ferramentas GCC (GNU Compiler Collection), pacote nativo em distribuições Linux.
* c++: Linguagem de programação de alto desempenho, superconjunto da linguagem C. Utilizado para construir o algorítimo PSO.
* Python 3.5: Linguagem de programação de alto nível, utilizada no trabalho para abrir os arquivos de saída da execução do PSO;
* matplotlib: Ferramenta disponível para Python para plotagem de gráficos.

## 5. REFERÊNCIAS E OUTROS MATERIAIS BASE
[1]. https://www.researchgate.net/publication/229157888_Empirical_Review_of_Standard_Benchmark_Functions_Using_Evolutionary_Global_Optimization
