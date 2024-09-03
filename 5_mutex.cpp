#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex m;

int sharedVariable=0;
void inc(int step){
    for(int i=0;i<100000;i++){
        m.lock();
        sharedVariable=sharedVariable+step;
        m.unlock();
    }
    return;
}
int main(){

    cout<<sharedVariable<<endl;

    std::thread t1(inc,1);
    std::thread t2(inc,1);

    t1.join();
    t2.join();

    cout<<sharedVariable<<endl;
    return 0;
}
