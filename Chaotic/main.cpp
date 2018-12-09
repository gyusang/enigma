//
//  main.cpp
//  Chaotic
//
//  Created by 이상규 on 13/11/2018.
//  Copyright © 2018 이상규. All rights reserved.
//

#include "pendulum.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
    int n;
    double theta_0, l_0;
    pendulum_init_param *param = (pendulum_init_param *)malloc(sizeof(pendulum_init_param));
    VectorXd l, m, y_0;
    n = 5; l_0 = 10; theta_0 = 90;
    theta_0 = M_PI*theta_0/180;
    
    l.resize(n);
    m.resize(n);
    y_0.resize(2*n);

    for(int i=0;i<n;i++){
        l(i) = l_0;
        m(i) = 1;
        y_0(i) = theta_0;
        y_0(n+i) = 0;
    }
    param -> n = n;
    param -> _l = &l;
    param -> _m = &m;
    param -> y_0 = &y_0;
    param -> N = 10000;
    
    unif01_Gen *gen = CreatePendulum(n, param);
    cout << "hi" << endl;
    cout.precision(11);
    for(int i=0;i<10;i++){
        cout << gen->GetU01(gen->param, gen->state) << endl;
    }
    return 0;
}
