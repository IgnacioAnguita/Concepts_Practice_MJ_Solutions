#include <cmath>

#include "analyticalFunctions.h"
#include "test.h"

void Test_1(){
	cout<<"Test 1: Put Call Parity: ";
	double S_0 = 60;
	double K = 65;
	double r = 0.05;
	double vol = 0.3;
	double T = 0.25;
	double q = 0.05;
	double c,p,f =0;

	c = Call_Option( S_0,  K,  vol,  r,  T, q);
	p = Put_Option( S_0,  K,  vol,  r,  T, q);
	f = Forward( S_0,  K,  vol,  r,  T, q);
	if (abs(c-p-f)<0.001){
		cout<<"passed"<<endl;
	}
	else{
		cout<<"failed"<<endl;
	}
}




