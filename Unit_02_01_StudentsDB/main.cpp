#include <iostream>
#include <string>
#include <string_view>
#include <limits>
#include <format>

#include "StudentDatabase.cpp"  

using namespace std;

int readInt(const string& prompt) {
    while (true) {
        cout << prompt;
        int v;
        if (cin >> v) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return v;
        }
        cout << "Invalid number. Try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string readLine(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

void printHeader() {
    cout << format("{:<6}{:<22}{:<6}{:<14}{}\n",
                   "ID", "Name", "Age", "Major", "Email");
    cout << string(70, '-') << '\n';
}

void printRow(const Student& s) {
    cout << format("{:<6}{:<22}{:<6}{:<14}{}\n",
                   s.getId(), s.getName(), s.getAge(), s.getMajor(), s.getEmail());
}

int menu() {
    cout << "\nStudent Records Manager\n";
    cout << "-----------------------\n";
    cout << "1) Add Student\n";
    cout << "2) Display All Students\n";
    cout << "3) Search by ID\n";
    cout << "4) Search by Name\n";
    cout << "5) Count Students by Major\n";
    cout << "0) Exit\n";
    return readInt("---> ");
}

int main() {
    StudentDatabase db;
    bool done = false;
    while (!done) {
        switch (menu()) {
            case 0: done = true; break;
            case 1: {
                int id = readInt("ID? ");
                string name = readLine("Full name? ");
                int age = readInt("Age? ");
                string major = readLine("Major? ");
                string email = readLine("Email? ");
                db.addStudent(id, name, age, major, email);
                cout << format("Added: {} (ID {})\n", name, id);
                break;
            }
            case 2: {
                const auto& v = db.all();
                if (v.empty()) { cout << "No students yet.\n"; break; }
                printHeader();
                for (const auto& s : v) printRow(s);
                break;
            }
            case 3: {
                int id = readInt("Search ID? ");
                if (auto* s = db.getById(id)) { printHeader(); printRow(*s); }
                else cout << "Student not found.\n";
                break;
            }
            case 4: {
                string name = readLine("Search full name? ");
                if (auto* s = db.getByName(name)) { printHeader(); printRow(*s); }
                else cout << "Student not found.\n";
                break;
            }
            case 5: {
                auto counts = db.countByMajor();
                if (counts.empty()) { cout << "No students yet.\n"; break; }
                for (const auto& [m, n] : counts) cout << format("{}: {}\n", m, n);
                break;
            }
            default: cout << "Unknown option.\n"; break;
        }
    }
    cout << "Goodbye.\n";
    return 0;
}
