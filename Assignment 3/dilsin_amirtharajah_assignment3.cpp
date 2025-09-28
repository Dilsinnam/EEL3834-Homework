#include <iostream> 
#include <vector>   
#include <limits>   // for input
using namespace std;

typedef vector<vector<int>> Matrix; // matrix type

Matrix input_matrix(int rows, int cols) { // input matrix
    Matrix mat; // empty list for matrix
    for (int i = 0; i < rows; i++) { // loop through rows
        while (true) {
            cout << "Enter values for Matrix (row " << i + 1 << " of " << rows 
                 << ", " << cols << " integers separated by spaces): ";
            Matrix temp(1); 
            temp[0].resize(cols); 
            bool valid = true; 

            for (int j = 0; j < cols; j++) {
                if (!(cin >> temp[0][j])) { // if input is not integer
                    cout << "Invalid input! Please enter a number." << endl; 
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    valid = false; 
                    break; 
                }
            }

            if (valid) { 
                mat.push_back(temp[0]); // add row to matrix
                break; 
            }
        }
    }
    return mat; 
}

void print_matrix(const Matrix &mat) { // print matrix
    for (auto &row : mat) { // loop through each row
        for (auto &val : row) cout << val << " "; 
        cout << endl;
    }
}

Matrix add_matrix(const Matrix &A, const Matrix &B) { // add matrix
    Matrix result(A.size(), vector<int>(A[0].size()));
    for (int i = 0; i < (int)A.size(); i++) // loop rows i
        for (int j = 0; j < (int)A[0].size(); j++) // loop columns j
            result[i][j] = A[i][j] + B[i][j]; // add
    return result;
}

Matrix subtract_matrix(const Matrix &A, const Matrix &B) { // subtract matrix
    Matrix result(A.size(), vector<int>(A[0].size()));
    for (int i = 0; i < (int)A.size(); i++) // loop rows i
        for (int j = 0; j < (int)A[0].size(); j++) // loop columns j
            result[i][j] = A[i][j] - B[i][j]; // subtract
    return result;
}

Matrix transpose_matrix(const Matrix &A) { // transpose matrix
    Matrix result(A[0].size(), vector<int>(A.size()));
    for (int i = 0; i < (int)A[0].size(); i++) // loop columns i
        for (int j = 0; j < (int)A.size(); j++) // loop rows j
            result[i][j] = A[j][i]; // swap
    return result;
}

Matrix multiply(const Matrix &A, int scalar = 2) { // multiply by scalar
    Matrix result(A.size(), vector<int>(A[0].size()));
    for (int i = 0; i < (int)A.size(); i++) // loop rows i
        for (int j = 0; j < (int)A[0].size(); j++) // loop columns j
            result[i][j] = A[i][j] * scalar; // multiply
    return result;
}

int get_input(string prompt, int low = -1, int high = -1) { // input
    int val;
    while (true) {
        cout << prompt;
        if (!(cin >> val)) { // try convert input
            cout << "Invalid input! Please enter a number." << endl; 
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (low != -1 && high != -1 && (val < low || val > high)) {
            cout << "Invalid input! Please enter a number between " << low << " and " << high << "." << endl; // error if out of range
        } else {
            return val; // return valid integer
        }
    }
}

void main_program() { // main 
    while (true) { // keep running until quit
        cout << "\nWelcome to the Matrix Calculator!" << endl;

        int rows = get_input("Enter number of rows (1-5): ", 1, 5); // read rows
        int cols = get_input("Enter number of columns (1-5): ", 1, 5); // read columns

        cout << "\nEnter values for Matrix A:" << endl; // ask for matrix A
        Matrix A = input_matrix(rows, cols); // input A

        cout << "\nEnter values for Matrix B:" << endl; // ask for matrix B
        Matrix B = input_matrix(rows, cols); // input B

        cout << "\nChoose an operation:" << endl; // menu text
        cout << "1. Add" << endl; // option 1
        cout << "2. Subtract" << endl; // option 2
        cout << "3. Transpose A" << endl; // option 3
        cout << "4. Scalar Multiply A" << endl; // option 4

        int choice;
        while (true) { // check menu choice
            choice = get_input("Your choice: ");
            if (choice < 1 || choice > 4) // check valid
                cout << "Invalid input! Please enter a number between 1 and 4." << endl;
            else
                break;
        }

        cout << endl;
        if (choice == 1) { // add
            cout << "Result of A + B:" << endl;
            print_matrix(add_matrix(A, B));
        } else if (choice == 2) { // subtract
            cout << "Result of A - B:" << endl;
            print_matrix(subtract_matrix(A, B));
        } else if (choice == 3) { // transpose
            cout << "Result of A^T:" << endl;
            print_matrix(transpose_matrix(A));
        } else if (choice == 4) { // multiply
            int s = get_input("Enter scalar value: ");
            cout << "Result of " << s << " * A:" << endl; // result text
            print_matrix(multiply(A, s)); // print result
        }

        cout << endl;
        while (true) {
            string again;
            cout << "Would you like to try again? (y/n): ";
            cin >> again;
            if (again == "y") {
                break; 
            } else if (again == "n") {
                cout << "Thanks for using the Matrix Calculator. Goodbye!" << endl;
                return; // exit
            } else {
                cout << "Invalid input! Please enter 'y' for yes or 'n' for no." << endl; // error
            }
        }
    }
}

int main() {
    main_program();
    return 0;
}
