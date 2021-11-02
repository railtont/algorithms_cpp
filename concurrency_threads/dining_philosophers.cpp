/*
Statement:
    This is a classical synchronization problem proposed by Dijkstra.
    Imagine you have five philosophers sitting on a roundtable. The philosopher's do only two kinds of activities. One: they contemplate, and two: they eat. However, they have only five forks between themselves to eat their food with. Each philosopher requires both the fork to his left and the fork to his right to eat his food.
    The arrangement of the philosophers and the forks are shown in the diagram.
    Design a solution where each philosopher gets a chance to eat his food without causing a deadlock.

Solution:
    if the number of filosophers is even, then the dinner will happens in 2 times
    1 - even position philosophers dinner frist
    2 - odd position philosophers wait until yours even philosophers finishes

    if the number of filosophers is odd, then the dinner will happens in 3 times,
    we can assume that the last philosopher doesnt exist, apply the previous solution
    then in the third time the last philosopher dinner.
    1 - even position philosophers dinner frist
    2 - odd position philosophers wait until yours even philosophers finishes
        * the last odd philosoper ([seats - 2]) doest need to wait the last philosoper
    3 - after philosofers 0 and seats-2 finishes dinner, the last philosoper dines

Compilation and Execution:
    g++ dining_philosophers.cpp -o d -pthread && ./d
*/


#include <bits/stdc++.h>
using namespace std;

vector<mutex*> forks;
vector<thread*> philosophers;
vector<int> neighbor_finish_count;
mutex count_mutex;

void sleep(int milisec){std::this_thread::sleep_for(std::chrono::milliseconds(milisec));}

void increment_count(int philo_id){
    count_mutex.lock();
    neighbor_finish_count[philo_id]++;
    count_mutex.unlock();
}
void get_forks(int philo_id, int seats){
    forks[philo_id]->lock();
    forks[(philo_id+1)%seats]->lock();
}

void release_forks(int philo_id, int seats){
    forks[philo_id]->unlock();
    increment_count((philo_id + 1)%seats);
    forks[(philo_id + 1)%seats]->unlock();
    increment_count((philo_id - 1 + seats)%seats);
}


void start_dining(int philo_id, int seats){
    if(philo_id == seats -1 && seats%2==1){ //if the number of filosophers is odd, then the dinner will
        increment_count(seats-2);
        while(neighbor_finish_count[philo_id] < 2){}
        
        get_forks(philo_id, seats);
        // printf("\t\t%d Start dinner.\n", philo_id);
        sleep(1000);
        printf("\t\t%d Finish dinner.\n", philo_id);
        release_forks(philo_id, seats);
    }
    else if(philo_id%2==0){
        get_forks(philo_id, seats);
        // printf("%d Start dinner.\n", philo_id);
        sleep(1000);
        printf("%d Finish dinner.\n", philo_id);
        release_forks(philo_id, seats);
    }
    else if(philo_id%2==1){
        while(neighbor_finish_count[philo_id] < 2){}
      
        get_forks(philo_id, seats);
        // printf("\t%d Start dinner.\n", philo_id);
        sleep(1000);
        printf("\t%d Finish dinner.\n", philo_id);
        release_forks(philo_id, seats);
    }
}

int main(){
    int seats=11;
    for(int i=0; i<seats; i++){
        forks.push_back(new mutex());
        neighbor_finish_count.push_back(0); //initialization
    }

    for(int i=0; i<seats; i++)
        philosophers.push_back(new thread(start_dining,i,seats));
    for(int i=0; i<seats; i++)
        philosophers[i]->join();
    
}