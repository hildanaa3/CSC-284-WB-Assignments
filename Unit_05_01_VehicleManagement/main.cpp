#include <iostream>
#include <iomanip>
#include "Fleet.h"
#include "Car.h"
#include "Truck.h"
#include "Motorcycle.h"

using std::cout;
using std::endl;

int main()
{
    cout << "Vehicle Management System\n";
    cout << "--------------------------\n\n";

    Fleet fleet;

    try
    {

        Vehicle *c1 = new Car("Ford", "Focus", 2019, 26500.0, 4, false);
        Vehicle *t1 = new Truck("Scania", "R450", 2017, 120000.0, 22.0);
        Vehicle *m1 = new Motorcycle("Yamaha", "MT-07", 2022, 3800.0, false);
        Vehicle *c2 = new Car("Chevrolet", "Bolt EUV", 2023, 9000.0, 4, true);

        fleet.addVehicle(c1);
        fleet.addVehicle(t1);
        fleet.addVehicle(m1);
        fleet.addVehicle(c2);

        fleet.displayAllVehicles();

        cout << "Total vehicle: " << Vehicle::vehicleCount << "\n";
        cout << "Average fuel efficiency (km/l): " << std::fixed << std::setprecision(2)
             << fleet.getAverageEfficiency() << "\n\n";

        cout << "Program ending... object destructors will run now.\n";
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Initialization error: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
