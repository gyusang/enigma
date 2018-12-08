//
//  main.cpp
//  Chaotic
//
//  Created by 이상규 on 13/11/2018.
//  Copyright © 2018 이상규. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <fstream>
#include "Eigen/Dense"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
//# define M_PIl          3.141592653589793238462643383279502884L
using namespace Eigen;
using namespace std;
int n,t, i, j, N;
double l, mass, theta_0, g = 9.8, h=0.001;
VectorXd M;
const static IOFormat CSVFormat(FullPrecision, DontAlignCols, ", ", ", ", "", "", "", "\n");
char s[50];
VectorXd n_pendulum(VectorXd state){
    MatrixXd A(n,n);
    VectorXd b(n),x(2*n), omega(n);
    for(i=0;i<n;i++){
        b(i) = 0;
        for(j=0;j<i;j++){
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
//    for(i=0; i<n; i++){
//        for(j=0; j<i;j++){
//            sprintf(s, "%.15f",A(i,j));
//            A(i,j) = strtod(s, NULL);
//            A(j,i) = A(i,j);
//        }
//        sprintf(s, "%.15f",A(i,i));
//        A(i,i) = strtod(s, NULL);
//    }
    b << A*b;
//    for(i=0;i<n;i++){
//        sprintf(s, "%.15f",b(i));
//        b(i) = strtod(s, NULL);
//    }
    x << omega,b;
    return x;
}

int main()
{
    ofstream file("save.txt");
    file.precision(16);
    int count = 0;
    cout.precision(16);
    cout << "N : ";
    cin >> N;
    cout << "n : ";
    cin >> n ;
    cout << "l : ";
    cin >> l;
    cout << "mass : ";
    cin >> mass;
    cout << "theta_0 : ";
    cin >> theta_0;
//    n = 5; l = 10; mass = 1; theta_0 = 90;
    theta_0 = M_PI*theta_0/180;
    M.resize(n);
    VectorXd y(2*n), y_2(2*n);
    for(int i=0;i<n;i++){
        M(i) = (n-i)*mass;
        y(i) = theta_0;
        y(n+i) = 0;
    }
    while(count<N){
        count += 1;
        y_2 = y + h * n_pendulum(y) / 2;
        y = y + h * n_pendulum(y_2);
        file << y.format(CSVFormat);
//        cout << n_pendulum(y).format(CSVFormat);
//        cout << y << endl << "-----" << endl;
    }
    
}
