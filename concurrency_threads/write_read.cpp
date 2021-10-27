/*
    :: Statemant ::
    Imagine you have an application where you have multiple readers and a single writer. 
    You are asked to design a lock which lets multiple readers read at the same time, but 
    only one writer write at a time.
    * Pluses in the solution:
        - A writer waits all readers finish before it starts. 
        - No new reader will started when a writer is trying to start.
    
    :: Expected output ::
        - Write events shall appear in sequence (start, finish) and belonging the same thread.
        - Reader events can appear in any order beteween them. 
*/

#include <bits/stdc++.h>
using namespace std;

mutex m1;
bool is_writing=false;
bool want_write=false;
int active_readers=0;

void sleep(int milisec){
    std::this_thread::sleep_for(std::chrono::milliseconds(milisec));
}

void reader(int id){
    while(true){
        m1.lock();       
        if(!want_write){
            active_readers++;
            m1.unlock();
            break;
        }
        m1.unlock();
    }
    
    printf("(%d) Read Start.\n", id);
    // reading ...
    printf("(%d) Read Finish.\n", id);

    m1.lock();
    active_readers--;
    m1.unlock();
}
void writer(int id){
    while(true){
        m1.lock();
        if(!want_write){
            want_write = true;
            m1.unlock();
            break;
        }
        m1.unlock();
    }

    while(active_readers > 0){}

    printf("(%d)     Write Start.\n", id);
    // writing ...
    sleep(rand()%200);
    printf("(%d)     Write Finish.\n", id);  

    m1.lock();
    want_write=false;
    m1.unlock();
}

int main(){
    int q = 20; //NUMBER OF THREADS
    srand (time(NULL));
    
    vector <thread*> v;
    while(q--){
        if(rand()%8==0) // RATIO READERS/WRITERS
            v.push_back(new thread(writer, q));
        else    
            v.push_back(new thread(reader, q));
    }
    for(int i=0; i<v.size(); i++)
        v[i]->join();
    
}