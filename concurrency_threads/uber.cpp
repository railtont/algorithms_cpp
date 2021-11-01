/*
Imagine at the end of a political conference, republicans and democrats are trying to leave the venue and ordering Uber 
rides at the same time. However, to make sure no fight breaks out in an Uber ride, the software developers at Uber come 
up with an algorithm whereby either an Uber ride can have all democrats or republicans or two Democrats and two 
Republicans. All other combinations can result in a fist-fight.

Your task as the Uber developer is to model the ride requestors as threads. Once an acceptable combination of riders is 
possible, threads are allowed to proceed to ride. Each thread invokes the method seated() when selected by the system 
for the next ride. When all the threads are seated, any one of the four threads can invoke the method drive() to inform 
the driver to start the ride.

** Solution not tested, aparently the kernel is not compatible with the barrier library **
To compile: g++-10 concurrency_threads/uber.cpp -o uber -lpthread -lrt -std=c++20
*/

#include <bits/stdc++.h>
#include <semaphore.h>
#include <barrier>

using namespace std;

barrier bar(4);
mutex drive;
sem_t rep, dem;
int uber=0;

bool try_start_drive(int cnt_rep, int cnt_dem){
    if(cnt_rep == 4){
        sem_post(&rep);
        sem_post(&rep);
        sem_post(&rep);
        sem_post(&rep);
    }
    else if(cnt_dem == 4){
        sem_post(&dem);
        sem_post(&dem);
        sem_post(&dem);
        sem_post(&dem);
    }
    else if(cnt_rep >= 2 && cnt_dem >= 2){
        sem_post(&dem);
        sem_post(&dem);
        sem_post(&rep);
        sem_post(&rep);
    }
    else 
        return false;
    return true;
}

void republicans(int id){
    drive.lock();

    sem_wait(&rep);
    printf("republican joining %d\n", id);

    int cnt_rep, cnt_dem;
    cnt_rep = sem_getvalue(&rep, &cnt_rep);
    cnt_dem = sem_getvalue(&dem, &cnt_dem);
    bool leader = try_start_drive(cnt_rep, cnt_dem);

    if(!leader){
        drive.unlock();
        barrier.wait();
        printf("uber (%d) leaving with %d\n", uber_count, id);
    }
    else{
        uber_count++;
        barrier.wait();
        drive.unlock();
        printf("uber (%d) leaving %d\n", uber_count, id);
    }
}
void democrats(int id){
    drive.lock();

    sem_wait(&dem);
    printf("democrat joining %d\n", id);

    int cnt_rep, cnt_dem;
    cnt_rep = sem_getvalue(&rep, &cnt_rep);
    cnt_dem = sem_getvalue(&dem, &cnt_dem);
    bool leader = try_start_drive(cnt_rep, cnt_dem);

    if(!leader){
        drive.unlock();
        barrier.wait();
        printf("uber (%d) leaving with %d\n", uber_count, id);
    }
    else{
        uber_count++;
        barrier.wait();
        drive.unlock();
        printf("uber (%d) leaving %d\n", uber_count, id);
    }
}

int main(){
    int thread_number = 30;
    srand (time(NULL));
    sem_init(&rep, 0, 4);
    sem_init(&dem, 0, 4);

    vector <thread *> v;
    for(int i=0; i<thread_number; i++){
        if(rand()%2==0){
            v.push_back(new thread(republicans,i));
        }
        else{
            v.push_back(new thread(democrats,i));
        }
    }

    for(int i=0; i<thread_number; i++)
        v[i]->join();

    sem_destroy(&rep);
    sem_destroy(&dem);
}