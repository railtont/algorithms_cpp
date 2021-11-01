/*
compile: g++-10 concurrency_threads/barrier_example.cpp -o barrier -pthread -lrt -std=c++20
    * not tested, aparently the kernel is not compatible with the barrier library
*/

#include <bits/stdc++.h>
#include <barrier>
#include <semaphore.h>

using namespace std;

barrier bar(4);
sem_t sem;

void sleep(int milisec){ std::this_thread::sleep_for(std::chrono::milliseconds(milisec));}

void f(id){
    sem_wait(&sem);
    sleep(2000);    
    bar.wait();
    printf("%d\n", id);
    sem_post(&sem);
}

int main(){
    int THREAD_NUMBER = 10;

    sem_init(&init, 0, 4);
    vector <thread *> v;
    for(int i=0; i<THREAD_NUMBER; i++){
        v.push_back(new thread(f,i));
    }
    for(int i=0; i<THREAD_NUMBER; i++){
        v[i].join();
    }
    sem_destroy(&init);
}