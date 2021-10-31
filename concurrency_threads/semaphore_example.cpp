/*
compile: gcc t.cpp -o t -lpthread -lrt
*/

#include <bits/stdc++.h>
#include <semaphore.h>

using namespace std;

int THREADS_NUMBER = 4;

sem_t s;

void sleep(int milisec){ std::this_thread::sleep_for(std::chrono::milliseconds(milisec));}

void f(int id){
	sem_wait(&s);
	sleep(1000);
	cout << id << endl;
	sem_post(&s);
}

int main(){
	sem_init(&s, 0, 2);

	vector <thread *> v;
	for(int i=0; i<THREADS_NUMBER; i++){
		v.push_back(new thread(f, i));
	}
	for(int i=0; i<THREADS_NUMBER; i++)
		v[i]->join();

	sem_destroy(&s);
}