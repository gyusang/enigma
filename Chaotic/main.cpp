//
//  main.cpp
//  Chaotic
//
//  Created by 이상규 on 13/11/2018.
//  Copyright © 2018 이상규. All rights reserved.
//

#include "pendulum.hpp"
#include "bbattery.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
//#include <stdio.h>

using namespace std;

int main()
{
    int n;
    double l_0 = 0.1, theta_0 = M_PI_2;
    cout.precision(16);
    for(n=3;n<=5;n++){
        cout << "n : " << n << ", l_0 : " << l_0 << ", theta_0 : " << theta_0 << endl;
        unif01_Gen *gen = CreatePendulum(n, 10000, theta_0, l_0);
        bbattery_SmallCrush(gen);
//        for(int i=0;i<500;i++){
//            file << gen->GetU01(gen->param, gen->state) << endl;
//        }
        DeletePendulum(gen);
    }
    return 0;
}

