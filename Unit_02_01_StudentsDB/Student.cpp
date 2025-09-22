// Student.cpp — definition + implementation in one .cpp
#include <string>
#include <utility>

using namespace std;

class Student {
public:
    Student(int id, string name, int age, string major, string email)
        : m_id{id}, m_name{move(name)}, m_age{age}, m_major{move(major)}, m_email{move(email)} {}

    int getId() const noexcept { return m_id; }
    int getAge() const noexcept { return m_age; }
    const string& getName()  const noexcept { return m_name; }
    const string& getMajor() const noexcept { return m_major; }
    const string& getEmail() const noexcept { return m_email; }

    void setId(int id) noexcept { m_id = id; }
    void setAge(int age) noexcept { m_age = age; }
    void setName(const string& name)   { m_name  = name; }
    void setMajor(const string& major) { m_major = major; }
    void setEmail(const string& email) { m_email = email; }

private:
    int m_id{};
    string m_name;
    int m_age{};
    string m_major;
    string m_email;
};
