#include <iostream>
#include <string>     // strings
#include <map>        // maps
#include <set>        // sets
#include <iomanip>    // decimals
#include <regex>      // expressions
using namespace std; 

bool numberCheck(const string & s) { // checking if input is a number with true/false
    regex realNumberCheck("^\\d+$"); // checking if input is numbers, however no signs
    return regex_match(s, realNumberCheck);
}

int main() {
    string firstInput; // making first variable
    while (true) {
        cout <<"Enter first number: "; // prompt one
        cin >> firstInput; // reading input
        
        if (numberCheck(firstInput)) { 
            break;
        } else {
            cout << "Error: Input must be a valid number." << endl; // error if input is not a number
            }
        }
    
    string secondInput;
    while (true) {
        cout << "Enter second number: ";
        cin >> secondInput;
        
        if (numberCheck(secondInput)) {
            break;
            } else {
                cout << "Error: Input must be a valid number." << endl;
                continue;
            }
    }
    }

