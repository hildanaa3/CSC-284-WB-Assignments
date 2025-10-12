#include "Truck.h"
#include <stdexcept>
#include <iomanip>

using std::cout;
using std::endl;

Truck::Truck() : Vehicle(), loadCapacityTons(1.0)
{
    cout << "[Truck ctor]\n";
}

Truck::Truck(const std::string &mk, const std::string &mdl, int yr, double mil, double capacityTons)
    : Vehicle(mk, mdl, yr, mil), loadCapacityTons(capacityTons)
{
    if (loadCapacityTons < 0.0)
        throw std::invalid_argument("Load capacity cannot be negative");
  
}

Truck::~Truck()


void Truck::setLoadCapacity(double capacityTons)
{
    if (capacityTons < 0.0)
        throw std::invalid_argument("Load capacity cannot be negative");
    loadCapacityTons = capacityTons;
}

double Truck::getFuelEfficiency() const
{
    double base = 9.0;
    if (loadCapacityTons > 5.0)
        base -= 0.1 * (loadCapacityTons - 5.0);
    if (base < 4.0)
        base = 4.0;
    return base;
}

void Truck::displayInfo() const {
    Vehicle::displayInfo();
    std::cout << "Type: Truck | Load Capacity: " << std::fixed << std::setprecision(1)
              << loadCapacityTons << " tons\n";
    std::cout << "Fuel Efficiency: " << std::fixed << std::setprecision(2)
              << getFuelEfficiency() << " km/l\n\n";
}

