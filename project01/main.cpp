
// clang++ -Wall -std=c++11 test.cc -o test
// g++ main.cpp

#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

#define NUM_THREADS 5 

void *fnProc(void *param) 
{
	long value = (long)param;
	cout << "This is a new message from thread #: " << value << "\n";
	
	for (int i = 0; i < 10; i++) {
		cout << "Running task #: " << (i + 1) << "\n";
		sleep(1);
	}
}

int main(int argc, char* argv[]) 
{
	pthread_t pt;
	int value = 10;
	
	int rc = pthread_create(&pt, NULL, fnProc, (void*) value);
	sleep(5);
	
	cout << "This is the main thread finishing running.\n";
	return 0;
}
