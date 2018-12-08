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
    int n, l, mass;
    double theta_0;
    pendulum_init_param *param = (pendulum_init_param *)malloc(sizeof(pendulum_init_param));
    n = 5; l = 10; mass = 1; theta_0 = 90;
    theta_0 = M_PI*theta_0/180;
    param -> n = n;
    param -> l = l;
    param -> mass = mass;
    param -> theta_0 = theta_0;
    param -> N = 10000;
    unif01_Gen *gen = CreatePendulum(n, param);
    cout.precision(11);
    for(int i=0;i<10;i++){
        cout << gen->GetU01(gen->param, gen->state) << endl;
    }
    return 0;
}
