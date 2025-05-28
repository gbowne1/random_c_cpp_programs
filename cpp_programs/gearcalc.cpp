#include <iomanip>
#include <iostream>

class Gear{
private:
    double teeth;
    double pitch_diameter;
    double pressure_angle;
public:
    Gear(double teeth, double pitch_diameter, double pressure_angle)
        : teeth(teeth), pitch_diameter(pitch_diameter), pressure_angle(pressure_angle) {}

    double getPitchDiameter() const {
        return pitch_diameter;
    }

    double getPressureAngle() const {
        return pressure_angle;
    }

    double getTeeth() const {
        return teeth;
    }
};

int main() {
    double teeth, pitch_diameter, pressure_angle;

    std::cout << "Enter number of teeth: ";
    std::cin >> teeth;
    std::cout << "Enter pitch diameter: ";
    std::cin >> pitch_diameter;
    std::cout << "Enter pressure angle (in degrees): ";
    std::cin >> pressure_angle;

    Gear gear(teeth, pitch_diameter, pressure_angle);

    std::cout << "\nGear Specifications:\n";
    std::cout << "Number of Teeth: " << gear.getTeeth() << "\n";
    std::cout << "Pitch Diameter: " << gear.getPitchDiameter() << "\n";
    std::cout << "Pressure Angle: " << gear.getPressureAngle() << " degrees\n";

    return 0;
}