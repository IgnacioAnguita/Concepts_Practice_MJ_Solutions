#include "SimpleMC3.h"
#include "Random.h"
#include <cmath>


double SimpleMonteCarlo3(double K,
						double Expiry,
						double Spot,
						double Vol,
						double r,
						unsigned long NumberOfPaths)						
{
	double variance = Vol*Vol*Expiry;
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5*variance;
	
	double movedSpot = Spot*exp(r*Expiry + itoCorrection);
	double thisSpot;
	double runningSum = 0;
	
	for(unsigned long i = 0; i < NumberOfPaths; i++){
		double thisGaussian = GetOneGaussianByBoxMuller();
		thisSpot = movedSpot * exp(rootVariance*thisGaussian);
		int indicator = 0;
		if ( thisSpot>K){
			indicator  = 1;
		}
		double thisPayOff = indicator * thisSpot/Spot;
		runningSum += thisPayOff;
	}
	
	double mean = runningSum / NumberOfPaths;
	mean *= exp(-r*Expiry);
	return mean;

}
