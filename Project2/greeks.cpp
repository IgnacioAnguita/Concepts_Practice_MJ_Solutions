#include "greeks.h"
#include "normal.h"
#include <math.h>
using namespace std;

double DeltaCallOption(double S_0, double K, double vol, double r, double T, double q){
	double d1;
	double b = r - q;
	d1 = (log(S_0/K) + (b+vol*vol/2)*T ) / (vol*sqrt(T));
	return CumulativeNormal(d1) * exp((b -r)*T) ;
}

double GammaCallOption(double S_0, double K, double vol, double r, double T, double q){
	double d1;
	double b = r - q;
	d1 = (log(S_0/K) + (b+vol*vol/2)*T ) / (vol*sqrt(T));
	return NormalDensity(d1) * exp((b -r)*T) / (S_0 * vol * sqrt(T)) ;
}

double VegaCallOption(double S_0, double K, double vol, double r, double T, double q){
	double d1;
	double b = r - q;
	d1 = (log(S_0/K) + (b+vol*vol/2)*T ) / (vol*sqrt(T));
	return S_0 * NormalDensity(d1) * exp((b -r)*T) * sqrt(T) ;
}

double RhoCallOption(double S_0, double K, double vol, double r, double T, double q){
	double d1, d2;
	double b = r - q;
	d1 = (log(S_0/K) + (b+vol*vol/2)*T ) / (vol*sqrt(T));
	d2 = d1 - vol * sqrt(T);
	return K * CumulativeNormal(d2) * exp(-r*T) * T ;
}

double ThetaCallOption(double S_0, double K, double vol, double r, double T, double q){
	double d1, d2;
	double b = r - q;
	d1 = (log(S_0/K) + (b+vol*vol/2)*T ) / (vol*sqrt(T));
	d2 = d1 - vol * sqrt(T);
	return - S_0 * exp((b -r)*T) * NormalDensity(d1) * vol / (2 * sqrt(T)) - (
		b-r) * S_0 * exp((b -r)*T) * CumulativeNormal(d1) - r * K * exp(-r*T) * CumulativeNormal(d2);
}
