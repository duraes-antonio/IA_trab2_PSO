# Inteligência Artificial - Trabalho 2 - PSO

## EXPLICAÇÃO TEÓRICA DO ALGORITMO
<p align="justify"/>
Semelhante a técnicas como Algorítimo Genético, Otimização por Colônia de Formigas, Otimização por Enxame de Vaga-lumes, o desenvolvimento deste algorítimo foi inspirado na observação do comportamento de um indivíduo em seu meio natural e atuação no coletivo [1].

<p align="justify"/>
O PSO simula o comportamento de um ou mais grupos (enxames) de uma espécie qualquer em busca de encontrar o máximo possível de alimento [2].

<p align="justify"/>
Sempre que uma partícula encontra uma quantidade de alimento, verifica-se se este número é superior ao máximo já encontrado, se assim for, a quantidade máxima é atualizada, e a localização em que essa partícula encontrou o alimento é armazenada.

<p align="justify"/>
As demais partículas ao se movimentarem em busca de alimento levarão em conta a localização que trouxe maior quantidade de alimento até então, dessa forma, tendem a seguir a partícula mais “bem-sucedida”.

<p align="justify"/>
Por trabalhar com a atuação de grupos sociais, o algorítimo leva em consideração dois principais conceitos sobre o comportamento de cada partículas, são eles: Inteligência cognitiva e social [3]. A inteligência social dita o quanto que o comportamento do bando influencia as ações do indivíduo, enquanto que a inteligência cognitiva diz respeito ao quanto o indivíduo considera como relevante seus próprios achados.

<p align="justify"/>
Além das inteligências citadas acima, o algorítimo trabalha com os conceitos de posição do indivíduo (em N dimensões, neste trabalho 2 dimensões serão abordadas) no espaço, e por este se movimentar, inclui-se também a variável velocidade (um valor para cada dimensão). Pelo fato de haver uma velocidade presente, há autores que optam pela adição de uma variável que represente um fator de inércia (representada em muitas obras como “w”), isto é, um valor que limite ou controle o quanto cada partícula está avançado no espaço.
<br>

## 1 PROBLEMA PROPOSTO
<p align="justify"/>
O problema que este trabalho propõe para compreensão de aplicação do algorítimo de Otimização por Enxame de Partículas é a minimização do resultado de uma fórmula matemática, a sexta fórmula de Schaffer[4].

<p align="justify"/>
A ideia é atingir o resultado mais próximo de zero com a execução da função por cada uma das partículas.

## 2. IMPLEMENTAÇÃO

### 2.1 Modelagem dos atores

Para implementação deste algorítimo, optamos por modelar estrutura contendo dois valores reais, par de eixos (x e y), nomeada de “Eixos”.
```cpp
/*Estrutura contendo o par de eixos X e Y;
 *Representa a posição, um ponto em um plano 2D;*/
struct Eixos {
    double x;
    double y;
};
```

Também modelamos uma estrutura chamada “Best” responsável por armazenar a posição (Eixos) e o melhor (neste caso, menor) valor (número real) encontrado até então.
```cpp
/*Armazena a posição que trouxe o melhor resultado da aplicação de uma função;
 *Fitness é o melhor valor, propriamente dito;*/
struct Best {
    Eixos pos;
    double fitness;
};
```

Por fim, foi realizada a modelagem da partícula em si, contendo sua posição atual (“pos”), velocidade (“vel”) para cada eixo, e seu momento Best, contendo a posição e melhor valor encontrado.
```cpp
struct Particula {

    /*Posição atual da partícula no plano*/
    Eixos pos;

    /*Par contendo a velocidade no eixo X e a velocidade no eixo Y*/
    Eixos vel;

    /*Estrutura com a posição do melhor valor alcançado pela partícula até então*/
    Best pbest;
};
```

### 2.2 Constantes

As seguintes constantes foram definidas de acordo com a especificação recebida.

Valores máximo e mínimo para a posição da partícula no plano:
```cpp
#define POS_MIN -100    /*Valor mínimo do intervalo de posição*/
#define POS_MAX 100     /*Valor máximo do intervalo de posição*/
```

Fator multiplicativo de velocidade e número desejado de execuções (utilizado para capturar as métricas de eficácia e, posteriormente, plotagem do gráfico comparativo):
```cpp
#define V_FATOR 0.15    /*15% do intervalo da posição máxima ou mínima*/
#define N_EXEC  10      /*Número de execuções do algorítimo*/
```

Coeficiente cognitivo, coeficiente social e fator de inércia:
```cpp
double c1 = 2.05, c2 = 2.05, w = 0.5;
```

### 2.3 Algorítimo PSO


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

[1]. Página 4. Disponível em: http://www.revistaeep.com/imagens/volume11_02/cap01.pdf
[2]. Página 13. Disponível em: http://antigo.nuclear.ufrj.br/DScTeses/Canedo/Tese_Final_Canedo.pdf
[3]. Página 3. Disponível em: https://fei.edu.br/sbai/SBAI2007/docs/30400_1.pdf
[4]. Fórmula 15, página 12. Disponível em: https://www.researchgate.net/publication/229157888_Empirical_Review_of_Standard_Benchmark_Functions_Using_Evolutionary_Global_Optimization
