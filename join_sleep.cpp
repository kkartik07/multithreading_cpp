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
    // the main function creates thread (takes some thread creation time)
    // and the thread starts executing parallely, 
    // meanwhile the main resumes further without waiting

    cout<<"Before creating thread"<<endl;
    auto startTime = chrono::high_resolution_clock::now(); 
    thread t1(printAndWait,10000);
    // Above line creates thread and also calls the function
    auto startTime2 = chrono::high_resolution_clock::now(); 

    // This gets printed first, showing that main is also executing parallely with the thread
    cout<<(startTime2-startTime).count()<<"From main"<<endl;

    cout<<"After creating thread"<<endl;

    t1.join();
    return 0;
}