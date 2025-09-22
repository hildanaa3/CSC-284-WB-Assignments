
#include <iostream>
#include <array>
#include <string>
#include <limits>

using namespace std;

class TrafficLight
{
public:
    enum class Color
    {
        Red = 0,
        Green = 1,
        Yellow = 2
    };

    TrafficLight() : current_(Color::Red) {}

    void step()
    {
        switch (current_)
        {
        case Color::Red:
            current_ = Color::Green;
            break;
        case Color::Green:
            current_ = Color::Yellow;
            break;
        case Color::Yellow:
            current_ = Color::Red;
            break;
        }
    }

    void run(int steps)
    {
        for (int i = 0; i < steps; ++i)
        {
            cout << toString(current_) << '\n';
            step();
        }
    }

private:
    Color current_;

    static const char *toString(Color c)
    {

        static constexpr array<const char *, 3> kNames = {"Red", "Green", "Yellow"};
        return kNames[static_cast<int>(c)];
    }
};

int readNonNegativeInt(const string &prompt)
{
    while (true)
    {
        cout << prompt;
        int value;
        if (cin >> value && value >= 0)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Please enter a non-negative integer.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main()
{
    TrafficLight light;

    int steps = readNonNegativeInt("How many steps should the light run? ");
    light.run(steps);

    return 0;
}
