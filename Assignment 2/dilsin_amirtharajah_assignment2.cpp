#include <iostream>   
#include <string>
#include <iomanip> // decimals
#include <regex> // for number checker
using namespace std; 

bool numberCheck(const string &s) { // pass by reference
    regex realNumberCheck("^[0-9]+(\\.[0-9]+)?$"); // ^ to start, [0-9]+ for digits, (\.[0-9]+)? for other digits
    return regex_match(s, realNumberCheck); // returns true if pass
}

int main() {

    string firstInput;  // first number
    string secondInput; // second number

    while (true) {  // loop
        cout << "Enter first number: ";        
        cin >> firstInput; // read input
        if (numberCheck(firstInput)) { // checking number
            break;                              
        } else {                                
            cout << "Error: Input must be a valid number." << endl; 
        }
    }

    
    while (true) {                              
        cout << "Enter second number: ";
        cin >> secondInput;
        if (numberCheck(secondInput)) {         
            break;
        } else {
            cout << "Error: Input must be a valid number." << endl;
        }
    }

    
    double num1 = stod(firstInput);  // string to double
    double num2 = stod(secondInput); // string to double

    
    int addCount = 0; // times add
    int subCount = 0; // times subtract
    int mulCount = 0; // times multiply
    int divCount = 0; // times divide
    int totalOperations = 0; // total operation
    double largest = 0;  // largest result

    
    while (true) { // loop
        
        cout << "\nChoose an option:\n"
             << "1) Add two numbers\n"
             << "2) Subtract two numbers\n"
             << "3) Multiply two numbers\n"
             << "4) Divide two numbers\n"
             << "5) Show summary\n"
             << "6) Reset summary\n"
             << "7) Quit\n"
             << "Choice: ";

        string choiceStr; // storing choice as text
        cin >> choiceStr;   

        regex menuCheck("^[1-7]$"); // regex for characters 1-7
        if (!regex_match(choiceStr, menuCheck)) { // regex false
            cout << "Error: Choice must be an integer from 1 to 7." << endl;
            continue;
        }

        int choice = stoi(choiceStr); // string to int
        cout << fixed << setprecision(2); // always show decimals and setprecision for 2 digits 

        
        if (choice == 1) {                      
            double result = num1 + num2; // add
            cout << "Result: " << result << endl; 
            addCount++;// increment by 1
            totalOperations++;
            if (result > largest) largest = result; // update result if biggest
        }
        else if (choice == 2) {                  
            double result = num1 - num2;
            cout << "Result: " << result << endl;
            subCount++; // increment by 1
             totalOperations++;
            if (result > largest) largest = result;
        }
        else if (choice == 3) {                  
            double result = num1 * num2;
            cout << "Result: " << result << endl;
            mulCount++; // increment by 1
            totalOperations++;
            if (result > largest) largest = result;
        }
        else if (choice == 4) {                  
            if (num2 == 0) {
                cout << "Error: Division by zero." << endl;
            } else {
                double result = num1 / num2;
                cout << "Result: " << result << endl;
                divCount++; // increment by 1
                totalOperations++;
                if (result > largest) largest = result;
            }
        }
        else if (choice == 5) {                  
            cout << "--- Summary ---" << endl;
            cout << "Numbers entered: " << num1 << " and " << num2 << endl;
            cout << "Total operations: " << totalOperations << endl;
            cout << "Largest result: " << largest << endl;
            cout << "Additions: " << addCount << endl;
            cout << "Subtraction: " << subCount << endl;
            cout << "Multiplications: " << mulCount << endl;
            cout << "Divisions: " << divCount << endl;
        }
        else if (choice == 6) {                  
            addCount = 0; // reset all to 0
            subCount = 0;
            mulCount = 0;
            divCount = 0;
            totalOperations = 0;
            largest = 0;
            cout << "Summary reset." << endl;
        }
        else if (choice == 7) {                  
            cout << "--- Summary ---" << endl;
            cout << "Numbers entered: " << num1 << " and " << num2 << endl;
            cout << "Total operations: " << totalOperations << endl;
            cout << "Largest result: " << largest << endl;
            cout << "Additions: " << addCount << endl;
            cout << "Subtraction: " << subCount << endl;
            cout << "Multiplications: " << mulCount << endl;
            cout << "Divisions: " << divCount << endl;
            break;      
        }
    }

    return 0; 
}
