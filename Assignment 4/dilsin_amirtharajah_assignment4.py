class Participant: 
    def __init__(self, id, name, email, fee_paid): 
        self.id = id # store id
        self.name = name # store name
        self.email = email # store email
        self.fee_paid = fee_paid # store fee

    def printInfo(self): 
        print(f"ID: {self.id} | Name: {self.name} | Email: {self.email} | Paid: {'yes' if self.fee_paid else 'no'}") # print details

    def displayID(self): 
        return self.id 

    def displayName(self): 
        return self.name 

    def paidAlready(self): 
        return self.fee_paid #boolean

def indexID(lst, id): # index by id or return -1
    for i in range(len(lst)): # loop over list, checks element
        if lst[i].displayID() == id: # check id 
            return i 
    return -1 # not found

def indexName(lst, name): # index by name or return -1
    for i in range(len(lst)): # loop over list, check name
        if lst[i].displayName() == name: # check name
            return i # return if found
    return -1 # not found

def sortName(lst): # sort by name
    n = len(lst) 
    if n < 2: # less than two no sorting
        return 
    swapped = True # swapped for loop
    while swapped: # loop repeats pass until swap  
        swapped = False # reset
        for i in range(1, n): 
            if lst[i-1].displayName() > lst[i].displayName(): # compare names
                lst[i-1], lst[i] = lst[i], lst[i-1] # swap elements
                swapped = True # swap happened

def main(): 
    participants = [] # objects
    # check capacity 1 - 200
    while True: # loop until valid capacity
        try:
            capacity_str = input("===== Event Registration System =====\nEnter maximum capacity (1-200): ") 
        except EOFError:
            return 
        try:
            capacity = int(capacity_str) 
            if 1 <= capacity <= 200: # check valid range
                break 
        except:
            pass
        print("Invalid capacity. Try again.") 

    print() 

    while True: 
        print("1. Add Participant") 
        print("2. Remove Participant") 
        print("3. Search Participant") 
        print("4. List Participants (Sorted by Name)") 
        print("5. Statistics") 
        print("6. Exit") 
        try:
            choice_str = input("Enter your choice: ") 
        except EOFError:
            break 
        print() 
        try:
            choice = int(choice_str) 
        except:
            continue # if wrong reshow menu

        if choice == 1: # Add Participant
            if len(participants) >= capacity: # check capacity
                print("Error: Capacity full. Cannot add more participants.\n") # error if full
                continue

            # ID input 
            while True: # loop until valid id 
                try:
                    id_str = input("Enter ID: ") 
                except EOFError:
                    return
                try:
                    idv = int(id_str) # parse id
                    if idv <= 0:
                        print("Error: ID must be greater than 0.") 
                        continue
                    if indexID(participants, idv) != -1:
                        print("Error: ID already exists.") # checking if not already entered
                        continue
                    break
                except:
                    print("Error: ID must be greater than 0.") # if wrong error

            
            while True: # loop until non-empty
                try:
                    name = input("Enter Name: ") 
                except EOFError:
                    return
                if name.strip() == "":
                    print("Error: Name cannot be empty.") # check if non empty name
                    continue
                break

            # Email checking
            while True: # loop until valid
                try:
                    email = input("Enter Email: ") 
                except EOFError:
                    return
                if email.strip() == "":
                    print("Error: Email cannot be empty.") 
                    continue
                if "@" not in email: # check for @
                    print("Error: Email must contain '@'.") 
                    continue
                break

            # Fee paid check
            while True: # loop until yes/no
                try:
                    paid = input("Fee Paid? (yes/no): ") # read response
                except EOFError:
                    return
                if paid.lower() == "yes":
                    fee = True
                    break
                if paid.lower() == "no":
                    fee = False
                    break
                print("Error: Enter 'yes' or 'no'.") # invalid gives error

            participants.append(Participant(idv, name, email, fee)) # add new to list
            print("Participant added!\n") 

        elif choice == 2: # Remove Participant
            try:
                id_str = input("Enter ID to remove: ") # to remove
            except EOFError:
                break
            try:
                idv = int(id_str) # id
            except:
                print("Error: ID not found.\n") # parse failed
                continue
            idx = indexID(participants, idv) 
            if idx == -1:
                print("Error: ID not found.\n") 
            else:
                participants.pop(idx) # remove participant 
                print("Participant removed!\n") 

        elif choice == 3: 
            try:
                t_str = input("Search by (1 = ID, 2 = Name): ") 
            except EOFError:
                break
            try:
                t = int(t_str) 
            except:
                print("Error: Participant not found.\n") 
                continue
            if t == 1: #
                try:
                    id_str = input("Enter ID: ") 
                except EOFError:
                    break
                try:
                    idv = int(id_str) 
                except:
                    print("Error: Participant not found.\n") 
                    continue
                idx = indexID(participants, idv) 
                if idx == -1:
                    print("Error: Participant not found.\n") 
                else:
                    print("Participant Found:") 
                    participants[idx].printInfo() 
                    print()

            elif t == 2: # search name
                try:
                    name = input("Enter Name: ") # prompt name
                except EOFError:
                    break
                idx = indexName(participants, name) # find index by name
                if idx == -1:
                    print("Error: Participant not found.\n") 
                else:
                    print("Participant Found:") # found
                    participants[idx].printInfo() 
                    print() 
            else:
                print("Error: Participant not found.\n") # error

        elif choice == 4: 
            print("Sorting by name...\n") # sort by print
            copy = participants[:] 
            sortName(copy) # sort copy by name
            for i, p in enumerate(copy): # loop through  participants 
                print(f"{i+1}) ", end="") 
                p.printInfo() 
            print() 

        elif choice == 5: 
            registered = len(participants) # check registered
            paid = sum(1 for p in participants if p.paidAlready()) # count paid
            unpaid = registered - paid # unpaid count
            print(f"Registered: {registered} / {capacity}") # print registered vs capacity
            print(f"Paid: {paid}") # print paid count
            print(f"Unpaid: {unpaid}\n") 

        elif choice == 6: 
            print("Goodbye!") 
            break 

        else:
            continue # invalid menu choice errors to show menu

if __name__ == "__main__": 
    main() #
