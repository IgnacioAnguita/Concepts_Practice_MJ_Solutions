#include <cmath>
#include <math.h> 
#include <iostream>
#include <cstdlib>
#include "normal.h"
#include "analyticalFunctions.h"
#include "test.h"
#include "PayOff.h"
#include "SimpleMC.h"
#include "investigations.h"

using namespace std;

int main(){

	Test_1();
	Test_2();
	Test_3();
	Test_4();
	Test_5();
	Test_6();
	Test_7();
	Test_8();
	investigation_1();
	investigation_2();
	investigation_3();
	investigation_4();
	TestMC();	

	return 0;
}
