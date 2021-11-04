/*
Real faNg Problem
Statement:
    Imagine we have an AsyncExecutor class that performs some useful task asynchronously
    via the method execute(). In addition, the method accepts a function object that acts
    as a callback and gets invoked after the asynchronous execution is done. The definition
    for the involved classes is below. The asynchronous work is simulated using sleep. 
    A passed-in call is invoked to let the invoker take any desired action after the 
    asynchronous processing is complete.

Compile and run: g++ concurrency_threads/asynchronous_to_synchronous_problem.cpp -o a -pthread && ./a
*/
#include <bits/stdc++.h>
using namespace std;

void sleep(int milisec){std::this_thread::sleep_for(std::chrono::milliseconds(milisec));}

mutex m;
thread *t;

class Async{
    public:
        Async(){}

        static void work(void (*func)()){
            cout << "thread init\n";
            sleep(2000);
            cout << "thread finish\n";
            func();
        }

        void execute(void (*func)()){
            t = new thread(&work, func);
            return;
        }
};

void callback(){
    cout << "running callback\n";
    m.unlock();
}

int main(){
    Async async_obj;

    m.lock();
    async_obj.execute(&callback);
    m.lock();
    cout << "finishing main proccess\n";
    t->join();
}



    // m.unlock();
    // m.lock();
    // m.lock();
    // m.unlock();