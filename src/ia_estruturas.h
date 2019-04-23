//
// Created by x on 23/04/19.
//

#ifndef IA_TRAB2_PSO_IA_ESTRUTURAS_H
#define IA_TRAB2_PSO_IA_ESTRUTURAS_H

/*Estrutura contendo o par de eixos X e Y;
 *Representa a posição, um ponto em um plano 2D;*/
struct Eixos {
    double x;
    double y;
};

/*Armazena a posição que trouxe o melhor resultado da aplicação de uma função;
 *Fitness é o melhor valor, propriamente dito;*/
struct Best {
    Eixos pos;
    double fitness;
};


struct Particula {

    /*Posição atual da partícula no plano*/
    Eixos pos;

    /*Par contendo a velocidade no eixo X e a velocidade no eixo Y*/
    Eixos vel;

    /*Estrutura com a posição do melhor valor alcançado pela partícula até então*/
    Best pbest;
};


#endif //IA_TRAB2_PSO_IA_ESTRUTURAS_H
