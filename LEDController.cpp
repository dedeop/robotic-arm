#include <rtt/RTT.hpp>
#include <rtt/Component.hpp>
#include <iostream>

class LEDController : public RTT::TaskContext {
public:
    LEDController(const std::string& name) : TaskContext(name) {
        // Registering the operations to turn LED on and off
        this->addOperation("turnLEDOn", &LEDController::turnLEDOn, this)
            .doc("Turns the LED on (GPIO0_48)");
        this->addOperation("turnLEDOff", &LEDController::turnLEDOff, this)
            .doc("Turns the LED off (GPIO0_48)");
    }

    void turnLEDOn() {
        int result = system("gpioset 1 48=1");
        if (result == 0) {
            std::cout << "LED turned on" << std::endl;
        } else {
            std::cerr << "Failed to turn LED on" << std::endl;
        }
    }

    void turnLEDOff() {
        int result = system("gpioset 1 48=0");
        if (result == 0) {
            std::cout << "LED turned off" << std::endl;
        } else {
            std::cerr << "Failed to turn LED off" << std::endl;
        }
    }
};

// Register the component with the Orocos RTT framework
ORO_CREATE_COMPONENT(LEDController)
