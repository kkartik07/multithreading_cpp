#include <iostream>
#include <thread>
#include <chrono>
typedef long long int ull;

using namespace std;
using namespace chrono;


void findEven(ull start, ull end, ull &EvenSum) {
	for (ull i = start; i <= end; ++i){
		if (!(i & 1)){
			EvenSum += i;
		}
	}
}

void findOdd(ull start, ull end, ull &OddSum) {
	for (ull i = start; i <= end; ++i){
		if (i & 1){
			OddSum += i;
		}
	}
}

int main() {
	
	ull start = 0, end = 1900000000;

	ull OddSum = 0;
	ull EvenSum = 0;
    
    auto startTime = high_resolution_clock::now(); 

	// // WITH THREAD
    thread t1(findEven, start, end, ref(EvenSum));
    thread t2(findOdd, start, end, ref(OddSum));

	t1.join();
	t2.join();

    // ************NOTE*************
    
    // while passing by reference, we need to mention ref(var) in the list of arguments
    // mentioning that we are passing by reference

    // std::ref is designed for situations where you need to explicitly create a reference wrapper,
    //  usually in cases like passing arguments to a function object, such as when working 
    // with std::thread, std::bind, or standard library algorithms that might otherwise copy the arguments.

	// // WITHOUT THREAD
	// findEven(start,end, ref(EvenSum));
	// findOdd(start, end, ref(OddSum));
    // ********************************

    auto stopTime = high_resolution_clock::now(); 
    auto duration = duration_cast<seconds>(stopTime - startTime);

	cout << "OddSum : " << OddSum << endl;
	cout << "EvenSum : " << EvenSum << endl;

	cout << "Sec: " << duration.count() << endl;

	return 0;
}

