//
//  pendulum.hpp
//  Chaotic
//
//  Created by 이상규 on 08/12/2018.
//  Copyright © 2018 이상규. All rights reserved.
//

#ifndef pendulum_hpp
#define pendulum_hpp

extern "C"{
#include "TestU01.h"
}
#include "Eigen/Dense"
using namespace Eigen;

unif01_Gen *CreatePendulum(int n, void *par);
void DeletePendulum (unif01_Gen *gen);

typedef struct {
    int n, N;
    double l, mass, theta_0;
} pendulum_init_param;


#endif /* pendulum_hpp */


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
