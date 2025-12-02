#include <iostream> 
#include <string>   
#include <sstream>  
#include <algorithm> 
#include <vector>
#include <climits>  
using namespace std; 

struct Entry { // structure to store the input
    int player_id;    
    int player_score; 
}; 

class high_score_class { 
public:              
    Entry* data;     // pointer to entry
    int size;
    int capacity;

    high_score_class() { // default 
        capacity = 4;                
        data = new Entry[capacity];  
        size = 0;                    
    }                                

    
    ~high_score_class() { // destructor 
        delete[] data; // delete array
    }                  

    
    high_score_class(const high_score_class& other) { // copy constructor 
        capacity = other.capacity;            
        size = other.size;                    
        data = new Entry[capacity];           // copy and new array
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i]; 
    }                                


    high_score_class& operator=(const high_score_class& other) { 
        if (this != &other) {                            
            delete[] data;                               
            capacity = other.capacity;                   // copy capacity
            size = other.size;                           // copy size
            data = new Entry[capacity];                  
            for (int i = 0; i < size; ++i)
                data[i] = other.data[i]; 
        }                                
        return *this;                    
    }

    
    int findIndexById(int player_id) const { // search function 
        for (int i = 0; i < size; ++i) { 
            if (data[i].player_id == player_id)
                return i; 
        }                 
        return -1;        
    }                     

    
    void checking_capacity_size() {             
        if (size < capacity) return;    
        int newCap = capacity * 2;      // double capacity
        Entry* newData = new Entry[newCap]; 
        for (int i = 0; i < size; ++i)
            newData[i] = data[i]; 
        delete[] data;            
        data = newData;           
        capacity = newCap;        
    }                             

    
    void addEntry(int player_id, int player_score) { // add new entry
        checking_capacity_size();              // checking capacity
        data[size].player_id = player_id;            
        data[size].player_score = player_score;      
        ++size;                        
    }                                  


    bool removeById(int player_id) { 
        int idx = findIndexById(player_id); 
        if (idx == -1) return false; 
        for (int i = idx; i + 1 < size; ++i)
            data[i] = data[i + 1]; 
        --size;
        return true;               
    }                              

   
    void updateByPointer(Entry* e, int newScore) { // update using pointer
        if (e) e->player_score = newScore;                
    }                                              

    
    void updateByReference(Entry& e, int newScore) { // update using reference
        e.player_score = newScore;
    }                                                


    void boostByPointer(Entry* e, int delta) { // boost score
        if (!e) return;                        
        long long temp = (long long)e->player_score + (long long)delta; 
        if (temp < 0) temp = 0;               // set min
        if (temp > 1000000) temp = 1000000;   // set max
        e->player_score = (int)temp;
    }

    void boostByReference(Entry& e, int delta) { // boost score by reference
        long long temp = (long long)e.player_score + (long long)delta; 
        if (temp < 0) temp = 0;                                 // set min
        if (temp > 1000000) temp = 1000000;                     // set max
        e.player_score = (int)temp;                                    
    }                                                           
}; 


pair<bool, int> try_to_parse_int(const string& s) { // parse string
    stringstream ss(s);                        
    long long tmp;                             
    if (!(ss >> tmp)) return {false, 0};       // failed 

    char c;
    if (ss >> c) return {false, 0};            // invalid if theres others
    
    if (tmp < INT_MIN || tmp > INT_MAX) return {false, 0}; 
    return {true, (int)tmp};
} 


void printMenu() { 
    cout << "High player_score Lab" << endl;
    cout << "1. Add Entry" << endl;
    cout << "2. View Entry" << endl;
    cout << "3. Update player_score" << endl;
    cout << "4. Remove Entry" << endl;
    cout << "5. Leaderboard (Top K)" << endl;
    cout << "6. Stats" << endl;
    cout << "7. Pointer Tools" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter your choice: ";
}


int main() {
    high_score_class lab;
    string line;

    while (true) {
        printMenu();
        if (!getline(cin, line)) return 0;
        auto parsed = try_to_parse_int(line);
        if (!parsed.first) {
            cout << "Invalid input." << endl << endl;
            continue;
        }
        int choice = parsed.second;

        if (choice < 1 || choice > 8) {
            cout << "Invalid choice." << endl << endl;
            continue;
        }

        if (choice == 8) {
            cout << "Goodbye!" << endl;
            break;
        }

        if (choice == 1) {
            int idVal = 0;
            while (true) {
                cout << "Enter player_id: ";
                if (!getline(cin, line)) return 0;
                auto p = try_to_parse_int(line);
                if (!p.first) {
                    cout << "Invalid input." << endl;
                    continue;
                }
                idVal = p.second;
                if (idVal <= 0) {
                    cout << "Error: player_id must be greater than 0." << endl;
                    continue;
                }
                if (lab.findIndexById(idVal) != -1) {
                    cout << "Error: player_id already exists." << endl;
                    continue;
                }
                break;
            }

            int scoreVal = 0;
            while (true) {
                cout << "Enter player_score: ";
                if (!getline(cin, line)) return 0;
                auto p = try_to_parse_int(line);
                if (!p.first) {
                    cout << "Invalid input." << endl;
                    continue;
                }
                scoreVal = p.second;
                if (scoreVal < 0 || scoreVal > 1000000) {
                    cout << "Error: player_score out of range." << endl;
                    continue;
                }
                break;
            }

            lab.addEntry(idVal, scoreVal);
            cout << "Entry added!" << endl << endl;
            continue;
        }

        if (choice == 2) {
            cout << "Enter player_id: ";
            if (!getline(cin, line)) return 0;
            auto p = try_to_parse_int(line);
            if (!p.first) {
                cout << "Invalid input." << endl << endl;
                continue;
            }
            int idVal = p.second;
            int idx = lab.findIndexById(idVal);
            if (idx == -1) {
                cout << "Error: player_id not found." << endl << endl;
                continue;
            }
            cout << "player_id: " << lab.data[idx].player_id << " | player_score: " << lab.data[idx].player_score << endl << endl;
            continue;
        }

        if (choice == 5) { 
            cout << "Enter K: ";
            if (!getline(cin, line)) return 0;
            auto p = try_to_parse_int(line);
            if (!p.first) {
                cout << "Invalid input." << endl << endl;
                continue;
            }
            int K = p.second;
            if (K <= 0) {
                cout << "Error: K must be greater than 0." << endl << endl;
                continue;
            }
            if (lab.size == 0) {
                cout << endl;
                continue;
            }

            vector<Entry> temp;
            for (int i = 0; i < lab.size; ++i)
                temp.push_back(lab.data[i]);

            sort(temp.begin(), temp.end(), [](const Entry& a, const Entry& b) {
                if (a.player_score != b.player_score)
                    return a.player_score > b.player_score;
                return a.player_id < b.player_id;
            });

            
            int toShow = std::min<int>((int)temp.size(), K);
            for (int i = 0; i < toShow; ++i)
                cout << (i + 1) << ". player_id: " << temp[i].player_id << " | player_score: " << temp[i].player_score << endl;

            cout << endl;
            continue;
        }
    }
    return 0;
}
