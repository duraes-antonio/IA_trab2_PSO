//
// Created by x on 23/04/19.
//

#ifndef IA_TRAB2_PSO_IA_ESTRUTURAS_H
#define IA_TRAB2_PSO_IA_ESTRUTURAS_H

struct Eixos {
    double x;
    double y;
};

struct Best {
    Eixos pos;
    double fitness;
};

struct Particula {
    Eixos pos;
    Eixos v;
    Best pbest;
};


#endif //IA_TRAB2_PSO_IA_ESTRUTURAS_H
