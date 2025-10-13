#include "Motorcycle.h"
#include <iomanip>

using std::cout;
using std::endl;

Motorcycle::Motorcycle() : Vehicle(), hasSidecar(false) {}

Motorcycle::Motorcycle(const std::string &mk, const std::string &mdl, int yr, double mil, bool sidecar)
    : Vehicle(mk, mdl, yr, mil), hasSidecar(sidecar) {}

Motorcycle::~Motorcycle() {}

void Motorcycle::setHasSidecar(bool sidecar)
{
    hasSidecar = sidecar;
}

double Motorcycle::getFuelEfficiency() const
{
    return hasSidecar ? 26.0 : 30.0;
}

void Motorcycle::displayInfo() const
{
    Vehicle::displayInfo();
    cout << "Type: Motorcycle | Sidecar: " << (hasSidecar ? "Yes" : "No") << "\n";
    cout << "Fuel Efficiency: " << std::fixed << std::setprecision(2)
         << getFuelEfficiency() << " km/l\n\n";
}
