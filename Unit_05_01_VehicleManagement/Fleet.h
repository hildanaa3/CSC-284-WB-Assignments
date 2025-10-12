#ifndef FLEET_H
#define FLEET_H

#include <vector>
#include "Vehicle.h"

class Fleet {
    std::vector<Vehicle*> vehicles; 

public:
    Fleet() = default;
    ~Fleet();

    void addVehicle(Vehicle* v);     
    void displayAllVehicles() const; 
    double getAverageEfficiency() const;
    std::size_t size() const { return vehicles.size(); }
};

#endif 
