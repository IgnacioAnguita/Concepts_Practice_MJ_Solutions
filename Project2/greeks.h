#ifndef GREEKS_H
#define GREEKS_H

double DeltaCallOption(double S_0, double K, double vol, double r, double T, double q);
double GammaCallOption(double S_0, double K, double vol, double r, double T, double q);
double VegaCallOption(double S_0, double K, double vol, double r, double T, double q);
double RhoCallOption(double S_0, double K, double vol, double r, double T, double q);
double ThetaCallOption(double S_0, double K, double vol, double r, double T, double q);

#endif
