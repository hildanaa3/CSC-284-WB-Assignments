#ifndef FLEET_H
#define FLEET_H

#include <vector>
#include "Vehicle.h"

class Fleet {
    std::vector<Vehicle*> vehicles; // aggregation; owns pointers

public:
    Fleet() = default;
    ~Fleet();

    void addVehicle(Vehicle* v);     // takes ownership
    void displayAllVehicles() const; // polymorphic dispatch
    double getAverageEfficiency() const;
    std::size_t size() const { return vehicles.size(); }
};

#endif // FLEET_H
