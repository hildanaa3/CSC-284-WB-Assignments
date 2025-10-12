#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"

class Car : public Vehicle {
    int  numDoors;
    bool isElectric;

public:
    Car();
    Car(const std::string& mk, const std::string& mdl, int yr, double mil, int doors, bool electric);
    ~Car() override;

    void setNumDoors(int doors);
    void setIsElectric(bool electric);

    int  getNumDoors()  const { return numDoors; }
    bool getIsElectric() const { return isElectric; }

    double getFuelEfficiency() const override; 
    void displayInfo() const override;
};

#endif
