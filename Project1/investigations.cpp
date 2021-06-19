#include "investigations.h"
#include <iostream>
#include "analyticalFunctions.h"
#include <algorithm> 

using namespace std;

void investigation_1(){

	double S_0 = 60;
	double K = 65;
	double r = 0.08;
	double T = 0.25;
	double q = 0;
	
	cout<<endl<<"Investigation 1: Checking the effect on call prices the Volatility: "<<endl;
	
	for (int i= 1; i<=10; i++){
		cout<<"Volatility: "<<0.1 * i<<" Call Price: "<<
			Call_Option(S_0,  K,  0.1 * i,  r,  T, q)<<endl;
	}		
}

void investigation_2(){

	double S_0 = 60;
	double K = 65;
	double r = 0.08;
	double T = 0.25;
	double q = 0;
	
	cout<<endl<<"Investigation 2: Checking the effect on digital call prices the Volatility: "<<endl;
	
	for (int i= 1; i<=10; i++){
		cout<<"Volatility: "<<0.1 * i<<" Digital Call Price: "<<
			Digital_Call_Option(S_0,  K,  0.1 * i,  r,  T, q)<<endl;
	}		
}

void investigation_3(){

	double S_0 = 60;
	double K = 60;
	double r = 0.08;
	double T = 0.25;
	double q = 0;
	
	cout<<endl<<"Investigation 3: Checking the effect on call prices ATM the Volatility: "<<endl;
	
	for (int i= 1; i<=10; i++){
		cout<<"Volatility: "<<0.1 * i<<" Call Price ATM: "<<
			Digital_Call_Option(S_0,  K,  0.1 * i,  r,  T, q)<<endl;
	}		
}

void investigation_4(){

	double S_0 = 60;
	double K = 60;
	double r = 0.08;
	double T = 0.25;
	double q = 0;
	double vol = 0.3;
	double movedSpot = 0;
	
	cout<<endl<<"Investigation 4: Checking the intrinsic value Vs Price on put options: "<<endl;
	
	for (int i= 1; i<=10; i++){
		movedSpot = S_0 * (-0.5 + i/10.0 +1);
		cout<<"Spot: "<<movedSpot<<" Put Price : "<<
			Put_Option(movedSpot,  K,  vol,  r,  T, q)<<" Intrinsic Value: "<<max(-movedSpot+K,0.0)<<endl;
	}		
}
