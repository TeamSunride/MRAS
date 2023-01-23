# How to implement a new Subsystem

A Subsystem is a class in the MRAS system that represents a specific sensor or system on the device. These classes
inherit from the base Subsystem class and implement its abstract methods. The Subsystem class provides a common
interface for all sensors and systems, allowing for easy communication and management by the MRAS_System class.

The Subsystem class has several members that are used to define the behavior and functionality of the sensor or
system it represents. These include setup() and loop() methods, which are used to initialize and continuously
update the sensor or system, respectively. Additionally, Subsystems have a get_status() method to check the
current status of the Subsystem, self_test() method to check that the Subsystem is working correctly and
on_message() method to handle messages sent to the Subsystem. The get_name() method returns a string that
provides a human-readable name for the Subsystem, used for logging and debugging purposes. Finally, the get_id()
method returns a unique ID assigned to the Subsystem, which is used to identify it within the MRAS system.

## Step-by-step guide

To implement a new subsystem for a new sensor, you can follow these steps:

1. Define a new class for your sensor subsystem, which should inherit from the Subsystem class. This class should be defined in its own header file, for example `Sensor_NewSensor.h`
2. In the header file, define any variables or objects that your sensor subsystem will need to use, such as an instance of the sensor object.
3. Implement the `setup()` function in the class. This function should handle any one-time setup required for the sensor, such as initializing the sensor object and configuring it for use.
4. Implement the `loop()` function in the class. This function should handle the main functionality of your sensor subsystem, such as reading data from the sensor and publishing it to other subsystems.
5. Implement any additional functions or overrides that you want your sensor subsystem to have. For example, you may want to include a self-test function that verifies that the sensor is functioning properly.
6. In the main `setup()` function of the MRAS_System, instantiate an object of your new sensor class, and add it as a subsystem to the MRAS_System by calling `mras->add_subsystem(&sensor);`
7. If necessary, add the sensor class as a subscriber to other subsystems to allow for data transfer between them.

## Example


```cpp
#include "Subsystem.h"
#include "NewSensor.h"

class Sensor_NewSensor : public Subsystem {
private:
    NewSensor* newSensor;

public:
    Sensor_NewSensor(uint8_t id, int parameter1, int parameter2, int parameter3) : Subsystem(id) {
        newSensor = new NewSensor(parameter1, parameter2, parameter3);
    }

    ~Sensor_NewSensor() {
        delete newSensor;
    }

    int8_t setup() override {
        newSensor->begin();
        newSensor->setDefaultConfig();
        return 0;
    }

    int8_t loop() override {
        int data = newSensor->readData();
        publish(data);
        return 0;
    }

    SUBSYSTEM_NAME("NewSensor")
};

```