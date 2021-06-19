#include <cmath>
#include "analyticalFunctions.h"
#include "test.h"
#include "PayOff.h"
#include "SimpleMC.h"

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

void Test_2(){
	cout<<"Test 2: Call decrease with Strike: ";
	double S_0 = 60;
	double KMax = 100;
	double KMin = 50;
	double r = 0.05;
	double vol = 0.3;
	double T = 0.25;
	double q = 0.05;
	double cCurrent,cPrev;
	double KIncrement = 1;

	cPrev = Call_Option(S_0,  KMin,  vol,  r,  T, q);
	
	for(double K = KMin + KIncrement; K<= KMax; K+= KIncrement){
		cCurrent = Call_Option(S_0,  K,  vol,  r,  T, q);
		if (cCurrent>cPrev){
			cout<<"failed"<<endl;
			return;
		}	
		cPrev = cCurrent;		
	}
	cout<<"passed"<<endl;
	return;
}

void Test_3(){
	cout<<"Test 3: S - S-Ke-rT ";
	double S_0 = 60;
	double K = 100;
	double r = 0.05;
	double vol = 0.3;
	double T = 0.25;
	double q = 0.05;
	double c;

	c = Call_Option(S_0,  K,  vol,  r,  T, q);
	
	if (c<=S_0 && c>=S_0-K*ZCBond(r,T)){		
		cout<<"passed"<<endl;
	}
	else{
		cout<<"failed"<<endl;
	}
}

void Test_4(){
	cout<<"Test 4: Call decrease with decreasing volatility: ";
	double S_0 = 60;
	double volMax = 1;
	double volMin = 0.1;
	double r = 0.05;
	double T = 0.25;
	double q = 0.05;
	double K = 50;
	double cCurrent,cPrev;
	double volIncrement = 0.01;

	cPrev = Call_Option(S_0,  K,  volMin,  r,  T, q);
	
	for(double vol = volMin + volIncrement; vol<= volMax; vol+= volIncrement){
		cCurrent = Call_Option(S_0,  K,  vol,  r,  T, q);
		if (cCurrent<cPrev){
			cout<<"failed"<<endl;
			return;
		}
		cPrev = cCurrent;		
	}
	cout<<"passed"<<endl;
}

void Test_5(){
	cout<<"Test 5: Call increase with increasing T: ";
	double S_0 = 60;
	double vol = 0.2;
	double r = 0.05;
	double TMin = 0.25;
	double TMax = 2;
	double q = 0.0;
	double K = 50;
	double cCurrent,cPrev;
	double TIncrement = 0.01;

	cPrev = Call_Option(S_0,  K,  vol,  r,  TMin, q);
	
	for(double T = TMin + TIncrement; T <= TMax; T+= TIncrement){
		cCurrent = Call_Option(S_0,  K,  vol,  r,  T, q);
		if (cCurrent<cPrev){
			cout<<"failed"<<endl;
			return;
		}
		cPrev = cCurrent;			
	}
	cout<<"passed"<<endl;
}

void Test_6(){
	cout<<"Test 6: Convexity check: ";
	double S_0 = 60;
	double K = 65;
	double r = 0.05;
	double vol = 0.3;
	double T = 0.25;
	double q = 0.05;
	double c1,c2,c3 =0;
	
	c1 = Call_Option(S_0,  K,  vol,  r,  T, q);
	c2 = Call_Option(S_0,  K+5,  vol,  r,  T, q);
	c3 = Digital_Call_Option( S_0,  K+10,  vol,  r,  T, q);
	
	
	if ((c1+c3)/2>c2){
		
		cout<<"passed"<<endl;
	}
	else{
		cout<<"failed"<<endl;
	}
}

void Test_7(){
	cout<<"Test 7: Spread with calls and Digital Call: ";
	double S_0 = 60;
	double K = 65;
	double r = 0.05;
	double vol = 0.3;
	double T = 0.25;
	double q = 0.05;
	double c1,c2,dc =0;
	
	c1 = Call_Option(S_0,  K,  vol,  r,  T, q);
	c2 = Call_Option(S_0,  K+1,  vol,  r,  T, q);
	dc = Digital_Call_Option( S_0,  K,  vol,  r,  T, q);
	
	
	if (abs(-c2+c1-dc)<0.1){
		
		cout<<"passed"<<endl;
	}
	else{
		cout<<"failed"<<endl;
	}
}

void Test_8(){
	cout<<"Test 8: Put Call Parity with digitals: ";
	double S_0 = 60;
	double K = 65;
	double r = 0.05;
	double vol = 0.3;
	double T = 0.25;
	double q = 0.05;
	double c,p,z =0;

	c = Digital_Call_Option( S_0,  K,  vol,  r,  T, q);
	p = Digital_Put_Option( S_0,  K,  vol,  r,  T, q);
	z = ZCBond(r, T);
	
	if (abs(c+p-z)<0.001){
		cout<<"passed"<<endl;
	}
	else{
		cout<<"failed"<<endl;
	}
}

void TestMC(){
	
	double S_0 = 60;
	double K = 65;
	double r = 0.08;
	double vol = 0.3;
	double T = 0.25;
	double q = 0;
	
	double callAnalytical, digitalCallAnalytical;
	double putAnalytical, digitalPutAnalytical;
	
	unsigned long NumberOfPaths = 2000000;
	
	PayOff payOffCall(K,PayOff::call);
	PayOff payOffPut(K,PayOff::put);
	PayOff payOffDigitalCall(K,PayOff::digitalCall);
	PayOff payOffDigitalPut(K,PayOff::digitalPut);
	
	double callMC = SimpleMonteCarlo(payOffCall,
						T,
						S_0,
						vol,
						r,
						NumberOfPaths);
						
	double digitalCallMC = SimpleMonteCarlo(payOffDigitalCall,
						T,
						S_0,
						vol,
						r,
						NumberOfPaths);
						
	double putMC = SimpleMonteCarlo(payOffPut,
						T,
						S_0,
						vol,
						r,
						NumberOfPaths);
						
	double digitalPutMC = SimpleMonteCarlo(payOffDigitalPut,
						T,
						S_0,
						vol,
						r,
						NumberOfPaths);
						
						
	
	callAnalytical = Call_Option(S_0,  K,  vol,  r,  T, q);
	digitalCallAnalytical = Digital_Call_Option(S_0,  K,  vol,  r,  T, q);
	putAnalytical = Put_Option(S_0,  K,  vol,  r,  T, q);
	digitalPutAnalytical = Digital_Put_Option(S_0,  K,  vol,  r,  T, q);
	
	cout<<"Test MC:"<<endl;
	if((callAnalytical-callMC)/callMC<0.001){
		cout<<"   Call test: passed"<<endl;
	}
	else{cout<<"   Call test: failed"<<endl;}
	
	if((digitalCallAnalytical-digitalCallMC)/digitalCallMC<0.001){
		cout<<"   Digital Call test: passed"<<endl;
	}
	else{cout<<"   Digital Call test: failed"<<endl;}
	
	
	if((putAnalytical-putMC)/putMC<0.001){
		cout<<"   Put test: passed"<<endl;
	}
	else{cout<<"   Put test: failed"<<endl;}
	
	
	if((digitalPutAnalytical-digitalPutMC)/digitalPutMC<0.001){
		cout<<"   Digital Put test: passed"<<endl;
	}
	else{cout<<"   Digital Put test: failed"<<endl;}
	
}



