#include "analyticalFunctions.h"

double Forward(double S_0, double K, double vol, double r, double T, double q){
	return (S_0 * exp((r-q)*T) - K)  * exp(-r * T);
}

double ZCBond(double r, double T){
	return exp(-r*T);	
}

double CallOption(double S_0, double K, double vol, double r, double T, double q){
	double d1,d2;
	double b = r - q;
	d1 = (log(S_0/K) + (b+vol*vol/2)*T ) / (vol*sqrt(T));
	d2 = d1 - vol * sqrt(T);	

	return S_0 * CumulativeNormal(d1) * exp((b -r)*T) - K * exp(-r * T) * CumulativeNormal(d2);
}

double PutOption(double S_0, double K, double vol, double r, double T, double q){
	double d1,d2;
	double b = r - q;
	d1 = (log(S_0/K) + (b+vol*vol/2)*T ) / (vol*sqrt(T));
	d2 = d1 - vol * sqrt(T);	

	return -S_0 * CumulativeNormal(-d1) * exp( (b - r)*T) + K * exp(-r * T) * CumulativeNormal(-d2);
}

double DigitalCallOption(double S_0, double K, double vol, double r, double T, double q){
	double d;
	double b = r - q;
	d = (log(S_0/K) + (b-vol*vol/2)*T ) / (vol*sqrt(T));
	return exp(-r*T)*CumulativeNormal(d);
}

double DigitalPutOption(double S_0, double K, double vol, double r, double T, double q){
	double d;
	double b = r - q;
	d = (log(S_0/K) + (b-vol*vol/2)*T ) / (vol*sqrt(T));
	return exp(-r*T)*CumulativeNormal(-d);
}
