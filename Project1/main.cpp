#include <cmath>
#include <math.h> 
#include <iostream>
#include <cstdlib>
#include "normal.h"
#include "analyticalFunctions.h"
#include "test.h"

using namespace std;

int main(){
	
	double S_0 = 60;
	double K = 65;
	double r = 0.08;
	double vol = 0.3;
	double T = 0.25;
	double q = 0;
	double c ;

	c = Call_Option( S_0,  K,  vol,  r,  T, q);
	cout<<"The price of the call is: "<<c<<endl;
	S_0 = 100 ;K = 80 ; T= 0.75; r = 0.06; vol = 0.35; q = 0.06;
	
	c = Digital_Put_Option( S_0,  K,  vol,  r,  T,  q);
	cout<<"The price of the digital put is: "<<c<<endl;
	Test_1();

	
	return 0;
}
