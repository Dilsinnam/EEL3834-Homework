
#include <iostream>
#include <string>
#include <cctype>
#include "Pet.h"
#include "Dog.h"
#include "Cat.h"

//  remove trail spaces from string
static std::string trim(const std::string& s) {
    size_t start = 0, end = s.size();
    while (start < end && std::isspace(static_cast<unsigned char>(s[start]))) ++start;
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) --end;
    return s.substr(start, end - start);
}

// return true only if  trimmed string is valid integer
static bool parseIntStrict(const std::string& s, int& out) {
    std::string t = trim(s);
    if (t.empty()) return false;

    size_t i = 0;
    if (t[0] == '+' || t[0] == '-') i = 1;
    if (i == t.size()) return false; // no digits

    for (; i < t.size(); ++i) {
        if (!std::isdigit(static_cast<unsigned char>(t[i]))) return false;
    }

    try {
        out = std::stoi(t);
        return true;
    } catch (...) {
        return false; // overflow 
    }
}

int main() {
    Pet* pet = nullptr;

    // Pet selection
    while (true) {
        std::cout << "Choose pet type (1=Dog, 2=Cat): ";
        std::string input;
        if (!std::getline(std::cin, input)) {
            // if fails, continue
            std::cout << "Invalid input.\n";
            continue;
        }
        int t;
        if (!parseIntStrict(input, t)) {
            std::cout << "Invalid input.\n";
            continue; 
        }
        if (t != 1 && t != 2) {
            std::cout << "Invalid choice.\n";
            continue; 
        }

        // Pet name
        std::string name;
        while (true) {
            std::cout << "Enter pet name: ";
            if (!std::getline(std::cin, name)) {
                // continue if input breaks
                std::cout << "Name cannot be empty.\n";
                continue;
            }
            std::string trimmed = trim(name);
            if (trimmed.empty()) {
                std::cout << "Name cannot be empty.\n";
                continue; 
            }
            name = trimmed; // store trimmed 
            break;
        }

        // create pet
        if (t == 1) {
            pet = new Dog(name);
        } else {
            pet = new Cat(name);
        }


        std::cout << "\n";
        break; 
    }

    bool running = true;
    while (running) {

        std::cout << "Virtual Pet\n";
        std::cout << "1. Feed pet\n";
        std::cout << "2. Play with pet\n";
        std::cout << "3. Show status\n";
        std::cout << "4. Exit\n";

        int choice = 0;
        while (true) {
            std::cout << "Enter choice: ";
            std::string line;
            if (!std::getline(std::cin, line)) {
                // input fail is invalid
                std::cout << "Invalid input.\n";
                continue; 
            }
            if (!parseIntStrict(line, choice)) {
                std::cout << "Invalid input.\n";
                continue; 
            }
            if (choice < 1 || choice > 4) {
                std::cout << "Invalid choice.\n";
                std::cout << "\n"; 
                
                choice = 0;
                break;
            }
            
            break;
        }

        if (choice == 0) {
            
            continue;
        }

        if (choice == 1) {
            // Feed pet
            int amount = 0;
            while (true) {
                std::cout << "Enter food amount (1-10): ";
                std::string amtStr;
                if (!std::getline(std::cin, amtStr)) {
                    std::cout << "Invalid input.\n";
                    continue; 
                }
                if (!parseIntStrict(amtStr, amount)) {
                    std::cout << "Invalid input.\n";
                    continue; 
                }
                if (amount < 1 || amount > 10) {
                    std::cout << "Error: amount must be between 1 and 10.\n";
                    continue; 
                }
                break; 
            }

            
            pet->feed(amount);
            std::cout << "You feed " << pet->getName() << ".\n";

            // Health check 
            if (pet->getHealth() <= 0) {
                std::cout << "Your pet's health has reached 0. Game over.\n";
                running = false;
            } else {
                
                std::cout << "\n";
            }
        } else if (choice == 2) {
            
            pet->play();
            std::cout << "You play with " << pet->getName() << ".\n";

            // health check
            if (pet->getHealth() <= 0) {
                std::cout << "Your pet's health has reached 0. Game over.\n";
                running = false;
            } else {

                std::cout << "\n";
            }
        } else if (choice == 3) {
            // show status
            pet->showStatus();
            
            std::cout << "\n";
        } else if (choice == 4) {
            
            std::cout << "Goodbye!\n";
            running = false;
        }
    }

    
    delete pet;
    return 0;
}