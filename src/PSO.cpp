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

Best gbest;

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

    Particula ps[n_particulas];
    gbest.fitness = DBL_MAX;

    for (int i = 0; i < n_particulas; i++) {
        ps[i].pos.x = rand_int(rand_engine);
        ps[i].pos.y = rand_int(rand_engine);
        ps[i].pbest.fitness = DBL_MAX;
        ps[i].vel.x = rand_double_vel(rand_engine);
        ps[i].vel.y = rand_double_vel(rand_engine);
    }

    for (int k = 0; k < n_iteracoes; k++) {

        for (int i = 0; i < n_particulas; i++) {
            double fitness = f(ps[i].pos.x, ps[i].pos.y);
            
            if (fitness < ps[i].pbest.fitness) {
                ps[i].pbest.pos = ps[i].pos;
                ps[i].pbest.fitness = fitness;

                if (fitness < gbest.fitness) {
                    gbest.pos = ps[i].pos;
                    gbest.fitness = fitness;
                }
            }

            ps[i].vel.x = calc_v(ps[i].pbest.pos.x, ps[i].vel.x, ps[i].pos.x, gbest.pos.x);
            ps[i].vel.y = calc_v(ps[i].pbest.pos.y, ps[i].vel.y, ps[i].pos.y, gbest.pos.y);

            ps[i].pos.x = ps[i].pos.x + ps[i].vel.x;
            ps[i].pos.y = ps[i].pos.y + ps[i].vel.y;

            if (ps[i].pos.x > POS_MAX) {
                ps[i].pos.x = POS_MAX;
                ps[i].vel.x = 0;
            } else if (ps[i].pos.x < POS_MIN) {
                ps[i].pos.x = POS_MIN;
                ps[i].vel.x = 0;
            }

            if (ps[i].pos.y > POS_MAX) {
                ps[i].pos.y = POS_MAX;
                ps[i].vel.y = 0;
            } else if (ps[i].pos.y < POS_MIN) {
                ps[i].pos.y = POS_MIN;
                ps[i].vel.y = 0;
            }
        }
        cout << "Gbest de (" << gbest.pos.x << "," << gbest.pos.y << ") = " << gbest.fitness << endl;
    }
}