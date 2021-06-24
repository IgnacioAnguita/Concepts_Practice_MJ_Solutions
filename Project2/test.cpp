#include "test.h"
#include "greeks.h"
#include "analyticalFunctions.h"
#include <iostream>
#include <stdlib.h>  
#include "PayOff.h"
#include "SimpleMC.h"
#include "SimpleMC3.h"

using namespace std;

void testDelta(){
	cout<<"Test 1 Call Delta";
	double S_0 = 100, K =100, vol = 0.2, r = 0.02, T = 1, q = 0, epsilon = 0.001 ;	
	double deltaCallA, c1,c2, deltaCallF;
	
	deltaCallA = DeltaCallOption(S_0, K, vol, r,  T, q);
	c1 = CallOption(S_0, K, vol, r,  T, q);
	c2 = CallOption(S_0 + epsilon, K, vol, r,  T, q);
	deltaCallF = (c2 - c1) / epsilon;
	
	if((deltaCallA-deltaCallF)/deltaCallF<0.01){
		cout<<": passed!"<<endl;
	}
	else{
		cout<<": failed!"<<endl;
	}	
}

void testGamma(){
	cout<<"Test 2 Call Gamma";
	double S_0 = 100, K =100, vol = 0.2, r = 0.02, T = 1, q = 0, epsilon = 0.001 ;	
	double gammaCallA, c1,c2,c3,gammaCallF;
	
	gammaCallA = GammaCallOption(S_0, K, vol, r,  T, q);
	c1 = CallOption(S_0, K, vol, r,  T, q);
	c2 = CallOption(S_0 + epsilon, K, vol, r,  T, q);
	c3 = CallOption(S_0 - epsilon, K, vol, r,  T, q);
	gammaCallF = (c2 - 2 * c1 + c3) / (epsilon * epsilon);
	
	if((gammaCallA-gammaCallF)/gammaCallF<0.01){
		cout<<": passed!"<<endl;
	}
	else{
		cout<<": failed!"<<endl;
	}	
}

void testVega(){
	cout<<"Test 3 Call Vega";
	double S_0 = 100, K =100, vol = 0.2, r = 0.02, T = 1, q = 0, epsilon = 0.0001 ;	
	double vegaCallA, c1,c2, vegaCallF;
	
	vegaCallA = VegaCallOption(S_0, K, vol, r,  T, q);
	c1 = CallOption(S_0, K, vol, r,  T, q);
	c2 = CallOption(S_0 , K, vol + epsilon, r,  T, q);
	vegaCallF = (c2 - c1) / (epsilon);
	
	if((vegaCallA-vegaCallF)/vegaCallF<0.01){
		cout<<": passed!"<<endl;
	}
	else{
		cout<<": failed!"<<endl;
	}	
}

void testRho(){
	cout<<"Test 4 Call Rho";
	double S_0 = 100, K =100, vol = 0.2, r = 0.02, T = 1, q = 0, epsilon = 0.0001 ;	
	double rhoCallA, c1,c2, rhoCallF;
	
	rhoCallA = VegaCallOption(S_0, K, vol, r,  T, q);
	c1 = CallOption(S_0, K, vol, r,  T, q);
	c2 = CallOption(S_0 , K, vol, r + epsilon,  T, q);
	rhoCallF = (c2 - c1) / (epsilon);
	
	if((rhoCallA-rhoCallF)/rhoCallF<0.01){
		cout<<": passed!"<<endl;
	}
	else{
		cout<<": failed!"<<endl;
	}	
}

void testTheta(){
	cout<<"Test 5 Call Theta";
	double S_0 = 100, K =100, vol = 0.2, r = 0.02, T = 1, q = 0, epsilon = 0.0001 ;	
	double thetaCallA, c1,c2, thetaCallF;
	
	thetaCallA = ThetaCallOption(S_0, K, vol, r,  T, q);
	c1 = CallOption(S_0, K, vol, r,  T, q);
	c2 = CallOption(S_0 , K, vol, r ,  T + epsilon, q);
	thetaCallF = (c2 - c1) / (epsilon);
	
	if((thetaCallA-thetaCallF)/thetaCallF<0.01){
		cout<<": passed!"<<endl;
	}
	else{
		cout<<": failed!"<<endl;
	}	
}

void testMC1(){
	cout<<"Test MC Calculating Delta through MC using different random numbers"<<endl;
	double S_0 = 100, K =100, vol = 0.2, r = 0.02, T = 1, q = 0, epsilon = 0.001 ;
	unsigned long int NumberOfPaths = 5000000;	
	PayOff payOffCall(K,PayOff::call);
	double deltaCallA = DeltaCallOption(S_0, K, vol, r,  T, q);
	double callMC1 = SimpleMonteCarlo(payOffCall,
						T,
						S_0,
						vol,
						r,
						NumberOfPaths);
	double callMC2 = SimpleMonteCarlo(payOffCall,
						T,
						S_0 + epsilon,
						vol,
						r,
						NumberOfPaths);
	double deltaMC = (callMC2 - callMC1) / epsilon;
	cout<<"Delta Analytic: "<<deltaCallA<<" Delta MC: "<<deltaMC<<endl;
}

void testMC2(){
	cout<<"Test MC Calculating Delta through MC using same random numbers"<<endl;
	double S_0 = 100, K =100, vol = 0.2, r = 0.02, T = 1, q = 0, epsilon = 0.001 ;
	unsigned long int NumberOfPaths = 5000000;	
	PayOff payOffCall(K,PayOff::call);
	double deltaCallA = DeltaCallOption(S_0, K, vol, r,  T, q);
	srand (1);
	double callMC1 = SimpleMonteCarlo(payOffCall,
						T,
						S_0,
						vol,
						r,
						NumberOfPaths);
	srand (1);
	double callMC2 = SimpleMonteCarlo(payOffCall,
						T,
						S_0 + epsilon,
						vol,
						r,
						NumberOfPaths);
	double deltaMC = (callMC2 - callMC1) / epsilon;
	cout<<"Delta Analytic: "<<deltaCallA<<" Delta MC: "<<deltaMC<<endl;
}

void testMC3(){
	cout<<"Test MC Calculating Delta through MC using the pathwise method"<<endl;
	double S_0 = 100, K =100, vol = 0.2, r = 0.02, T = 1, q = 0, epsilon = 0.001 ;
	unsigned long int NumberOfPaths = 5000000;	
	double deltaCallA = DeltaCallOption(S_0, K, vol, r,  T, q);
	double deltaMC = SimpleMonteCarlo3(K,
						T,
						S_0 + epsilon,
						vol,
						r,
						NumberOfPaths);

	cout<<"Delta Analytic: "<<deltaCallA<<" Delta MC: "<<deltaMC<<endl;
}
