#include <iostream>
#include <iomanip>
#include <vector>
#include <cstddef>
#include "Statistics.h"

using std::cout;
using std::fixed;
using std::setprecision;
using std::vector;

int main()
{
    try
    {

        Statistics<int> intStats;
        intStats.addValue(10);
        intStats.addValue(20);
        intStats.addValue(30);

        Statistics<double> doubleStats;
        doubleStats.addValue(3.14);
        doubleStats.addValue(2.71);
        doubleStats.addValue(4.5);

        cout << "Int Stats (class): Min = " << intStats.getMin()
             << ", Max = " << intStats.getMax()
             << ", Avg = " << intStats.getAverage() << "\n";

        cout << fixed << setprecision(2);
        cout << "Double Stats (class): Min = " << doubleStats.getMin()
             << ", Max = " << doubleStats.getMax()
             << ", Avg = " << doubleStats.getAverage() << "\n\n";

        vector<float> vf{1.0f, 9.5f, 3.25f, 7.0f};
        cout << "Float Stats (functions): Min = " << getMin(vf)
             << ", Max = " << getMax(vf)
             << ", Avg = " << getAverage(vf) << "\n";

        vector<long long> vll{-5, 0, 12, 100, 42};

        cout << "Long Long Stats (functions): Min = " << getMin(vll)
             << ", Max = " << getMax(vll)
             << ", Avg = " << getAverage(vll) << "\n";
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }
    return 0;
}
