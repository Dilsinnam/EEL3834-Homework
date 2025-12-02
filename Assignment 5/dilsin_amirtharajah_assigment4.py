class Snippet:
    def __init__(self, id: int, text: str):
        self.id = id
        self.text = text

    def __repr__(self):
        return f'ID: {self.id} | "{self.text}"'

    def __add__(self, other):
        return Snippet(0, self.text + " " + other.text)

    def __lt__(self, other):
        if len(self.text) != len(other.text):
            return len(self.text) < len(other.text)
        return self.text < other.text

    def __eq__(self, other):
        return self.text == other.text


def trim(s: str) -> str:
    return s.strip()


def find_index_by_id(lst: list, id: int) -> int:
    for i, sn in enumerate(lst):
        if sn.id == id:
            return i
    return -1


def count_overlaps(text: str, sub: str) -> int:
    if sub == "":
        return 0
    count = 0
    i = 0  # index for substring
    while i + len(sub) <= len(text):
        if text[i:i + len(sub)] == sub:
            count += 1
        i += 1
    return count


def replace_nonoverlap(text: str, find_str: str, replace_str: str) -> str:
    if find_str == "":
        return text
    res = ""
    i = 0
    while i < len(text):  # iterate text
        pos = text.find(find_str, i)
        if pos == -1:
            res += text[i:]
            break
        res += text[i:pos]
        res += replace_str
        i = pos + len(find_str)
    return res


def convert_case(s: str, mode: int) -> str:
    if mode == 1:
        return s.lower()
    elif mode == 2:
        return s.upper()
    else:
        return s


def read_int():
    try:
        val = int(input().strip())  # parse int
        return val
    except Exception:
        return None


while True:
    print("Enter capacity: ", end='')
    cap = read_int()
    if cap is None:
        print("Invalid choice.")
        continue
    if cap < 1 or cap > 200:
        print("Invalid choice.")
        continue
    break

snippets = []

while True:
    print("===== Snippet Lab =====")
    print("1. Add Snippet")
    print("2. View Snippet")
    print("3. Combine Two Snippets (+)")
    print("4. Compare Two Snippets (<, ==)")
    print("5. Tools (on one Snippet)")
    print("6. Stats")
    print("7. Exit")
    print("Enter your choice: ", end='')
    choice = read_int()
    print()
    if choice is None:
        print("Invalid choice.")
        print()
        continue

    if choice == 1:
        if len(snippets) >= cap:
            print("Invalid choice.")
            print()
            continue
        while True:
            print("Enter ID: ", end='')
            nid = read_int()
            if nid is None or nid <= 0:
                print("Error: ID must be greater than 0.")
                continue
            if find_index_by_id(snippets, nid) != -1:
                print("Error: ID already exists.")
                continue
            print("Enter Text:")
            text = input()
            text = trim(text)
            if text == "":
                print("Error: Text cannot be empty.")
                continue
            if len(text) > 120:
                print("Error: Text too long (max 120).")
                print()
                break
            snippets.append(Snippet(nid, text))
            print("Snippet added!")
            print()
            break

    elif choice == 2:
        print("Enter ID: ", end='')
        vid = read_int()
        if vid is None:
            print("Error: ID not found.")
            print()
            continue
        idx = find_index_by_id(snippets, vid)
        if idx == -1:
            print("Error: ID not found.")
            print()
            continue
        print(snippets[idx])
        print()

    elif choice == 3:
        print("Enter left ID: ", end='')
        left = read_int()
        if left is None:
            print("Error: ID not found.")
            print()
            continue
        lidx = find_index_by_id(snippets, left)
        if lidx == -1:
            print("Error: ID not found.")
            print()
            continue
        print("Enter right ID: ", end='')
        right = read_int()
        if right is None:
            print("Error: ID not found.")
            print()
            continue
        ridx = find_index_by_id(snippets, right)
        if ridx == -1:
            print("Error: ID not found.")
            print()
            continue
        while True:
            print("Enter new ID for combined snippet: ", end='')
            nid = read_int()
            if nid is None or nid <= 0:
                print("Error: ID must be greater than 0.")
                continue
            if find_index_by_id(snippets, nid) != -1:
                print("Error: ID already exists.")
                continue
            combined = snippets[lidx] + snippets[ridx]
            if len(combined.text) > 120:
                print("Error: Text too long (max 120).")
                print()
                break
            combined.id = nid
            snippets.append(combined)
            print(f"Combined! New ID: {nid}")
            print()
            break

    elif choice == 4:
        print("Enter first ID: ", end='')
        a = read_int()
        if a is None:
            print("Error: ID not found.")
            print()
            continue
        aidx = find_index_by_id(snippets, a)
        if aidx == -1:
            print("Error: ID not found.")
            print()
            continue
        print("Enter second ID: ", end='')
        b = read_int()
        if b is None:
            print("Error: ID not found.")
            print()
            continue
        bidx = find_index_by_id(snippets, b)
        if bidx == -1:
            print("Error: ID not found.")
            print()
            continue
        if snippets[aidx] == snippets[bidx]:
            print("first == second")
        elif snippets[aidx] < snippets[bidx]:
            print("first < second")
        else:
            print("second < first")
        print()

    elif choice == 5:
        print("Enter ID: ", end='')
        tid = read_int()
        if tid is None:
            print("Error: ID not found.")
            print()
            continue
        tidx = find_index_by_id(snippets, tid)
        if tidx == -1:
            print("Error: ID not found.")
            print()
            continue

        while True:
            print("a) Length")
            print("b) Character at index")
            print("c) Count substring (overlaps)")
            print("d) Replace substring (all non-overlapping)")
            print("e) Trim ends")
            print("f) Case convert (1=lower, 2=upper)")
            print("g) Back")
            print("Enter choice: ", end='')
            sub = input().strip()
            if sub == "a":
                print(f"Length: {len(snippets[tidx].text)}")
            elif sub == "b":
                print("Enter index: ", end='')
                idxval = read_int()
                if idxval is None or idxval < 0 or idxval >= len(snippets[tidx].text):
                    print("Error: Index out of range.")
                    continue
                print(f"char: {snippets[tidx].text[idxval]}")
            elif sub == "c":
                print("Enter substring: ", end='')
                subq = input().rstrip("\n")
                subq = trim(subq)
                if subq == "":
                    print("Error: Text cannot be empty.")
                    continue
                cnt = count_overlaps(snippets[tidx].text, subq)
                print(f"Count: {cnt}")
            elif sub == "d":
                print("Find: ", end='')
                find_str = input().rstrip("\n")
                find_str = trim(find_str)
                print("Replace with: ", end='')
                rep_str = input().rstrip("\n")
                rep_str = trim(rep_str)
                if len(rep_str) > 120:
                    print("Error: Text too long (max 120).")
                    continue
                updated = replace_nonoverlap(snippets[tidx].text, find_str, rep_str)
                if len(updated) > 120:
                    print("Error: Text too long (max 120).")
                    continue
                snippets[tidx].text = updated
                print(f'Updated: "{snippets[tidx].text}"')
            elif sub == "e":
                snippets[tidx].text = trim(snippets[tidx].text)
                print(f'Trimmed: "{snippets[tidx].text}"')
            elif sub == "f":
                print("1=lower, 2=upper: ", end='')
                m = read_int()
                if m is None or (m != 1 and m != 2):
                    print("Invalid choice.")
                    continue
                snippets[tidx].text = convert_case(snippets[tidx].text, m)
                print(f'Converted: "{snippets[tidx].text}"')
            elif sub == "g":
                print()
                break
            else:
                print("Invalid choice.")
        print()

    elif choice == 6:
        count = len(snippets)
        total_chars = sum(len(s.text) for s in snippets)
        avg = 0.0 if count == 0 else total_chars / count
        distinct = 0
        for i in range(len(snippets)):  # count unique texts
            found = False
            for j in range(i):
                if snippets[i].text == snippets[j].text:
                    found = True
                    break
            if not found:
                distinct += 1
        print(f"Snippets: {count}")
        print(f"Total characters: {total_chars}")
        print(f"Average length: {avg:.2f}")
        print(f"Distinct texts: {distinct}")
        print()

    elif choice == 7:
        print("Goodbye!")
        print()
        break
    else:
        print("Invalid choice.")
        print()
