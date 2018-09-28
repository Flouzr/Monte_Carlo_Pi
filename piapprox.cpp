//π(PI) approximation using Monte Carlo simulation
//SSE Group 6
//Author: Matt Marino

#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <cmath>
#define TIMING

#ifdef TIMING
#define INIT_TIMER auto start = std::chrono::high_resolution_clock::now();
#define START_TIMER start = std::chrono::high_resolution_clock::now();
#define STOP_TIMER(dartcount, picalc)  std::cout <<  dartcount << ": " << picalc  << " RUNTIME: " << \
    std::chrono::duration_cast<std::chrono::milliseconds>( \
            std::chrono::high_resolution_clock::now()-start \
    ).count() << " ms" << std::endl; 
#else
#define INIT_TIMER
#define START_TIMER
#define STOP_TIMER(dartcount, picalc)
#endif

using namespace std;

//we are using double since float loses precision 
//and is not suitable for math operations

double doMath(int dartCount)
{
	srand(time(NULL)); //Seed the 'random' generator each time
	int circle = 0;
	for (int i = 0; i < dartCount; i++)
	{
		double x = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
		double y = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
		if (x * x + y * y <= 1.0) //Check if inside quadrant
			circle++;
	}
	
	double pi = (double) 4 * circle / dartCount; //multiply by 4 since only 1 quadrant
	return pi;
}

int main ()
{
	const int N[] = {1000, 10000, 100000, 100000000};
	for (const int &darts : N)
	{
		cout.precision(10);
		srand(time(NULL)); //Feed with 'random' data every loop
		INIT_TIMER 
		START_TIMER
		double pi = doMath(darts);
		STOP_TIMER(darts, pi) //Use chrono timer as it is more accurate than using system time
		double diff = std::abs(pi - M_PI);
		double pError = (diff / M_PI) * 100;
 		cout << fixed << " └──diff: " << diff << " [" << pError << "% error]\n"; 
	}
	return 0;
}

