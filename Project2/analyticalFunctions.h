#ifndef ANALYTICAL_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define ANALYTICAL_H

#include "normal.h"

using namespace std;

double Forward(double S_0, double K, double vol, double r, double T, double q);

double ZCBond(double r, double T);

double CallOption(double S_0, double K, double vol, double r, double T, double q);

double PutOption(double S_0, double K, double vol, double r, double T, double q);

double DigitalCallOption(double S_0, double K, double vol, double r, double T, double q);

double DigitalPutOption(double S_0, double K, double vol, double r, double T, double q);

#endif
