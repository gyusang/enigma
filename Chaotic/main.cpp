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
    n = 2; l_0 = 10; theta_0 = 90;
    theta_0 = M_PI*theta_0/180;

    unif01_Gen *gen = CreatePendulum(n, 10000, theta_0, l_0);
    cout.precision(15);
    for(int i=0;i<10;i++){
        cout << gen->GetU01(gen->param, gen->state) << endl;
    }
    return 0;
}
