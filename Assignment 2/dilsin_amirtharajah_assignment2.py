import re  # regular expressions


def number_check(s): # s is text
    pattern = r'^[0-9]+(\.[0-9]+)?$' # ^ start, digits, optional .digits, $ end
    return re.match(pattern, s) is not None # returns match object/none

while True: # loop
    first_input = input("Enter first number: ")  
    if number_check(first_input):                
        break                                    
    else:
        print("Error: Input must be a valid number.")  

while True:
    second_input = input("Enter second number: ")
    if number_check(second_input):
        break
    else:
        print("Error: Input must be a valid number.")

num1 = float(first_input) # convert text to decimal
num2 = float(second_input)


add_count = 0
sub_count = 0
mul_count = 0
div_count = 0
total_operations = 0
largest = 0.0


while True:

    print("\nChoose an option:\n"
          "1) Add two numbers\n"
          "2) Subtract two numbers\n"
          "3) Multiply two numbers\n"
          "4) Divide two numbers\n"
          "5) Show summary\n"
          "6) Reset summary\n"
          "7) Quit")
    choice_str = input("Choice: ")           

    if not re.match(r"^[1-7]$", choice_str): # ^ start, [1-7], $ end
        print("Error: Choice must be an integer from 1 to 7.")
        continue                              

    choice = int(choice_str) # text to number

    if choice == 1:                      
        result = num1 + num2
        print("Result:", f"{result:.2f}") # :.2f for format with 2 decimals
        add_count += 1 # increment 1
        total_operations += 1
        if result > largest:
            largest = result
    elif choice == 2:                  
        result = num1 - num2
        print("Result:", f"{result:.2f}")
        sub_count += 1
        total_operations += 1
        if result > largest:
            largest = result
    elif choice == 3:                  
        result = num1 * num2
        print("Result:", f"{result:.2f}")
        mul_count += 1
        total_operations += 1
        if result > largest:
            largest = result
    elif choice == 4:                  
        if num2 == 0:
            print("Error: Division by zero.")
        else:
            result = num1 / num2
            print("Result:", f"{result:.2f}")
            div_count += 1
            total_operations += 1
            if result > largest:
                largest = result
    elif choice == 5:                  
        print("--- Summary ---")
        print(f"Numbers entered: {num1:.2f} and {num2:.2f}")
        print(f"Total operations: {total_operations}")
        print(f"Largest result: {largest:.2f}")
        print(f"Additions: {add_count}")
        print(f"Subtraction: {sub_count}")
        print(f"Multiplications: {mul_count}")
        print(f"Divisions: {div_count}")
    elif choice == 6:                  
        add_count = 0
        sub_count = 0
        mul_count = 0
        div_count = 0
        total_operations = 0
        largest = 0.0
        print("Summary reset.")
    elif choice == 7:                  
        print("--- Summary ---")
        print(f"Numbers entered: {num1:.2f} and {num2:.2f}")
        print(f"Total operations: {total_operations}")
        print(f"Largest result: {largest:.2f}")
        print(f"Additions: {add_count}")
        print(f"Subtraction: {sub_count}")
        print(f"Multiplications: {mul_count}")
        print(f"Divisions: {div_count}")
        break   
