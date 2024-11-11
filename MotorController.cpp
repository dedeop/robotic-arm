#include <rtt/RTT.hpp>
#include <rtt/Component.hpp>
#include <iostream>
#include <cstdlib>
#include <unistd.h>  // for usleep (microsecond sleep)

class MotorController : public RTT::TaskContext {
public:
    MotorController(const std::string& name) 
        : TaskContext(name), isForward(true), cycleTime(500000) {  // cycleTime is in microseconds (0.5s)
        
        // Register operations for controlling motor
        this->addOperation("setForward", &MotorController::setForward, this)
            .doc("Set the motor direction to forward");
        this->addOperation("setReverse", &MotorController::setReverse, this)
            .doc("Set the motor direction to reverse");
    }

    // Operation to set motor direction to forward
    void setForward() {
        system("gpioset 1 48=1");  // DIR pin high for forward
        system("gpioset 1 34=1");  // PWM pin high for full speed
        std::cout << "Motor set to forward" << std::endl;
    }

    // Operation to set motor direction to reverse
    void setReverse() {
        system("gpioset 1 48=0");  // DIR pin low for reverse
        system("gpioset 1 34=1");  // PWM pin high for full speed
        std::cout << "Motor set to reverse" << std::endl;
    }

    // Function to stop the motor by disabling PWM
    void disableMotor() {
        system("gpioset 1 34=0");  // PWM pin low to stop the motor
        std::cout << "Motor disabled" << std::endl;
    }

    bool configureHook() override {
        std::cout << "Configuring MotorController..." << std::endl;
        return true;  // Motor is enabled by default due to SLP being high
    }

    bool startHook() override {
        std::cout << "Starting MotorController..." << std::endl;
        return true;
    }

    void updateHook() override {
        // Oscillate the motor: spin slightly in one direction, then reverse
        if (isForward) {
            setForward();
            usleep(cycleTime);  // Delay for forward motion
            disableMotor();  // Stop briefly before reversing
        } else {
            setReverse();
            usleep(cycleTime);  // Delay for reverse motion
            disableMotor();  // Stop briefly before reversing again
        }
        
        isForward = !isForward;  // Toggle direction
        usleep(cycleTime);  // Pause between each change in direction
    }

private:
    bool isForward;  // Flag to track direction
    const int cycleTime;  // Duration for each movement in microseconds
};

// Register the component with Orocos RTT
ORO_CREATE_COMPONENT(MotorController)
