#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iomanip>

using namespace std;


class Snippet {
private:
    int snippet_id;
    string snippet_text;
public:
    Snippet() : snippet_id(0), snippet_text("") {} // setting snippet_id to 0 and snippet_text to nothing
    Snippet(int i, const string &t) : snippet_id(i), snippet_text(t) {} // initialize 

    int get_id() const { return snippet_id; } // getter to return the id
    const string &get_text() const { return snippet_text; }
    void set_text(const string &t) { snippet_text = t; } // setter to replace snippet

    friend ostream &operator<<(ostream &os, const Snippet &temporary_string) { // friend 
        os << "ID: " << temporary_string.snippet_id << " | \"" << temporary_string.snippet_text << "\"";
        return os;
    }

    friend Snippet operator+(const Snippet &a, const Snippet &b) { // friend
        string combined = a.snippet_text + " " + b.snippet_text; // combined
        return Snippet(0, combined);
    }
    
    friend bool operator<(const Snippet &a, const Snippet &b) {
        if (a.snippet_text.size() != b.snippet_text.size()) return a.snippet_text.size() < b.snippet_text.size(); // check by length
        return a.snippet_text < b.snippet_text;
    }

    friend bool operator==(const Snippet &a, const Snippet &b) {
        return a.snippet_text == b.snippet_text; // equal if texts equal
    }
};

// helper
static string trim(const string &temporary_string) { // for whitespace
    size_t start = 0;
    while (start < temporary_string.size() && isspace(static_cast<unsigned char>(temporary_string[start]))) ++start;
    size_t end = temporary_string.size();
    while (end > start && isspace(static_cast<unsigned char>(temporary_string[end-1]))) --end;
    return temporary_string.substr(start, end - start);
}


static int find_index_by_id(const vector<Snippet> &list, int snippet_id) {
    for (size_t i = 0; i < list.size(); ++i) { // iterating over list
        if (list[i].get_id() == snippet_id) return static_cast<int>(i);
    }
    return -1;
}


static int checking_overlaps(const string &snippet_text, const string &sub) {
    if (sub.empty()) return 0;
    int count = 0; // counter 
    for (size_t pos = 0; pos + sub.size() <= snippet_text.size(); ++pos) {
        if (snippet_text.compare(pos, sub.size(), sub) == 0) ++count; // increment 
    }
    return count;
}

// helper
static string checking_no_overlap(const string &snippet_text, const string &findStr, const string &replaceStr) {
    if (findStr.empty()) return snippet_text; //  return original if string empty
    string result;
    size_t i = 0;
    while (i < snippet_text.size()) {
        size_t pos = snippet_text.find(findStr, i);
        if (pos == string::npos) {
            result.append(snippet_text.substr(i)); // add the remainder to it
            break;
        }
        result.append(snippet_text.substr(i, pos - i));
        result.append(replaceStr); // add the replacement
        i = pos + findStr.size();
    }
    return result;
}


static string convert_the_case(const string &temporary_string, int mode) {
    string out = temporary_string; // copy original
    if (mode == 1) {
        for (size_t i = 0; i < out.size(); ++i) out[i] = static_cast<char>(tolower(static_cast<unsigned char>(out[i]))); // char to lower
    } else if (mode == 2) {
        for (size_t i = 0; i < out.size(); ++i) out[i] = static_cast<char>(toupper(static_cast<unsigned char>(out[i]))); // char to upper
    }
    return out;
}


// Modified: print a blank line after successful integer reads so the sample run spacing matches.
// helper
static bool read_the_integer(int &out) {
    if (!(cin >> out)) {
        cin.clear(); // Clear error flags
        string dummy;
        getline(cin, dummy); // Consume the invalid input
        return false;
    }
    string rest_of_line;
    getline(cin, rest_of_line); // Consume the rest of the line (e.g., newline)
    cout << endl; // <-- added to create the blank line after integer input (matches sample runs)
    return true;
}

static void read_line_trimmed(string &out) {
    string temporary_string;
    getline(cin, temporary_string); // get the full line including spaces
    out = trim(temporary_string); // trim and assign to out
}

int main() {
    int capacity = 0;
    // This is the capacity prompt you wanted to keep
    while (true) {
        cout << "Enter capacity: ";
        if (!read_the_integer(capacity)) {
            cout << "Invalid choice." << endl;
            continue;
        }
        if (capacity < 1 || capacity > 200) {
            cout << "Invalid choice." << endl;
            continue;
        }
        break;
    }

    vector<Snippet> snippets;
    snippets.reserve(static_cast<size_t>(capacity));

    while (true) {
        cout << "===== Snippet Lab =====" << endl;
        cout << "1. Add Snippet" << endl;
        cout << "2. View Snippet" << endl;
        cout << "3. Combine Two Snippets (+)" << endl;
        cout << "4. Compare Two Snippets (<, ==)" << endl;
        cout << "5. Tools (on one Snippet)" << endl;
        cout << "6. Stats" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";

        int user_choice;
        if (!read_the_integer(user_choice)) {
            cout << "Invalid choice." << endl;
            continue;
        }

        if (user_choice == 1) {
            if (static_cast<int>(snippets.size()) >= capacity) {
                cout << "Invalid choice." << endl;
                continue;
            }
            cout << "Enter ID: ";
            int new_id;
            if (!read_the_integer(new_id)) {
                cout << "Error: ID must be greater than 0." << endl;
                continue;
            }
            if (new_id <= 0) {
                cout << "Error: ID must be greater than 0." << endl;
                continue;
            }
            if (find_index_by_id(snippets, new_id) != -1) {
                cout << "Error: ID already exists." << endl;
                continue;
            }
            cout << "Enter Text: "; // Changed from "Text:" to "Text: "
            string snippet_text;
            read_line_trimmed(snippet_text);
            if (snippet_text.empty()) {
                cout << "Error: Text cannot be empty." << endl;
                continue;
            }
            if (snippet_text.size() > 120) {
                cout << "Error: Text too long (max 120)." << endl;
                continue;
            }
            snippets.emplace_back(new_id, snippet_text);
            cout << "Snippet added!" << endl;
        } else if (user_choice == 2) {
            cout << "Enter ID: ";
            int vid;
            if (!read_the_integer(vid)) {
                cout << "Error: ID not found." << endl;
                continue;
            }
            int idx = find_index_by_id(snippets, vid);
            if (idx == -1) {
                cout << "Error: ID not found." << endl;
                continue;
            }
            cout << snippets[idx] << endl;
        } else if (user_choice == 3) { // combine
            if (static_cast<int>(snippets.size()) >= capacity) { // Check capacity before combining
                cout << "Error: Not enough capacity to add combined snippet." << endl;
                continue;
            }
            cout << "Enter left ID: ";
            int left;
            if (!read_the_integer(left)) { cout << "Error: ID not found." << endl; continue; }
            int lidx = find_index_by_id(snippets, left);
            if (lidx == -1) { cout << "Error: ID not found." << endl; continue; }

            cout << "Enter right ID: ";
            int right;
            if (!read_the_integer(right)) { cout << "Error: ID not found." << endl; continue; }
            int ridx = find_index_by_id(snippets, right);
            if (ridx == -1) { cout << "Error: ID not found." << endl; continue; }

            cout << "Enter new ID for combined snippet: ";
            int new_id;
            if (!read_the_integer(new_id)) { cout << "Error: ID must be greater than 0." << endl; continue; }
            if (new_id <= 0) { cout << "Error: ID must be greater than 0." << endl; continue; }
            if (find_index_by_id(snippets, new_id) != -1) { cout << "Error: ID already exists." << endl; continue; }

            Snippet combined = snippets[lidx] + snippets[ridx];
            if (combined.get_text().size() > 120) {
                cout << "Error: Text too long (max 120)." << endl;
                continue;
            }
            combined = Snippet(new_id, combined.get_text());
            snippets.push_back(combined); // Use push_back, emplace_back is slightly different
            cout << "Combined! New ID: " << new_id << endl;
        } else if (user_choice == 4) {
            cout << "Enter first ID: ";
            int a;
            if (!read_the_integer(a)) { cout << "Error: ID not found." << endl; continue; }
            int aidx = find_index_by_id(snippets, a);
            if (aidx == -1) { cout << "Error: ID not found." << endl; continue; }

            cout << "Enter second ID: ";
            int b;
            if (!read_the_integer(b)) { cout << "Error: ID not found." << endl; continue; }
            int bidx = find_index_by_id(snippets, b);
            if (bidx == -1) { cout << "Error: ID not found." << endl; continue; }

            if (snippets[aidx] == snippets[bidx]) {
                cout << "first == second" << endl;
            } else if (snippets[aidx] < snippets[bidx]) {
                cout << "first < second" << endl;
            } else {
                cout << "second < first" << endl;
            }
        } else if (user_choice == 5) {
            cout << "Enter ID: ";
            int tid;
            if (!read_the_integer(tid)) { cout << "Error: ID not found." << endl; continue; }
            int tidx = find_index_by_id(snippets, tid);
            if (tidx == -1) { cout << "Error: ID not found." << endl; continue; }

            while (true) {
                cout << "a) Length" << endl;
                cout << "b) Character at index" << endl;
                cout << "c) Count substring (overlaps)" << endl;
                cout << "d) Replace substring (all non-overlapping)" << endl;
                cout << "e) Trim ends" << endl;
                cout << "f) Case convert (1=lower, 2=upper)" << endl;
                cout << "g) Back" << endl;
                cout << "Enter choice: "; // Renamed from "Enter user_choice: "

                string subchoice;
                getline(cin, subchoice);
                cout << endl; // <-- added so Tools submenu input produces the blank-line formatting shown in sample runs
                if (subchoice.empty()) { cout << "Invalid choice." << endl; continue; } // Renamed error
                char sc = subchoice[0];
                if (sc == 'a') {
                    cout << "Length: " << snippets[tidx].get_text().size() << endl;
                } else if (sc == 'b') {
                    cout << "Enter index: ";
                    int idxval;
                    if (!read_the_integer(idxval)) { cout << "Error: Index out of range." << endl; continue; }
                    const string &txt = snippets[tidx].get_text();
                    if (idxval < 0 || static_cast<size_t>(idxval) >= txt.size()) {
                        cout << "Error: Index out of range." << endl;
                        continue;
                    }
                    cout << "char: " << txt[idxval] << endl;
                } else if (sc == 'c') {
                    cout << "Enter substring: ";
                    string sub;
                    getline(cin, sub);
                    sub = trim(sub); // Trim the substring input
                    if (sub.empty()) { cout << "Error: Text cannot be empty." << endl; continue; }
                    int cnt = checking_overlaps(snippets[tidx].get_text(), sub);
                    cout << "Count: " << cnt << endl;
                } else if (sc == 'd') {
                    cout << "Find: ";
                    string findStr;
                    getline(cin, findStr);
                    findStr = trim(findStr);
                    cout << "Replace with: "; // Removed extra newline
                    string repStr;
                    getline(cin, repStr);
                    repStr = trim(repStr);
                    // This check needs to be on the *potential* new string, not just the replacement
                    string updated = checking_no_overlap(snippets[tidx].get_text(), findStr, repStr); // replace
                    if (updated.size() > 120) { cout << "Error: Text too long (max 120)." << endl; continue; } // check if fit
                    snippets[tidx].set_text(updated);
                    cout << "Updated: \"" << snippets[tidx].get_text() << "\"" << endl;
                } else if (sc == 'e') { // trim
                    string trimmed = trim(snippets[tidx].get_text());
                    snippets[tidx].set_text(trimmed); // update 
                    cout << "Trimmed: \"" << snippets[tidx].get_text() << "\"" << endl;
                } else if (sc == 'f') {
                    cout << "1=lower, 2=upper: "; // Removed extra newline
                    int m;
                    if (!read_the_integer(m)) { cout << "Invalid choice." << endl; continue; } // Renamed error
                    if (m != 1 && m != 2) { cout << "Invalid choice." << endl; continue; } // Renamed error
                    string conv = convert_the_case(snippets[tidx].get_text(), m);
                    snippets[tidx].set_text(conv);
                    cout << "Converted: \"" << snippets[tidx].get_text() << "\"" << endl;
                } else if (sc == 'g') {
                    break;
                } else {
                    cout << "Invalid choice." << endl; // Renamed error
                }
            }
        } else if (user_choice == 6) {
            int count = static_cast<int>(snippets.size());
            int total_chars = 0;
            for (const auto &temporary_string : snippets) total_chars += static_cast<int>(temporary_string.get_text().size());
            double avg = (count == 0) ? 0.0 : static_cast<double>(total_chars) / count;

            int distinct = 0;
            for (size_t i = 0; i < snippets.size(); ++i) {
                bool found = false; // find duplicate
                for (size_t j = 0; j < i; ++j) { // compare with others
                    if (snippets[i].get_text() == snippets[j].get_text()) { found = true; break; }
                }
                if (!found) ++distinct;
            }
            cout << "Snippets: " << count << endl;
            cout << "Total characters: " << total_chars << endl;
            cout << "Average length: " << fixed << setprecision(2) << avg << endl;
            cout << "Distinct texts: " << distinct << endl;
        } else if (user_choice == 7) {
            cout << "Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid choice." << endl; // Renamed error
        }
    }

    return 0;
}
    