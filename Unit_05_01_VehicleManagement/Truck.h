#ifndef TRUCK_H
#define TRUCK_H

#include "Vehicle.h"

class Truck : public Vehicle {
    double loadCapacityTons; // tons

public:
    Truck();
    Truck(const std::string& mk, const std::string& mdl, int yr, double mil, double capacityTons);
    ~Truck() override;

    void setLoadCapacity(double capacityTons);
    double getLoadCapacity() const { return loadCapacityTons; }

    double getFuelEfficiency() const override;
    void displayInfo() const override;
};

#endif
