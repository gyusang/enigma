//
//  main.cpp
//  Chaotic
//
//  Created by 이상규 on 13/11/2018.
//  Copyright © 2018 이상규. All rights reserved.
//

#include "pendulum.hpp"
#include "bbattery.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
    int n, rep[11] = {0, };
    double l_0 = 10, theta_0 = M_PI_2;
    for(n=3;n<=5;n++){
        if(n==3)    rep[8] = 2;
        if(n==4)    rep[4] = 2;
        if(n==5){
            rep[9] = 2;
            rep[10] = 2;
        }
        cout << "n : " << n << ", l_0 : " << l_0 << ", theta_0 : " << theta_0 << endl;
        unif01_Gen *gen = CreatePendulum(n, 10000, theta_0, l_0);
        bbattery_RepeatSmallCrush(gen, rep);
        DeletePendulum(gen);
        if(n==3)    rep[8] = 0;
    }
    return 0;
}
