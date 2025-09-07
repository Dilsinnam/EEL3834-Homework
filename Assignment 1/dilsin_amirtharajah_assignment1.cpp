#include <iostream>
#include <string>     // strings
#include <map>        // maps
#include <set>        // sets
#include <iomanip>    // decimals
using namespace std;  

int main() {
    string income;  
    double total_income = -1; // storing as double for checking

    while (true) {
        cout << "Enter monthly income: ";  // prompt one
        cin >> income;  // reading inputs

        try {
            total_income = stod(income);  // stod means string to double
            if (total_income < 0) {
                cout << "Error: Income must be non-negative.\n";
                continue; // prompt again
            }
            break; // income good
        } catch (invalid_argument const &e) {
            cout << "Error. Input must be a numerical value.\n";
        }
    }

    set<string> categories;  // storing categories
    map<string, double> expenses;  // storing expenses

    bool on = true;  // true/false 
    
    string user_prompt;  // storing category input
    string prompt = "Enter expense category or ('done'): "; // repeat

    while (on) {  // loop
        cout << prompt;   // prompt question
        cin >> user_prompt;  // get input from 

        
        if (user_prompt == "done") { // ending program
            on = false;  

            cout <<"\n---Budget Summary---\n";
            double total = 0.0;  // tracking total spent

            
            for (auto const &pair : expenses) { // looping expenses
                // auto = compiler checks type automatically
                // const =  no changing
                // & = making a copy
                total += pair.second;  // expense amount
            }
            
            double amount_left = total_income - total;  // money left
            int number_of_expenses = expenses.size();   // number of categories added

            double most_expense = 0.0;  // storing biggest expense
            for (auto const &pair : expenses) {  
                if (pair.second > most_expense) {
                    most_expense = pair.second;  // change if there is a bigger expense
                }
            }

            // decimals to two places
            cout << fixed << setprecision(2);
            cout << "Income: " << total_income << endl;
            cout << "Total spent: " << total << endl;
            cout << "Remaining: " << amount_left << endl;
            cout << "Expenses entered: " << number_of_expenses << endl;
            cout << "Largest expense: " << most_expense << "\n\n";

            cout << "By category: \n";
            // columns
            cout << left << setw(15) << "Category" << right << setw(10) << endl;
            for (auto const &pair : expenses) {
                cout << left << setw(15) << pair.first 
                     << right << setw(10) << fixed << setprecision(2) << pair.second << endl; // pair.first = key to category, pair.second = value of amount
            }
        } 
        else { // checking if input is all characters
            bool characters = true;  // if valid
            for (char c : user_prompt) {  // check each character
                if (!isalpha(c)) {  // if not a letter etc.
                    characters = false;
                    break;
                }
            }
            if (!characters) {
                cout << "Error: Input must be words\n";
                continue;  // back to start of loop
            }

            if (categories.find(user_prompt) != categories.end()) { // check if the category was used
                cout << "Error: Category must have a new name.\n";
                continue;  
            }

            string value;
            cout << "Enter amount: ";
            cin >> value;

            try {
                double amount_check = stod(value);  // change to double

                if (amount_check > 0) {
                    expenses[user_prompt] = amount_check;  // add to map
                    categories.insert(user_prompt);        // add to set
                } else if (amount_check < 0) {
                    cout << "Error. Expense amounts must be non-negative.\n";
                    continue;
                } else { // allow for 0 (incase)
                    expenses[user_prompt] = amount_check;
                    categories.insert(user_prompt);
                }
            } catch (invalid_argument const &e) {  // stod failure
                cout << "Error. Input must be a numerical value.\n";
                continue;
            }
        }
    }

    return 0;  // end 
}
