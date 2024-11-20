#include <rtt/RTT.hpp>

#include <rtt/Component.hpp>

#include <iostream>

#include <thread>  // For std::this_thread::sleep_for

#include <chrono>  // For std::chrono::milliseconds



class MotorController : public RTT::TaskContext {

public:

    MotorController(const std::string& name)

        : TaskContext(name), isForward(true), cycleCount(0), maxCycles(5) {

        // Register operations

        this->addOperation("moveServoOne", &MotorController::moveServoOne, this)

            .doc("Move Servo One back and forth for a set number of cycles");

        this->addOperation("moveServoTwo", &MotorController::moveServoTwo, this)

            .doc("Move Servo Two back and forth for a set number of cycles");

        this->addOperation("moveServoThree", &MotorController::moveServoThree, this)

            .doc("Move Servo Three back and forth for a set number of cycles");

        this->addOperation("moveBackAndForth", &MotorController::moveBackAndForth, this)

            .doc("Move all servos back and forth in sequence");

        this->addOperation("moveServoOneRight", &MotorController::moveServoOneRight, this)

            .doc("Move Servo One to the right for 500ms");

        this->addOperation("moveServoOneLeft", &MotorController::moveServoOneLeft, this)

            .doc("Move Servo One to the left for 500ms");

        this->addOperation("moveServoTwoRight", &MotorController::moveServoTwoRight, this)

            .doc("Move Servo Two to the right for 500ms");

        this->addOperation("moveServoTwoLeft", &MotorController::moveServoTwoLeft, this)

            .doc("Move Servo Two to the left for 500ms");

        this->addOperation("moveServoThreeRight", &MotorController::moveServoThreeRight, this)

            .doc("Move Servo Three to the right for 500ms");

        this->addOperation("moveServoThreeLeft", &MotorController::moveServoThreeLeft, this)

            .doc("Move Servo Three to the left for 500ms");

    }



    void moveServoOne() {

        cycleCount = 0;
	isForward = true;

        while (cycleCount < maxCycles) {

            if (isForward) {

                moveServoOneRight();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // 1000ms delay

            } else {

                moveServoOneLeft();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // 1000ms delay

            }

            isForward = !isForward;  // Toggle direction

            cycleCount++;

            std::cout << "Servo One: Cycle " << cycleCount << "/" << maxCycles << " completed." << std::endl;

        }

        std::cout << "Servo One: Completed " << maxCycles << " cycles." << std::endl;

    }



    void moveServoTwo() {

        cycleCount = 0;
	isForward = true;

        while (cycleCount < maxCycles) {

            if (isForward) {

                moveServoTwoRight();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // 1000ms delay

            } else {

                moveServoTwoLeft();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // 1000ms delay

            }

            isForward = !isForward;  // Toggle direction

            cycleCount++;

            std::cout << "Servo Two: Cycle " << cycleCount << "/" << maxCycles << " completed." << std::endl;

        }

        std::cout << "Servo Two: Completed " << maxCycles << " cycles." << std::endl;

    }



    void moveServoThree() {

        cycleCount = 0;
	isForward = true;

        while (cycleCount < maxCycles) {

            if (isForward) {

                moveServoThreeRight();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // 1000ms delay

            } else {

                moveServoThreeLeft();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // 1000ms delay

            }

            isForward = !isForward;  // Toggle direction

            cycleCount++;

            std::cout << "Servo Three: Cycle " << cycleCount << "/" << maxCycles << " completed." << std::endl;

        }

        std::cout << "Servo Three: Completed " << maxCycles << " cycles." << std::endl;

    }



    void moveBackAndForth() {

        moveServoOne();

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));  // 2000ms delay before running next motor

        moveServoTwo();

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));  // 2000ms delay before running next motor

        moveServoThree();

    }



    void moveServoOneRight() {

        system("gpioset 1 48=1");  // DIR pin high for right

        system("gpioset 1 34=1");  // PWM pin high for movement

        std::cout << "Servo One moving RIGHT!" << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(25));  // 1000ms delay

        system("gpioset 1 34=0");  // PWM pin low to stop

        std::cout << "Servo One stopped!" << std::endl;

    }



    void moveServoOneLeft() {

        system("gpioset 1 48=0");  // DIR pin low for left

        system("gpioset 1 34=1");  // PWM pin high for movement

        std::cout << "Servo One moving LEFT!" << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(25));  // 1000ms delay

        system("gpioset 1 34=0");  // PWM pin low to stop

        std::cout << "Servo One stopped!" << std::endl;

    }



    void moveServoTwoRight() {

        system("gpioset 1 14=1");  // DIR pin high for right

        system("gpioset 1 16=1");  // PWM pin high for movement

        std::cout << "Servo Two moving RIGHT!" << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(25));  // 1000ms delay

        system("gpioset 1 16=0");  // PWM pin low to stop

        std::cout << "Servo Two stopped!" << std::endl;

    }



    void moveServoTwoLeft() {

        system("gpioset 1 14=0");  // DIR pin low for left

        system("gpioset 1 16=1");  // PWM pin high for movement

        std::cout << "Servo Two moving LEFT!" << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(25));  // 1000ms delay

        system("gpioset 1 16=0");  // PWM pin low to stop

        std::cout << "Servo Two stopped!" << std::endl;

    }



    void moveServoThreeRight() {

        system("gpioset 1 59=1");  // DIR pin high for right

        system("gpioset 1 75=1");  // PWM pin high for movement

        std::cout << "Servo Three moving RIGHT!" << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(25));  // 1000ms delay

        system("gpioset 1 75=0");  // PWM pin low to stop

        std::cout << "Servo Three stopped!" << std::endl;

    }



    void moveServoThreeLeft() {

        system("gpioset 1 59=0");  // DIR pin low for left

        system("gpioset 1 75=1");  // PWM pin high for movement

        std::cout << "Servo Three moving LEFT!" << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(25));  // 1000ms delay

        system("gpioset 1 75=0");  // PWM pin low to stop

        std::cout << "Servo Three stopped!" << std::endl;

    }



private:

    bool isForward;       // Flag to track motor direction

    int cycleCount;       // Current cycle count

    const int maxCycles;  // Maximum number of cycles

};



ORO_CREATE_COMPONENT(MotorController)

