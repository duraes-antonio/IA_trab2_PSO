#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <random>
#include "ia_estruturas.h"

#define POS_MIN -100
#define POS_MAX 100
#define V_FATOR 0.15
#define V_MAX   100

using namespace std;

/*Variáveis recebidas do usuário*/
int n_particulas, n_iteracoes;

/*Constantes*/
double c1 = 2.05, c2 = 2.05;

/*Variáveis para gerar números pseudo-aleatórios*/
random_device rand_semente;
mt19937 rand_engine(rand_semente());
uniform_int_distribution<int> rand_int(POS_MIN, POS_MAX);
uniform_real_distribution<double> rand_double_vel(POS_MIN * V_FATOR, POS_MAX * V_FATOR);
uniform_real_distribution<double> rand_double_pos(0, 1);

/*Lê a qtd. de partículas e a qtd. de iterações*/
void ler_dados() {

    printf("\nDigite o número de partículas:\n");
    cin >> n_particulas;

    printf("\nDigite o número de iterações:\n");
    cin >> n_iteracoes;
}

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

    /*Gere uma posição randômica e a atribua para todas partículas*/
    double pos_geral_x = rand_int(rand_engine);
    double pos_geral_y = rand_int(rand_engine);

    for (int i = 0; i < num_particulas; ++i) {
        temp_part = (Particula *) malloc(sizeof(Particula));
        temp_part->pbest.fitness = -1;
        temp_part->pos.x = pos_geral_x;
        temp_part->pos.y = pos_geral_y;

        /*Para cada partícula, gere uma velocidade randômica p/ cada eixo*/
        temp_part->vel.x = rand_double_vel(rand_engine);
        temp_part->vel.y = rand_double_vel(rand_engine);
        particulas.push_back(temp_part);
    }

    return particulas;
}

/*Calcula e retorna a nova velocidade da partícula*/
double calc_v(double pbest_pos, double current_v, double p_pos, double gbest_pos){

    double r1 = rand_double_pos(rand_engine);
    double r2 = rand_double_pos(rand_engine);

    double veloc_cognit = c1 * r1 * (pbest_pos - p_pos);
    double veloc_social = c2 * r2 * (gbest_pos - p_pos);
    double v = current_v + veloc_cognit + veloc_social;

    if (v > POS_MAX * V_FATOR) v = POS_MAX * V_FATOR;
    else if (v < POS_MIN * V_FATOR) v = POS_MIN * V_FATOR;

    return v;
}

int main(){

    ler_dados();

    vector<Particula *> ps = gerar_particulas(n_particulas);
    Best gbest;
    gbest.fitness = DBL_MAX;

    for (int k = 0; k < n_iteracoes; ++k) {

        for (Particula *part: ps) {
            double fitness = f(part->pos.x, part->pos.y);

            if (fitness < part->pbest.fitness || part->pbest.fitness == -1.0) {
                part->pbest.pos = part->pos;
                part->pbest.fitness = fitness;

                if (fitness < gbest.fitness) {
                    gbest.pos = part->pos;
                    gbest.fitness = fitness;
                }
            }

            part->vel.x = calc_v(part->pbest.pos.x, part->vel.x, part->pos.x, gbest.pos.x);
            part->vel.y = calc_v(part->pbest.pos.y, part->vel.y, part->pos.y, gbest.pos.y);

            part->pos.x = part->pos.x + part->vel.x;
            part->pos.y = part->pos.y + part->vel.y;

            if (part->pos.x > POS_MAX) {
                part->pos.x = POS_MAX;
                part->vel.x = 0;
            } else if (part->pos.x < POS_MIN) {
                part->pos.x = POS_MIN;
                part->vel.x = 0;
            }

            if (part->pos.y > POS_MAX) {
                part->pos.y = POS_MAX;
                part->vel.y = 0;
            } else if (part->pos.y < POS_MIN) {
                part->pos.y = POS_MIN;
                part->vel.y = 0;
            }
        }
        cout << "Gbest de (" << gbest.pos.x << "," << gbest.pos.y << ") = " << gbest.fitness << endl;
    }

    for (int i = 0; i < n_particulas; ++i) free(ps[i]);
}