#include <iostream>
#include <cstring> 
#include <cstdlib>
#include <ctime>

using namespace std;

class Engine {
private:
    double speed;
    double temperature;
public:
    Engine(double s = 0.0, double t = 20.0) : speed(s), temperature(t) {}
    void setSpeed(double s) { speed = s; }
    double getSpeed() const { return speed; }
    void show() const { cout << "[ Speed: " << speed << " rpm, Temperature: " << temperature << " °C ]" << endl; }
};

class Controller {
private:
    double targetSpeed;
    double timer;
public:
    Controller(double s = 0.0, double t = 0.0) : targetSpeed(s), timer(t) {}
    void setTargetSpeed(double s) { targetSpeed = s; }
    void setTimer(double t) { timer = t; }
    double getTargetSpeed() const { return targetSpeed; }
    double getTimer() const { return timer; }
    void show() const { cout << "[ Target speed: " << targetSpeed << " rpm, Timer: " << timer << " sec ]" << endl; }
};

class Remote {
private:
    double speedSetting;
    double timeSetting;
public:
    Remote(double s = 0.0, double t = 0.0) : speedSetting(s), timeSetting(t) {}
    double getSpeed() const { return speedSetting; }
    double getTime() const { return timeSetting; }
    void show() const { cout << "[ Remote -> Speed: " << speedSetting << ", Time: " << timeSetting << " ]" << endl; }
};


class Fan {
private:
    Engine engine;
    Controller controller;
    Remote remote;
    char* name;

    void initializeName(const char* fanName) {
        size_t len = strlen(fanName);
        name = new char[len + 1];
        strcpy_s(name, len + 1, fanName);
    }

public:
    ~Fan() { delete[] name; }

    Fan() : engine(), controller(), remote(), name(nullptr) {
        initializeName("Bosch");
    }

    Fan(const Engine& e, const Controller& c, const Remote& r)
        : engine(e), controller(c), remote(r), name(nullptr) {
        initializeName("Bosch");
    }

    Fan(const Fan& other)
        : engine(other.engine), controller(other.controller), remote(other.remote), name(nullptr) {
        initializeName(other.name);
    }

    Fan& operator=(const Fan& other) {
        if (this == &other) return *this;

        engine = other.engine;
        controller = other.controller;
        remote = other.remote;

        if (name) delete[] name;
        initializeName(other.name);

        return *this;
    }

    void show() const {
        cout << "\n--- Fan status (" << name << ") ---" << endl;
        engine.show();
        controller.show();
        remote.show();
    }

    void applySettings() {
        controller.setTargetSpeed(remote.getSpeed());
        controller.setTimer(remote.getTime());
        engine.setSpeed(controller.getTargetSpeed());
        cout << "\nSettings applied to " << name << ": engine speed = "
            << engine.getSpeed() << " rpm, shutdown time = "
            << controller.getTimer() << " sec." << endl;
    }
};


int main() {
    double speed, time;
    cout << "Enter the desired engine speed (rpm): ";
    cin >> speed;
    cout << "Enter the fan shutdown time (sec): ";
    cin >> time;

    Remote r(speed, time);
    Controller c;
    Engine e;

    Fan f(e, c, r);

    cout << "\nInitial state:" << endl;
    f.show();

    f.applySettings();

    cout << "\nAfter applying settings:" << endl;
    f.show();

    return 0;
}