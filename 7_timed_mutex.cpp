#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std;

int amount = 0;
timed_mutex mt;

// other thread can wait for 2 seconds, 
// while the current thread with mutex is performing some operation 
// and sleeping for 1 second
void print1to10(int thread_no){
    for(int i=0;i<3;i++){
        if(mt.try_lock_for(chrono::seconds(3))){
            amount++;
            this_thread::sleep_for(chrono::seconds(1));
            cout<<"Thread "<<thread_no<<" entered"<<endl;
            mt.unlock();
        }else{
            cout<<"Thread "<<thread_no<<" couldn't enter"<<endl;
        }
    }
}
int main(){

    // if mutex was acquired by t1, then t2 would keep on waiting till it frees mutex 
    // but if we used try_lock, then t2 would check mutex's availibility and not wait if not free
    // but irl, we would like t2 to wait for only sometime instead of exiting if mutex not available and instead of waiting for too long
    // for that, we make use of timed mutex
    thread t1(print1to10,1);
    thread t2(print1to10,2);
    t1.join();
    t2.join();
    cout<<amount<<endl;
}