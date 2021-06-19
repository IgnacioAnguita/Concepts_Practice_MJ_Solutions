#include <math.h>
#include "PayOff.h"
#include <cmath>
#include <algorithm> 

using namespace std;

PayOff::PayOff(double Strike_, OptionType TheOptionsType_):
	Strike(Strike_), TheOptionsType(TheOptionsType_)
{
}

double PayOff::operator()(double spot) const
{
	switch (TheOptionsType)
	{
		case call:
			return max(spot-Strike,0.0);
		case put:
			return max(Strike-spot,0.0);
		case digitalCall:
			if (Strike<spot) {return 1.0;}	
			else {return 0.0;}				
		case digitalPut:
			if (Strike>spot) {return 1.0;}	
			else {return 0.0;}
		
	}
}
