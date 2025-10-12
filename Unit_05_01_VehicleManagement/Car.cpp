#include "Car.h"
#include <stdexcept>
#include <iomanip>

using std::cout;
using std::endl;

Car::Car() : Vehicle(), numDoors(4), isElectric(false)
{
    cout << "[Car ctor]\n";
}

Car::Car(const std::string &mk, const std::string &mdl, int yr, double mil, int doors, bool electric)
    : Vehicle(mk, mdl, yr, mil), numDoors(doors), isElectric(electric)
{
    if (numDoors <= 0)
        throw std::invalid_argument("Number of doors must be positive");
    
}

Car::~Car()


void Car::setNumDoors(int doors)
{
    if (doors <= 0)
        throw std::invalid_argument("Number of doors must be positive");
    numDoors = doors;
}

void Car::setIsElectric(bool electric) { isElectric = electric; }

double Car::getFuelEfficiency() const
{
    if (isElectric)
        return 0.0;
    double base = 15.0;
    return (numDoors > 4) ? (base - 1.0) : base;
}

void Car::displayInfo() const
{
    Vehicle::displayInfo();
    cout << "Category: Car | Doors: " << numDoors
         << " | Electric: " << (isElectric ? "Yes" : "No") << "\n";
    cout << "Estimated Efficiency: ";
    if (isElectric)
    {
        cout << "N/A (electric)\n\n";
    }
    else
    {
        cout << std::fixed << std::setprecision(1)
             << getFuelEfficiency() << " km/l\n\n";
    }
}
