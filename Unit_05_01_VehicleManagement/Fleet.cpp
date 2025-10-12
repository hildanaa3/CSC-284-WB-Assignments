#include "Fleet.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

Fleet::~Fleet() {
    cout << "[Fleet dtor] Releasing " << vehicles.size() << " vehicles\n";
    for (Vehicle* v : vehicles) delete v;
}

void Fleet::addVehicle(Vehicle* v) {
    if (v) vehicles.push_back(v);
}

void Fleet::displayAllVehicles() const {
    cout << "--- Fleet Vehicles ---\n";
    for (const Vehicle* v : vehicles) v->displayInfo();
}

double Fleet::getAverageEfficiency() const {
    if (vehicles.empty()) return 0.0;
    double sum = 0.0;
    for (const Vehicle* v : vehicles) sum += v->getFuelEfficiency();
    return sum / static_cast<double>(vehicles.size());
}
