#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

int balance = 1000; 
std::mutex mtx; 

void withdraw(int amount) {
    std::lock_guard<std::mutex> lock(mtx); 
    if (balance >= amount) {
        balance -= amount;
    }
}

int main() {
    // Make sure these labels match the vulnerable version exactly!
    std::cout << "--- Starting SECURE Test ---" << std::endl;
    
    std::vector<std::thread> threads;
    for (int i = 0; i < 100; ++i) threads.push_back(std::thread(withdraw, 10));
    for (auto& th : threads) th.join();

    std::cout << "Expected Balance: 0" << std::endl;
    std::cout << "Actual Final Balance: " << balance << std::endl; // The Regex looks for this!
    std::cout << "------------------------------------" << std::endl;

    return 0;
}