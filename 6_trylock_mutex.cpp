#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>


using namespace std;

mutex m;

int sharedVariable=0;
void inc(int step){
    for(int i=0;i<100000;i++){
        // try_lock checks if the mutex can be gained, if not it will skips instead of waiting unlike
        //  in .lock()

        // it saves time by not blocking the thread
        if(m.try_lock()){
            sharedVariable=sharedVariable+step;
            m.unlock();
        }
    }
    return;
}

int main(){

    auto start = chrono::high_resolution_clock::now();
    cout<<sharedVariable<<endl;

    std::thread t1(inc,1);
    std::thread t2(inc,1);

    t1.join();
    t2.join();
    auto end = chrono::high_resolution_clock::now();

    // if we use try_lock (non blocking) we finish everything in about 12549145 units of time
    // while
    // if we use lock directly we take about 26580868 units of time
    //  to complete as it is blocking and keeps on waiting
    cout<<"time "<<(end-start).count()<<endl;
    cout<<sharedVariable<<endl;
    return 0;
}
