#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void printAndWait(int count){
    auto startTime = chrono::high_resolution_clock::now(); 
    while(count--){
        cout << "Hello world from thread " << count << endl;
        this_thread::sleep_for(chrono::milliseconds(1));  // Introduce a small delay
    }
    auto stopTime = chrono::high_resolution_clock::now(); 
    auto duration = chrono::duration_cast<chrono::microseconds>(stopTime - startTime);
    cout << duration.count() << " microseconds for func" << endl;
}


int main(){

    cout<<"Before creating thread"<<endl;

    thread t1(printAndWait,10000);
    
    cout<<"After creating thread"<<endl;

    // this is done to prevent errors,
    // check if the thread is joinable 
    // as thread can be joined or detached multiple times in code by mistake 
    // causing system error

    // if(t1.joinable()) t1.join();
                // or
    if(t1.joinable()) t1.detach();
    // t1.detach means the main wants to detach or end the link of the thread with it.
    //  So the thread runs independenlty now, But the resources allocated to it are 
    // no longer managed by main. So this can cause some critical errors

    cout<<"This gets printed after t1 finishes the job, as t1.join means main waits till that line"<<endl;
    return 0;
}