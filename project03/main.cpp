
#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
long aux_data = 0;

#define MAX_LOOP 20

void *fnProc1(void *param)
{
	long value = (long)param;
	
	for (int i = 0; i < MAX_LOOP; i++) {
	
		pthread_mutex_lock(&count_mutex);
		aux_data = (i + 1) * 10;	
		cout << "Proc1 ["<< value << "] -> Iteration #" << (i + 1) << " value of data: " << aux_data << "\n";
		pthread_mutex_unlock(&count_mutex);
		
		if ((i % 2) == 0) {
			cout << "***\n";
			sleep(1);
		}
	}
	
	pthread_exit(NULL);
}

void *fnProc2(void *param)
{
	long value = (long)param;
	
	for (int i = 0; i < MAX_LOOP; i++) {
	
		pthread_mutex_lock(&count_mutex);
		aux_data = (i + 1) * (-20);
		cout << "Proc2 ["<< value << "] -> Iteration #" << (i + 1) << " value of data: " << aux_data << "\n";
		pthread_mutex_unlock(&count_mutex);
		sleep(1);
	}
	
	pthread_exit(NULL);
}

int main() 
{
	pthread_t id1, id2;
	
	long v1 = 1;
	long v2 = 2;
	
	cout << "*** begin of main thread ***\n";
	pthread_create(&id1, NULL, fnProc1, (void*) v1);
	pthread_create(&id2, NULL, fnProc2, (void*) v2);
		
	sleep(MAX_LOOP + 3);

	cout << "*** end of main thread ***\n";	
	return EXIT_SUCCESS;
}
