
// author: Pedro Ontiveros 
// date: Fri Jan  6 11:46:58 AM EST 2023

// clang++ -Wall -std=c++11 test.cc -o test
// g++ main.cpp

#include <iostream>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <stdlib.h>

using namespace std;

#define LOOP_SIZE 10

mutex m;
long id = 1;

// fnProc02 function for worker thread.
void fnProc02(void *param) 
{
    long id = (long)param;
    
    for (int i = 0; i < LOOP_SIZE; i++) {
        m.lock();
        id = i * 1;
        cout << "## fnProc02: \t\t#iteration: " << (i + 1) << " id = " << id <<" ##\n";
        m.unlock();
        sleep(1);
    }
}

// lambda function for worker thread.
auto fnProc03 = [](void *param) {
    for (int i = 0; i < LOOP_SIZE; i++) {
        m.lock();
        id = i * -1;
        cout << "@@ fnProc03: \t\t#iteration: " << (i + 1) << " id = " << id <<" @@\n";
        m.unlock();
        sleep(1);
    }
};

// Functors for worker thread.
class fnClassObject {

public:
    void operator()(void *params) {
        for (unsigned int i = 0; i < LOOP_SIZE; i++) {
            m.lock();
            id = i * 10;
            cout << "** fnClassObject: \t#iteration: " << (i + 1) << " id = " << id <<" **\n";
            m.unlock();
            sleep(1);
        } 
    }
};

// 
void runProc02() 
{
    long id = 10;
    thread t1(fnProc02, &id);
    t1.join();
}

void runProc03()
{
    unsigned long id = 20;
    thread t2(fnProc03, &id);    
    t2.join(); // Hold the main thread until t1 finishes.
}

void runProc04()
{
    unsigned long id = 30;
    thread t3(fnClassObject(), &id);
    t3.join();
}

void runProc05() 
{
    runProc02();
    runProc03();
    runProc04();
}

void runProc06() 
{
    unsigned long id2, id3, id4 = 0;
    
    thread t1(fnProc02, &id2);
    thread t3(fnClassObject(), &id4);
    thread t2(fnProc03, &id3);  
    
    t1.join();
    t2.join();
    t3.join();
}

int main(int argc, char* argv[])
{
    if (argc == 2) {
        int option = abs(atoi(argv[1])); 
    
        cout << "*** begin of main thread ***\n";
        
        switch(option) {
            case 2: runProc02(); break;
            case 3: runProc03(); break;
            case 4: runProc04(); break;
            case 5: runProc05(); break;
            case 6: runProc06(); break;
            default: 
                cout << "There is no option running.";
        } 
        
        cout << "*** end of main thread ***\n";
    } else {
        cout << "Missing argument, please try again.\n";
    }
    
    return 0;
}
