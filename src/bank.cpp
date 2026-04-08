#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

int balance = 1000;

void withdraw(int amount) {
    if (balance >= amount) {
        // Sleep to ensure the race condition happens
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        balance -= amount;
    }
}

int main() {
    // If this doesn't print, the program isn't even starting
    std::cout << "--- VULNERABLE TEST STARTING ---" << std::endl;

    std::vector<std::thread> threads;
    for (int i = 0; i < 100; ++i) {
        threads.push_back(std::thread(withdraw, 10));
    }
    
    for (auto& th : threads) {
        th.join();
    }

    std::cout << "Actual Final Balance: " << balance << std::endl;
    std::cout << "--- VULNERABLE TEST FINISHED ---" << std::endl;
    
    return 0;
}

// #include <iostream>
// #include <thread>
// #include <vector>
// #include <chrono>

// // This is the shared variable that will be corrupted
// int balance = 1000; 

// void withdraw(int amount) {
//     if (balance >= amount) {
//         // Force a context switch to make the race condition happen
//         std::this_thread::sleep_for(std::chrono::milliseconds(1)); 
//         balance -= amount;
//     }
// }

// int main() {
//     std::cout << "--- Starting Race Condition Test ---" << std::endl;
    
//     std::vector<std::thread> threads;
    
//     // Launch 100 threads
//     for (int i = 0; i < 100; ++i) {
//         threads.push_back(std::thread(withdraw, 10));
//     }
    
//     // Wait for all threads to finish
//     for (auto& th : threads) {
//         th.join();
//     }

//     std::cout << "Expected Balance: 0" << std::endl;
//     std::cout << "Actual Final Balance: " << balance << std::endl;
//     std::cout << "------------------------------------" << std::endl;

//     return 0;
// }