#include "normal.h"

double NormalDensity(double x)
{
	return OneOverRootTwoPi * exp(-x*x/2);
}

double InverseCumultativeNormal(double u)
{
	static double a[4] = { 2.506628, -18.61500062529, 41.39119773534, -25.44106049};
	static double b[4] = {-8.47351093090, 23.08336743743, -21.06224101826, 3.13082909833};
	static double c[9] = {0.3374754822726147,
						0.976169,
						0.16079797,
						0.0276438810333863,
						0.00384057,
						0.00039518965119,
						0.00003217678817,
						0.0000002888167364,
						0.0000003960315187		
						};
	
	double x = u -0.5;
	double r;
	
	if (fabs(x)<0.42)
	{
		double y = x*x;
		r = x*(((a[3]*y+a[3])*y+a[1])*y+a[0])/
			((((b[3]*y+b[2])*y+b[1])*y+b[0])*y+1.0);
	}
	else
	{
		r = u;
		if (x>0.0){
			r = 1.0 -u;
		}
		
		x = log(-log(r));
		
		r = c[0] + r*(c[1]+r*(c[2]+r*(c[3]+r*(c[4]+r*(c[5]+r*(c[6]+r*(c[7]+r*c[8])))))));
		
		if (x<0.0){
			r = -r;
		}
	}
	
	return r;
}

double CumulativeNormal(double x){
	static double a[5] = {
	0.319381530,
	-0.356563782,
	1.781477937,
	-1.821255978,
	1.330274429
	};
	
	double result;
	
	if (x<-7.0) {
		result = NormalDensity(x) / sqrt(1.+x*x);
		
	}
	
	else 
	{
		if (x>7.0)
			result = 1.0 - CumulativeNormal(-x);
		else 
		{
			double tmp = 1.0 / (1.0 + 0.2316419 * fabs(x));
			result = 1 - NormalDensity(x)*
					(tmp*(a[0]+tmp*(a[1]+tmp*(a[2]+
					tmp*(a[3]+tmp*a[4])))));
			if (x<=0.0)
				result = 1.0 - result;
		}
		
	}
	return result;
}