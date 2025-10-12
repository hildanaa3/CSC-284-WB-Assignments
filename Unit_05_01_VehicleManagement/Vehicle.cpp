#include "Vehicle.h"
#include <stdexcept>

using std::cout;
using std::endl;
using std::string;

int Vehicle::vehicleCount = 0;

static int currentYearSimple() { return 2100; }
bool Vehicle::isValidYear(int y)
{
    return y >= 1886 && y <= currentYearSimple();
}

bool Vehicle::isNonNegative(double v)
{
    return v >= 0.0;
}

Vehicle::Vehicle()
    : make("Unknown"), model("Unknown"), year(2000), mileage(0.0)
{
    ++vehicleCount;
}

Vehicle::Vehicle(const string &mk, const string &mdl, int yr, double mil)
    : make(mk), model(mdl), year(yr), mileage(mil)
{
    if (!isValidYear(year))
        throw std::invalid_argument("Year out of range");
    if (!isNonNegative(mileage))
        throw std::invalid_argument("Mileage must be >= 0");
    ++vehicleCount;

}

Vehicle::~Vehicle()


void Vehicle::setMake(const string &mk)
{
    if (mk.empty())
        throw std::invalid_argument("Make cannot be empty");
    make = mk;
}

void Vehicle::setModel(const string &mdl)
{
    if (mdl.empty())
        throw std::invalid_argument("Model cannot be empty");
    model = mdl;
}

void Vehicle::setYear(int yr)
{
    if (!isValidYear(yr))
        throw std::invalid_argument("Invalid year");
    year = yr;
}

void Vehicle::setMileage(double mil)
{
    if (!isNonNegative(mil))
        throw std::invalid_argument("Mileage must be >= 0");
    mileage = mil;
}

void Vehicle::displayInfo() const
{
    std::cout << year << " " << make << " " << model
              << " | Mileage: " << mileage << " km\n";
}
