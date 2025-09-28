def input_matrix(rows, cols): # input matrix
    mat = [] # empty list for matrix
    for i in range(rows): # loop through rows
        while True: 
            try: # convert
                row = list(map(int, input(f"Enter values for Matrix (row {i+1} of {rows}, {cols} integers separated by spaces): ").split())) # input reads row values, split splits into strings, map convert to int, list stores as list
                if len(row) != cols: # check if correct columns
                    print(f"Invalid input! Please enter exactly {cols} integers.") # error if wrong 
                else:
                    mat.append(row) # add row to matrix
                    break # exit loop 
            except ValueError: # if input is not integer
                print("Invalid input! Please enter a number.") 
    return mat # 

def print_matrix(mat): # print matrix
    for row in mat: # loop through each row
        print(*row) # print row with spaces

def add_matrix(A, B): # add matrix
    return [[A[i][j] + B[i][j] for j in range(len(A[0]))] for i in range(len(A))] # loop rows i, loop columns j, add

def subtract_matrix(A, B): # subtract matrix
    return [[A[i][j] - B[i][j] for j in range(len(A[0]))] for i in range(len(A))] # loop rows i, loop columns j, subtract

def transpose_matrix(A): # transpose matrix
    return [[A[j][i] for j in range(len(A))] for i in range(len(A[0]))] # loop columns i, loop rows j, swap

def multiply(A, scalar=2): # multiply by scalar
    return [[A[i][j] * scalar for j in range(len(A[0]))] for i in range(len(A))] # loop rows i, loop columns j, multiply

def get_input(prompt, low=None, high=None): # input
    while True: 
        try: # try convert input
            val = int(input(prompt)) # read integer
            if low is not None and high is not None: 
                if val < low or val > high: # check range
                    print(f"Invalid input! Please enter a number between {low} and {high}.") # error if out of range
                    continue # ask 
            return val # return valid integer
        except ValueError: # if not an integer
            print("Invalid input! Please enter a number.") # error message

def main(): # main 
    while True: # keep running until quit
        print("\nWelcome to the Matrix Calculator!") 

        rows = get_input("Enter number of rows (1–5): ", 1, 5) # read rows
        cols = get_input("Enter number of columns (1–5): ", 1, 5) # read columns

        print() 
        print("Enter values for Matrix A:") # ask for matrix A
        A = input_matrix(rows, cols) # input A

        print() 
        print("Enter values for Matrix B:") # ask for matrix B
        B = input_matrix(rows, cols) # input B

        print() 
        print("Choose an operation:") # menu text
        print("1. Add") # option 1
        print("2. Subtract") # option 2
        print("3. Transpose A") # option 3
        print("4. Scalar Multiply A") # option 4

        while True: # check menu choice
            try:
                choice = int(input("Your choice: ")) # read choice
                if choice not in [1, 2, 3, 4]: # check valid
                    print("Invalid input! Please enter a number between 1 and 4.") 
                else:
                    break 
            except ValueError: # not integer
                print("Invalid input! Please enter a number.") # error 

        print() 
        if choice == 1: # add
            print("Result of A + B:") 
            print_matrix(add_matrix(A, B)) 
        elif choice == 2: # subtract
            print("Result of A - B:") 
            print_matrix(subtract_matrix(A, B)) 
        elif choice == 3: # transpose
            print("Result of A^T:") 
            print_matrix(transpose_matrix(A)) 
        elif choice == 4: # multiply
            while True: 
                try:
                    s = int(input("Enter scalar value: ")) # read scalar
                    break 
                except ValueError: # not integer
                    print("Invalid input! Please enter a number.") 
            print(f"Result of {s} * A:") # result text
            print_matrix(multiply(A, s)) # print result

        print() 
        while True: 
            again = input("Would you like to try again? (y/n): ").strip().lower() 
            if again == "y": 
                break # restart 
            elif again == "n": 
                print("Thanks for using the Matrix Calculator. Goodbye!") 
                return # exit
            else: 
                print("Invalid input! Please enter 'y' for yes or 'n' for no.") # error

main() 
