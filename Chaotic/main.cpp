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
#include <fstream>
//#include <stdio.h>

using namespace std;

int main()
{
    int n=3;
    double l_0 = 0.1+1e-13, theta_0 = M_PI_2;
    ofstream file("l13.txt");
    file.precision(16);
    file << "n : " << n << endl;
    file << "l_0 : " << l_0 << endl << "theta_0 : " << theta_0 << endl;
    unif01_Gen *gen = CreatePendulum(n, 10000, theta_0, l_0);
//    bbattery_RepeatSmallCrush(gen, rep);
    for(int i=0;i<500;i++){
        file << gen->GetU01(gen->param, gen->state) << endl;
    }
    DeletePendulum(gen);
    return 0;
}
