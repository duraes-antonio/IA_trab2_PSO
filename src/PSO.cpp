#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <float.h>
#include "ia_estruturas.h"

#define POS_MIN -100
#define POS_MAX 100
#define V_FATOR 0.15
#define V_MAX   100

using namespace std;

Best gbest;

/*Constantes*/
double c1 = 2.05, c2 = 2.05;
double r1, r2;


double f(double x, double y){
    double numerador = pow(sin(sqrt(x*x + y*y)), 2) - 0.5;
    double denominador = pow(1 + 0.001 * (x*x + y*y), 2);
    return 0.5 + (numerador / denominador);
}

double calc_v(double pbest_pos, double current_v, double p_pos, double gbest_pos){
    r1 = ((double) rand() / (RAND_MAX));
    r2 = ((double) rand() / (RAND_MAX));

    double v = current_v + c1 * r1 * (pbest_pos - p_pos) + c2 * r2 * (gbest_pos - p_pos);
    if (v > POS_MAX * V_FATOR) v = POS_MAX * 0.15;
    else if (v < POS_MIN * V_FATOR) v = POS_MIN * 0.15;
    return v;
}

int main(){
    int num_particulas;
    cin >> num_particulas;

    Particula ps[num_particulas];
    srand(time(NULL));
    gbest.fitness = DBL_MAX;

    for (int i = 0; i < num_particulas; i++){
        ps[i].pos.x = rand() % 201 - 100;
        ps[i].pos.y = rand() % 201 - 100;
        ps[i].pbest.fitness = DBL_MAX;
        ps[i].v.x = rand() % int(V_MAX * V_FATOR);
        ps[i].v.y = rand() % int(V_MAX * V_FATOR);
    }

    for (int k = 0; k < 100; k++){

        for (int i = 0; i < num_particulas; i++){
            double fitness = f(ps[i].pos.x, ps[i].pos.y);
            
            if (fitness < ps[i].pbest.fitness) {
                ps[i].pbest.pos = ps[i].pos;
                ps[i].pbest.fitness = fitness;

                if (fitness < gbest.fitness) {
                    gbest.pos = ps[i].pos;
                    gbest.fitness = fitness;
                    
                    cout << "Gbest de (" << gbest.pos.x << "," << gbest.pos.y << ") = " << gbest.fitness << endl;
                }
            }

            ps[i].v.x = calc_v(ps[i].pbest.pos.x, ps[i].v.x, ps[i].pos.x, gbest.pos.x);
            ps[i].v.y = calc_v(ps[i].pbest.pos.y, ps[i].v.y, ps[i].pos.y, gbest.pos.y); 

            ps[i].pos.x = ps[i].pos.x + ps[i].v.x;
            ps[i].pos.y = ps[i].pos.y + ps[i].v.y;

            if (ps[i].pos.x > POS_MAX) {
                ps[i].pos.x = POS_MAX;
                ps[i].v.x = 0;
            } else if (ps[i].pos.x < POS_MIN) {
                ps[i].pos.x = POS_MIN;
                ps[i].v.x = 0;
            }

            if (ps[i].pos.y > POS_MAX) {
                ps[i].pos.y = POS_MAX;
                ps[i].v.y = 0;
            } else if (ps[i].pos.y < POS_MIN) {
                ps[i].pos.y = POS_MIN;
                ps[i].v.y = 0;
            }
        }

    }
}