#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H

#include "Vehicle.h"

class Motorcycle : public Vehicle {
    bool hasSidecar;

public:
    Motorcycle();
    Motorcycle(const std::string& mk, const std::string& mdl, int yr, double mil, bool sidecar);
    ~Motorcycle() override;

    void setHasSidecar(bool sidecar);
    bool getHasSidecar() const { return hasSidecar; }

    double getFuelEfficiency() const override;
    void displayInfo() const override;
};

#endif
