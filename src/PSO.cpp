#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <random>
#include <stdio.h>
#include <cstring>
#include <string>
#include "ia_estruturas.h"

#define POS_MIN -100    /*Valor mínimo do intervalo de posição*/
#define POS_MAX 100     /*Valor máximo do intervalo de posição*/
#define V_FATOR 0.15    /*15% do intervalo acima*/
#define V_MAX   100
#define N_EXEC  10

using namespace std;

/*Variáveis recebidas do usuário*/
int n_particulas;

/*Constantes;
 *Coeficiente cognitivo, coef. social e fator de inércia*/
double c1 = 2.05, c2 = 2.05, w = 0.5;

/*Variáveis para gerar números pseudo-aleatórios*/
random_device rand_semente;
mt19937 rand_engine(rand_semente());
uniform_int_distribution<int> rand_int(POS_MIN, POS_MAX);
uniform_real_distribution<double> rand_double_vel(POS_MIN * V_FATOR, POS_MAX * V_FATOR);
uniform_real_distribution<double> rand_double_pos(0, 1);

/*Função fitness - Função a ter seu resultado minimizado*/
double f(double x, double y) {
    double numerador = pow(sin(sqrt(x*x + y*y)), 2) - 0.5;
    double denominador = pow(1 + 0.001 * (x*x + y*y), 2);
    return 0.5 + (numerador / denominador);
}

/*Cria, inicializa corretamente e retorna N partículas*/
vector<Particula *> gerar_particulas(int num_particulas) {

    Particula *temp_part;
    vector<Particula *> particulas;

    /*[Instrução da ESPECIFICAÇÃO]
     * Gere a velocidade randômica de X e de Y, atribua a p/ todas partículas*/
    double geral_vx = rand_double_vel(rand_engine);
    double geral_vy = rand_double_vel(rand_engine);

    /*Para cada partícula*/
    for (int i = 0; i < num_particulas; ++i) {
        temp_part = (Particula *) malloc(sizeof(Particula));

        /*Defina um fitness padrão (flag), atribua a posição X e Y randômicas*/
        temp_part->pbest.fitness = -1;
        temp_part->pos.x = rand_int(rand_engine);
        temp_part->pos.y = rand_int(rand_engine);

        /*Para cada partícula, gere uma velocidade randômica p/ cada eixo*/
        temp_part->vel.x = geral_vx;
        temp_part->vel.y = geral_vy;
        particulas.push_back(temp_part);
    }

    return particulas;
}

/*Calcula e retorna a nova velocidade da partícula*/
double calc_v(double pbest_pos, double current_v, double p_pos, double gbest_pos){

    /*Gere os valores randômicos entre 0 e 1 para r1 e r2*/
    double r1 = rand_double_pos(rand_engine);
    double r2 = rand_double_pos(rand_engine);

    /*Calcule a velocidade cognitiva e social*/
    double veloc_cognit = c1 * r1 * (pbest_pos - p_pos);
    double veloc_social = c2 * r2 * (gbest_pos - p_pos);

    /*Calcule a velocidade final com o fator de inércia*/
    double v = w * current_v + veloc_cognit + veloc_social;

    /*Se ultrapassar o limite máximo/mínimo, defina vel. como máx/min*/
    if (v > POS_MAX * V_FATOR) v = POS_MAX * V_FATOR;
    else if (v < POS_MIN * V_FATOR) v = POS_MIN * V_FATOR;

    return v;
}

/*Atualiza a posição de uma partícula, considerando seus máximos e mínimos*/
void atualizar_posicao(Particula* particula) {

    particula->pos.x = particula->pos.x + particula->vel.x;
    particula->pos.y = particula->pos.y + particula->vel.y;

    if (particula->pos.x > POS_MAX) {
        particula->pos.x = POS_MAX;
        particula->vel.x = 0;
    }

    else if (particula->pos.x < POS_MIN) {
        particula->pos.x = POS_MIN;
        particula->vel.x = 0;
    }

    if (particula->pos.y > POS_MAX) {
        particula->pos.y = POS_MAX;
        particula->vel.y = 0;
    }

    else if (particula->pos.y < POS_MIN) {
        particula->pos.y = POS_MIN;
        particula->vel.y = 0;
    }
}

int main(int argc, char *argv[]){

    /*PASSO 1: Determinar o número de partículas*/
    n_particulas = atoi(argv[1]);

    /*[ESPCIFICAÇÃO] Estabeleça o número de iterações*/
    int iteracoes[] = {20, 50, 100};
    FILE * arquivo;

    /*Loop para quantidade de execuções*/
    for (int i = 0; i < N_EXEC; ++i){

        /*Para cada conjunto de iterações (20, 50, 100)*/
        for (int n_iteracoes : iteracoes){

            /*Nomeie os arquivos de saída no seguinte formato:
             *{NUM-PARTICULA}p_{NUM-ITERAÇÕES}i_{NUM-EXECUÇÃO-ATUAL}exec.csv*/
            char buffer[128];
            sprintf(buffer, "%dp_%di_%dexec.csv", n_particulas, n_iteracoes, i+1);

            /*Abrindo arquivo*/
            arquivo = fopen(buffer, "w");

            /*PASSO 2 e 3: Inicializar cada partícula com a mesma veloc. e posição diferente*/
            vector<Particula *> ps = gerar_particulas(n_particulas);
            Best gbest;
            gbest.fitness = DBL_MAX;

            /*Para cada iteração*/
            for (int k = 0; k < n_iteracoes; ++k) {

                /*PASSO 4: Para cada partíc., calcular sua aptidão e verificar seu p-best*/
                for (Particula *part: ps) {
                    double fitness = f(part->pos.x, part->pos.y);

                    if (fitness < part->pbest.fitness || part->pbest.fitness == -1.0) {
                        part->pbest.pos = part->pos;
                        part->pbest.fitness = fitness;

                        /*PASSO 5: Descobrir qual a melhor partícula globalmente.
                        *Verificação dentro do loop atual para evitar o custo de loop
                        * adicional só para verificar cada partícula*/
                        if (fitness < gbest.fitness) {
                            gbest.pos = part->pos;
                            gbest.fitness = fitness;
                        }
                    }

                    /*PASSO 6a e 6b: Atualizar a velocidade e a posição de cada eixo*/
                    part->vel.x = calc_v(part->pbest.pos.x, part->vel.x, part->pos.x, gbest.pos.x);
                    part->vel.y = calc_v(part->pbest.pos.y, part->vel.y, part->pos.y, gbest.pos.y);
                    atualizar_posicao(part);
                }

                /*Escreva o número da iteração e o resultado do gbest atual*/
                fprintf(arquivo, "%d;%.30lf\n", k+1, gbest.fitness);
            }

            /*Fechando arquivo*/
            fclose(arquivo);

            /*Libera a memória alocada dinamicamente*/
            for (int j = 0; j < n_particulas; ++j) free(ps[j]);
        }
    }
}