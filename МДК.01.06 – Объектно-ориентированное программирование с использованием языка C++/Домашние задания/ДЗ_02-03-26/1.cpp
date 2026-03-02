#include <iostream>
#include <string>

class Car {
private:
    std::string model;
    int fuelLevel;

public:
    Car(std::string m, int fuel) {
        model = m;
        fuelLevel = fuel;
    }

    void drive(int distance) {
        if (fuelLevel >= distance) {
            fuelLevel -= distance;
            std::cout << model << " проехала " << distance << " км. Остаток топлива: " << fuelLevel << std::endl;
        } else {
            std::cout << model << " не может проехать " << distance << " км. Недостаточно топлива!" << std::endl;
        }
    }

    void refuel(int amount) {
        fuelLevel += amount;
        std::cout << model << " заправлена на " << amount << " ед. Текущий уровень топлива: " << fuelLevel << std::endl;
    }

    void getFuel() {
        std::cout << model << " уровень топлива: " << fuelLevel << std::endl;
    }
};

int main() {
    Car car1("Toyota", 50);
    Car car2("BMW", 30);

    car1.getFuel();
    car2.getFuel();

    car1.drive(20);
    car2.drive(40);

    car1.refuel(10);
    car2.refuel(5);

    car1.getFuel();
    car2.getFuel();

    return 0;
}
