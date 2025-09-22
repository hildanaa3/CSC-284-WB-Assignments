// StudentDatabase.cpp — includes Student.cpp directly (no headers)
#include <vector>
#include <string>
#include <string_view>
#include <unordered_map>

#include "Student.cpp"  // intentionally included so we have the full type here

using namespace std;

class StudentDatabase {
public:
    Student& addStudent(int id, const string& name, int age,
                        const string& major, const string& email) {
        students.emplace_back(id, name, age, major, email);
        return students.back();
    }

    Student* getById(int id) {
        for (auto& s : students) if (s.getId() == id) return &s;
        return nullptr;
    }

    Student* getByName(string_view fullName) {
        for (auto& s : students) {
            string_view sv{s.getName()};
            if (sv == fullName) return &s;
        }
        return nullptr;
    }

    const vector<Student>& all() const noexcept { return students; }

    unordered_map<string,int> countByMajor() const {
        unordered_map<string,int> counts;
        for (const auto& s : students) counts[s.getMajor()]++;
        return counts;
    }

private:
    vector<Student> students;
};
