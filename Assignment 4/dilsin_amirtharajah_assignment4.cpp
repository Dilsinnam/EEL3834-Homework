#include <iostream> 
#include <vector> 
#include <string> 
#include <sstream>
using namespace std; 

class Participant { // class
private:
  int id; // storing participant ID (private)
  string name; // storing participant name (private)
  string email; // storing participant email (private)
  bool feePaid; // storing  fee paid (private)
public:
  Participant() : id(0), name(""), email(""), feePaid(false) {} // basic constructor
  Participant(int i, const string& n, const string& e, bool p) : id(i), name(n), email(e), feePaid(p) {} // constructor 
  void printInfo() const { cout << "ID: " << id << " | Name: " << name << " | Email: " << email << " | Paid: " << (feePaid ? "yes" : "no") << endl; } // prints details
  int getId() const { return id; } // return id
  string getName() const { return name; } // return name 
  bool hasPaid() const { return feePaid; } // return paid
}; // end class

int findID(const vector<Participant>& v, int id) { // return index or -1
  for (size_t i = 0; i < v.size(); ++i) { // loop
    if (v[i].getId() == id) return static_cast<int>(i); // id match 
  }
  return -1; // return if not found
}

int findIndex(const vector<Participant>& v, const string& name) { // returns index or - 1
  for (size_t i = 0; i < v.size(); ++i) { // loop
    if (v[i].getName() == name) return static_cast<int>(i); // match
  }
  return -1; // return if not found
}

void sortName(vector<Participant>& v) { // sort participants
  bool swapped = true; // flag for loop
  while (swapped) { // reset pass with loop
    swapped = false; // reset swapped 
    for (size_t i = 1; i < v.size(); ++i) { // inner loop for pairs
      if (v[i - 1].getName() > v[i].getName()) { // compare names
        Participant tmp = v[i - 1]; v[i - 1] = v[i]; v[i] = tmp; // swap
        swapped = true; // swap happened = true
      }
    }
  }
}

string toLower(const string& s) { // lowercase
  string r = s; // mapped to r
  for (char& c : r) c = static_cast<char>(tolower(static_cast<unsigned char>(c))); // loop chars
  return r; // lowercase string
}

int main() { 
  vector<Participant> participants; // storing in memory
  int capacity = 0; // store maximum capacity
  string line; 

  // read and check
  while (true) { // loop until valid
    cout << "===== Event Registration System =====" << endl; 
    cout << "Enter maximum capacity (1-200): "; 
    if (!getline(cin, line)) return 0; 
    stringstream ss(line); 
    int val; // temporary int
    if (ss >> val && ss.eof()) { // check if parse succeeded
      if (val >= 1 && val <= 200) { capacity = val; break; } // if in range, correct
    }
    cout << "Invalid capacity. Try again." << endl; // error when parse failed
  }

  cout << endl; 
  
  while (true) { // repeat menu
    cout << "1. Add Participant" << endl; 
    cout << "2. Remove Participant" << endl; 
    cout << "3. Search Participant" << endl; 
    cout << "4. List Participants (Sorted by Name)" << endl; 
    cout << "5. Statistics" << endl; 
    cout << "6. Exit" << endl; 
    cout << "Enter your choice: "; 
    if (!getline(cin, line)) break; 
    stringstream ss(line); // parse choice
    int choice; 
    if (!(ss >> choice) || !(ss.eof())) { cout << endl; continue; } // invalid = reprint
    cout << endl; 

    if (choice == 1) { 
      if (static_cast<int>(participants.size()) >= capacity) { // check if full
        cout << "Error: Capacity full. Cannot add more participants." << endl << endl; 
        continue; 
      }

      int id = 0; // holder for new id
      while (true) { // loop until valid id 
        cout << "Enter ID: "; 
        if (!getline(cin, line)) return 0; // exit
        stringstream s2(line); // parse ID 
        if (s2 >> id && s2.eof()) { // parse success 
          if (id <= 0) { cout << "Error: ID must be greater than 0." << endl; continue; } // validate >0
          if (findID(participants, id) != -1) { cout << "Error: ID already exists." << endl; continue; } 
          break; 
        }
        cout << "Error: ID must be greater than 0." << endl; // parse failed 
      }

      string name; 
      while (true) { // loop until name filled
        cout << "Enter Name: "; 
        if (!getline(cin, name)) return 0; // export on fail
        if (name.empty()) { cout << "Error: Name cannot be empty." << endl; continue; } 
        break; 
      }

      string email; // holder for email
      while (true) { // loop until valid 
        cout << "Enter Email: "; 
        if (!getline(cin, email)) return 0; // exit if fail
        if (email.empty()) { cout << "Error: Email cannot be empty." << endl; continue; } // check if non empty
        if (email.find('@') == string::npos) { cout << "Error: Email must contain '@'." << endl; continue; } 
        break; // 
      }

      string paid; 
      bool fee = false; // boolean for payment
      while (true) { // loop for yes/no
        cout << "Fee Paid? (yes/no): "; 
        if (!getline(cin, paid)) return 0; // exit if fail
        string lower = toLower(paid); // lowercase
        if (lower == "yes") { fee = true; break; } // yes = true
        if (lower == "no") { fee = false; break; } // no = false
        cout << "Error: Enter 'yes' or 'no'." << endl; 
      }

      participants.emplace_back(id, name, email, fee); // add new object
      cout << "Participant added!" << endl << endl; 
    }
    else if (choice == 2) { // Remove Participant 
      cout << "Enter ID to remove: "; 
      if (!getline(cin, line)) break; // EOF 
      stringstream s(line); // parse input
      int id; // remove id
      if (!(s >> id) || !s.eof()) { cout << "Error: ID not found." << endl << endl; continue; } 
      int idx = findID(participants, id); // find index by id
      if (idx == -1) { cout << "Error: ID not found." << endl << endl; } 
      else { participants.erase(participants.begin() + idx); cout << "Participant removed!" << endl << endl; } 
    }
    else if (choice == 3) { 
      cout << "Search by (1 = ID, 2 = Name): "; 
      if (!getline(cin, line)) break; // EOF handling
      stringstream s(line); int t; // parse choice t
      if (!(s >> t) || !s.eof()) { cout << "Error: Participant not found." << endl << endl; continue; } 
      if (t == 1) { // search id
        cout << "Enter ID: "; // prompt id
        if (!getline(cin, line)) break; // EOF 
        stringstream s2(line); int id; // parse id
        if (!(s2 >> id) || !s2.eof()) { cout << "Error: Participant not found." << endl << endl; continue; } // error 
        int idx = findID(participants, id); // index
        if (idx == -1) { cout << "Error: Participant not found." << endl << endl; } // error
        else { cout << "Participant Found:" << endl; participants[idx].printInfo(); cout << endl; } // print participant
      } else if (t == 2) { 
        cout << "Enter Name: "; 
        string name; if (!getline(cin, name)) break; 
        int idx = findIndex(participants, name); 
        if (idx == -1) { cout << "Error: Participant not found." << endl << endl; } // error
        else { cout << "Participant Found:" << endl; participants[idx].printInfo(); cout << endl; } 
      } else { cout << "Error: Participant not found." << endl << endl; } 
    }
    else if (choice == 4) { 
      cout << "Sorting by name..." << endl << endl; 
      vector<Participant> copy = participants; // copy to memory
      sortName(copy); // call to sort by name
      for (size_t i = 0; i < copy.size(); ++i) { // printing participants
        cout << (i + 1) << ") " ; // print index
        copy[i].printInfo(); // print participant 
      }
      cout << endl; 
    }
    else if (choice == 5) { 
      int registered = static_cast<int>(participants.size()); 
      int paid = 0; // counter for paid
      for (const auto& p : participants) { // loop to count paid 
        if (p.hasPaid()) ++paid; // increment if paid
      }
      int unpaid = registered - paid; // find unpaid 
      cout << "Registered: " << registered << " / " << capacity << endl; 
      cout << "Paid: " << paid << endl; 
      cout << "Unpaid: " << unpaid << endl << endl; 
    }
    else if (choice == 6) { 
      cout << "Goodbye!" << endl; 
      break; 
    } else { 
      cout << endl; 
    }
  } 

  return 0; 
} 
