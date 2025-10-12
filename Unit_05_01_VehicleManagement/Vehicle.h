#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <iostream>

class Vehicle {
protected:
    std::string make;
    std::string model;
    int year;
    double mileage;

    static bool isValidYear(int y);
    static bool isNonNegative(double v);

public:
    static int vehicleCount;

    Vehicle();
    Vehicle(const std::string& mk, const std::string& mdl, int yr, double mil);
    virtual ~Vehicle();

    std::string getMake() const { return make; }
    std::string getModel() const { return model; }
    int getYear() const { return year; }
    double getMileage() const { return mileage; }


    void setMake(const std::string& mk);
    void setModel(const std::string& mdl);
    void setYear(int yr);
    void setMileage(double mil);


    virtual void displayInfo() const;
    virtual double getFuelEfficiency() const = 0;
};

#endif 
