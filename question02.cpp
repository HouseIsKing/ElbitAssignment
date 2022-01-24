//Question 2 - threads & synchronization

//Task: Improve execution time by using multi-threading instead of calling operation1 and operation2 serially, make sure that sum=EXPECTED_SUM after using threads
// please explain the changes you made and what new aspects you had to deal with when shifting from serial execution to parallel execution 

// Make sure you compile the code in "Release" configuration (e.g O2 optimization level).
// Do not modify the constexpr variables

#include <chrono>
#include <iostream>
#include <vector>
#include <thread>

constexpr size_t ITERATIONS = 1000*1000ULL;
constexpr size_t OP1_PARAM = 2ULL;
constexpr size_t OP2_PARAM = 1ULL;
constexpr size_t EXPECTED_SUM = 1000001000000ULL;

std::atomic<size_t> sum = 0;

void operation1(size_t arg) {
	std::cout << "Performing operation1" << std::endl;
	size_t localSum = 0;
	for (size_t i = 0; i < ITERATIONS; i++) {
		localSum += (arg+i);
	}
	std::this_thread::sleep_for(std::chrono::seconds(5)); //Simulate some heavy work
	sum += localSum;
	std::cout << "Operation1 Performed" << std::endl;
}


void operation2(size_t arg) {
	std::cout << "Performing operation2" << std::endl;
	size_t localSum = 0;
	for (size_t i = 0; i < ITERATIONS; i++) {
		localSum += (arg*i);
	}
	std::this_thread::sleep_for(std::chrono::seconds(10));  //Simulate some heavy work
	sum += localSum;
	std::cout << "Operation2 Performed" << std::endl;
}
//Inital run time: 15014 mili seconds
//After modification run time: 10035 mili seconds, improvement of ~33%!(simple use of threads and atomic add)
//We can improve even more if we make each thread calculate it's value and then only add the final value to the sum.(I did it, but no improvement because 2 threads)
//Although it doesn't improve run time with 2 threads, with a lot more threads it is more likely it'll make a lot of difference.(Because of atomic add)
//New aspects to deal with: Waiting for both threads to finish, what happens if both of them reach the same memory spot and try to change it.
//It'll 'cause a corrupted value. If we're not waiting for both of them to finish of course the sum won't be correct.
int main(int argc, char** argv)
{
	auto start = std::chrono::steady_clock::now();
	std::thread thread1 (operation1,OP1_PARAM);
	std::thread thread2 (operation2,OP2_PARAM);
	thread1.join();
	thread2.join();
	auto end = std::chrono::steady_clock::now();
	std::cout << "Total execution duration in milliseconds: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
	std::cout << "Result:  " << sum <<  ", " <<(sum == EXPECTED_SUM ? "success" : "failure!")<< std::endl;
	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}