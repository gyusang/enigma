//
//  pendulum.cpp
//  Chaotic
//
//  Created by 이상규 on 08/12/2018.
//  Copyright © 2018 이상규. All rights reserved.
//


#include "pendulum.hpp"
#include <iostream>
//#include <string.h>
#include <stdlib.h>

using namespace std;
#define g 9.8
#define h 0.01

VectorXd process_y;

class Pendulum{
private:
    int t;
    double l, mass, theta_0;
    VectorXd M, y;
    VectorXd derivs(VectorXd state);
public:
    int n;
    Pendulum(int n, int t, double l, double mass, double theta_0);
    ~Pendulum();
    void next_step();
    VectorXd current();
};

Pendulum::Pendulum(int _n, int N, double _l, double _mass, double _theta_0){
    n = _n;
    l = _l;
    mass = _mass;
    M.resize(n);
    y.resize(2*n);
    for(int i=0;i<n;i++){
        M(i) = (n-i)*mass;
        y(i) = theta_0;
        y(n+i) = 0;
    }
    for(int cnt=0;cnt<N;cnt++){
        next_step();
    }
}

Pendulum::~Pendulum(){
    M.resize(0);
    y.resize(0);
}

void Pendulum::next_step(){
    VectorXd y_2(2*n);
    y_2 = y + h * derivs(y) / 2;
    y = y + h * derivs(y_2);
}

VectorXd Pendulum::current(){
    return y;
}

VectorXd Pendulum::derivs(VectorXd state){
    MatrixXd A(n,n);
    VectorXd b(n),x(2*n), omega(n);
    for(int i=0;i<n;i++){
        b(i) = 0;
        for(int j=0;j<i;j++){
            A(i,j) = M(i)*l*l*cos(state(j)-state(i));
            A(j,i) = A(i,j);
            b[i] += M(i)*l*sin(state[j]-state[i])*state(n+j)*state(n+j);
        }
        
        A(i,i) = M(i)*l*l;
        for(int j=i;j<n;j++){
            b(i) += M(j)*l*sin(state[j]-state[i])*state(n+j)*state(n+j);
        }
        omega(i)=state(n+i);
        b(i) = b(i)*l-M(i)*g*l*sin(state[i]);
    }
    A << A.inverse();
    b << A*b;
    x << omega,b;
    return x;
}


static double Pendulum_U01(void *par, void *sta){
    double result;
    int *state = (int *) sta;
    Pendulum *pen = (Pendulum *) par;
    process_y.resize(pen->n);
    if(*state % pen->n == 0){
        *state = 0;
        pen->next_step();
    }
    process_y = pen->current();
    result = abs(process_y(*state));
    result *= 10000;
    *state += 1;
    return fmod(result, 1);
}

static unsigned long Pendulum_Bits (void *par, void *sta){
    return (unsigned long) (Pendulum_U01 (par, sta) * 4294967296);
}

static void WritePendulum (void *sta){
    int *state = (int *) sta;
    cout << "order : " << *state << endl;
}

unif01_Gen *CreatePendulum(int n, void *par){
    pendulum_init_param * init_param = (pendulum_init_param *) par;
    unif01_Gen *gen;
    int *state;
    size_t leng;
    char name[60];
    VectorXd y = VectorXd(2*n);
    Pendulum *pen;
    gen = (unif01_Gen *) malloc(sizeof(unif01_Gen));
    pen = new Pendulum(init_param->n, init_param->N, init_param->l,
                                 init_param->mass, init_param->theta_0);
    gen->state = state = (int*) malloc(sizeof(int));
    *state = 0;
    gen->param = pen;
    gen->Write = WritePendulum;
    gen->GetU01 = Pendulum_U01;
    gen->GetBits = Pendulum_Bits;
    strcpy(name, "n-Pendulum System"); // TODO add str int
    leng = strlen(name);
    gen->name = (char *) calloc(leng+1, sizeof(char));
    strncpy(gen->name, name, leng);
    return gen;
}

void DeletePendulum (unif01_Gen *gen){
    Pendulum *pen = (Pendulum *) gen->param;
    delete pen;
    free(gen->state);
    free(gen->param);
    free(gen->name);
    free(gen);
}

