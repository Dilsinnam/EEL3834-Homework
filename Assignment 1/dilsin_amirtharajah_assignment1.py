income = input("Enter monthly income: ") # opening statement
prompt = ("Enter expense category or ('done'): ") # second statement
categories = set() # making a set to store
expenses = {} # making a dictionary to store
on = True
while on:
    user_prompt = input(prompt)

    if user_prompt.lower() == 'done':
        on = False

        print("---Budget Summary---")
        income_total = float(income) # making income decimals
        total = sum(expenses.values()) # adding the values of expenses
        remaining_amount = income_total - total # subtracting
        expense_amount = len(expenses) # check number of items
        big_expense = max(expenses.values()) if expenses else 0 # largest expense

        # printing to two decimal places
        print(f"Income:  {income_total: .2f}")
        print(f"Total spent:  {total: .2f}")
        print(f"Remaining:  {remaining_amount: .2f}")
        print(f"Expenses entered:  {expense_amount: .2f}")
        print(f"Largest expense:  {big_expense: .2f}\n")
        
        print("By category: ")
        for cat, amt in expenses.items():
            print(f"{cat} {amt:.2f}")

    else:
        try:
            prompt_check = user_prompt.isalpha() # checking if input is words only
            if not prompt_check:
                print("Error: Input must be a word(s).")
                continue # go back to prompt 

            if user_prompt in categories: # checking if the input was used already
                print("Error: Category must have a new name.")
                continue # go back to prompt

            value = input("Enter amount: ") # third statement
            value_check = float(value) # checking if input is numbers only
            if value_check > 0: #checking if value is greater than 0
                expenses[user_prompt] = value_check # adding value to dictionary
                categories.add(user_prompt)  # only add to categories when valid
            elif value_check < 0: # checking if value is less than 0
                print("Error. Expense amounts must be non-negative.")
                continue
            else:
                # allow 0, but add
                expenses[user_prompt] = value_check
                categories.add(user_prompt)
        except ValueError:
            print("Error. Input must be a numerical value.")
            continue # go back to prompt
