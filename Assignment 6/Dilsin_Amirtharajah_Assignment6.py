capacity = 4  # initial capacity 
data_version_one = [None] * capacity  
size = 0  # entry starting

def try_to_parse_int(s):  # to parse string
    try:  
        val = int(s.strip())
        return True, val  # removing whitespace and return
    except:  
        return False, 0  # failed

# to find index
def find_index_by_id(id_val):  
    global size, data_version_one  # look at global size, data
    for i in range(size):  
        if data_version_one[i]['id'] == id_val:  # check if it matches
            return i  
    return -1  

def checking_capacity():  # checking to see if theres more room for more entries
    global capacity, data_version_one, size  # looking at globals
    if size < capacity:  # space = do nothing
        return
    new_capacity = capacity * 2  
    updated_data = [None] * new_capacity  # new list
    for i in range(size): 
        updated_data[i] = data_version_one[i]  
    data_version_one = updated_data  # replacing the old data with updated_data
    capacity = new_capacity  # update capacity

def add_entry_to_storage(id_val, score_val):  # to add an entry to storage
    global size, data_version_one  # looking at globals
    checking_capacity()  # calling the checker 
    data_version_one[size] = {'id': id_val, 'score': score_val}  # stored in dict
    size += 1  

def remove_entry_by_id(id_val):  # used to remove an entry from storage
    global size, data_version_one  # looking at globals
    idx = find_index_by_id(id_val)  
    if idx == -1:  
        return False  

    for i in range(idx, size - 1):
        data_version_one[i] = data_version_one[i + 1]  # shift left
    data_version_one[size - 1] = None  # clear last 
    size -= 1  # decrement 
    return True  

def update_by_pointer(idx, new_score):  
    global data_version_one  # looking at global data var
    if idx >= 0:
        data_version_one[idx]['score'] = new_score  

def update_by_reference(entry, new_score):  
    entry['score'] = new_score  

def boost_by_pointer(idx, delta):  # boost through pointer
    global data_version_one  # looking at globals
    if idx < 0:
        return
    temp = data_version_one[idx]['score'] + delta  # get the new value
    if temp < 0:  # set the lower bound
        temp = 0
    if temp > 1000000:  # set the upper bound
        temp = 1000000
    data_version_one[idx]['score'] = temp  

def boost_by_reference(entry, delta):  # boost through reference
    temp = entry['score'] + delta  
    if temp < 0:  # lower bound
        temp = 0
    if temp > 1000000:  # upper bound
        temp = 1000000
    entry['score'] = temp  


def print_menu(): 
    print("High Score Lab") 
    print("1. Add Entry") 
    print("2. View Entry")  
    print("3. Update Score")  
    print("4. Remove Entry") 
    print("5. Leaderboard (Top K)")  
    print("6. Stats")  
    print("7. Pointer Tools") 
    print("8. Exit")  
    print("Enter your choice: ", end='')  


def main():  
    global size, capacity, data_version_one  # get globals
    while True:  
        print_menu()  
        try:
            line = input()  
        except EOFError:
            return  # added just incase of console input, i had issues with the last assignment with it
        ok, val = try_to_parse_int(line)  
        if not ok:  
            print("Invalid input.")  
            print()  
            continue  
        choice = val  
        if choice < 1 or choice > 8:  
            print("Invalid choice.")  
            print()  
            continue  

        if choice == 8:  
            print("Goodbye!")  
            return  

        if choice == 1:  
            
            while True:
                print("Enter ID: ", end='')  
                try:
                    line = input()  
                except EOFError:
                    return
                ok, id_value = try_to_parse_int(line)  
                if not ok:  
                    print("Invalid input.")  
                    continue
                if id_value <= 0:  
                    print("Error: ID must be greater than 0.")  
                    continue  
                if find_index_by_id(id_value) != -1:  
                    print("Error: ID already exists.")  
                    continue  
                break  

            
            while True:
                print("Enter Score: ", end='')
                try:
                    line = input()
                except EOFError:
                    return
                ok, sval = try_to_parse_int(line)
                if not ok:
                    print("Invalid input.")  
                    continue  
                if sval < 0 or sval > 1000000:
                    print("Error: Score out of range.")  
                    continue  
                break  

            add_entry_to_storage(id_value, sval)  
            print("Entry added!")  
            print()  
            continue  

        if choice == 2:  
            print("Enter ID: ", end='')  
            try:
                line = input()
            except EOFError:
                return
            ok, id_value = try_to_parse_int(line)  
            if not ok:
                print("Invalid input.")  
                print()  
                continue  
            idx = find_index_by_id(id_value)  
            if idx == -1:
                print("Error: ID not found.")  
                print()  
                continue  
            print(f"ID: {data_version_one[idx]['id']} | Score: {data_version_one[idx]['score']}")  
            print()  
            continue  

        if choice == 3:  
            print("Enter ID: ", end='')  
            try:
                line = input()
            except EOFError:
                return
            ok, id_value = try_to_parse_int(line)  
            if not ok:
                print("Invalid input.")  
                print()  
                continue

            print("Enter new Score: ", end='')  
            try:
                line = input()
            except EOFError:
                return
            ok, newscore = try_to_parse_int(line)  
            if not ok:
                print("Invalid input.")  
                print()  
                continue

           
            while True:
                print("Method (1=pointer, 2=reference): ", end='')  
                try:
                    line = input()
                except EOFError:
                    return
                ok, method = try_to_parse_int(line)  
                if not ok or (method != 1 and method != 2):  
                    print("Invalid choice.")  
                    continue  
                break  

            idx = find_index_by_id(id_value)  # check if exists
            if idx == -1:
                print("Error: ID not found.")  
                print()  
                continue

            if newscore < 0 or newscore > 1000000:  
                print("Error: Score out of range.")  
                print()  
                continue


            if method == 1:
                update_by_pointer(idx, newscore)  # pointer update
            else:
                update_by_reference(data_version_one[idx], newscore)  # reference update

            print("Updated.")  
            print()  
            continue  

        if choice == 4:  
            
            while True:
                print("Enter ID: ", end='')  
                try:
                    line = input()
                except EOFError:
                    return
                ok, id_value = try_to_parse_int(line)  
                if not ok:
                    print("Invalid input.")  
                    continue  
                if not remove_entry_by_id(id_value):  
                    print("Error: ID not found.")  
                    continue  
                print("Removed.")  
                print()  
                break  
            continue  

        if choice == 5:
            print("Enter K: ", end='')  
            try:
                line = input()
            except EOFError:
                return
            ok, k = try_to_parse_int(line) 
            if not ok:
                print("Invalid input.")  
                print()  
                continue  
            if k <= 0:
                print("Error: K must be greater than 0.")  
                print()  
                continue  
            if size == 0:  
                print()  
                continue  

            temp = []  
            for i in range(size):
                temp.append({'id': data_version_one[i]['id'], 'score': data_version_one[i]['score']})  # copy
            
            temp.sort(key=lambda e: (-e['score'], e['id']))  
            to_show = min(len(temp), k)  
            for i in range(to_show):
                print(f"{i+1}. ID: {temp[i]['id']} | Score: {temp[i]['score']}")  
            print()  
            continue  

        if choice == 6:  
            total = 0
            for i in range(size):
                total += data_version_one[i]['score']
            avg = 0.0  
            if size > 0:
                avg = total / size  
            
            print(f"Entries: {size}")  
            print(f"Total score: {total}")  
            print("Average score: {0:.2f}".format(avg))  
            print(f"Capacity: {capacity}")  
            print()  
            continue  

        if choice == 7:  
            while True:
                print("a) Boost by pointer")  
                print("b) Boost by reference")  
                print("c) Back")  
                print("Enter choice: ", end='')  
                try:
                    line = input()
                except EOFError:
                    return
                if line not in ('a', 'b', 'c'):  
                    print("Invalid choice.")  
                    continue  
                if line == 'c':  
                    print()  
                    break  
                print("Enter ID: ", end='')  
                try:
                    line = input()
                except EOFError:
                    return
                ok, id_value = try_to_parse_int(line)  
                if not ok:
                    print("Invalid input.")  
                    continue  
                idx = find_index_by_id(id_value)  
                if idx == -1:
                    print("Error: ID not found.")  
                    continue  
                print("Enter delta: ", end='')  
                try:
                    line = input()
                except EOFError:
                    return
                ok, delta = try_to_parse_int(line)  
                if not ok:
                    print("Invalid input.")
                    continue  
                if line == 'a':  
                    boost_by_pointer(idx, delta) # call boost
                    print("Boosted.")
                    continue  
                else:  
                    boost_by_reference(data_version_one[idx], delta)  # call reference
                    print("Boosted.")  
                    continue  

if __name__ == "__main__":
    main()  
