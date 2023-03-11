//
// Created by Tom Danvers on 13/12/2022.
//

#ifndef MRAS_SUBSYSTEM_H
#define MRAS_SUBSYSTEM_H

#include <cstdint>
#include "SystemMessage.h"

// macro to define empty message handler for subsystems that don't want to receive messages
#define SUBSYSTEM_NO_MESSAGE_HANDLER void on_message(SystemMessage *msg) override {};

#define SUBSYSTEM_NAME(name) const char* get_name() override { return name; }


/**
 * A Subsystem is a class in the MRAS system that represents a specific sensor or system on the device. These classes
 * inherit from the base Subsystem class and implement its abstract methods. The Subsystem class provides a common
 * interface for all sensors and systems, allowing for easy communication and management by the MRAS_System class.
 *
 * The Subsystem class has several members that are used to define the behavior and functionality of the sensor or
 * system it represents. These include setup() and loop() methods, which are used to initialize and continuously
 * update the sensor or system, respectively. Additionally, Subsystems have a get_status() method to check the
 * current status of the Subsystem, self_test() method to check that the Subsystem is working correctly and
 * on_message() method to handle messages sent to the Subsystem. The get_name() method returns a string that
 * provides a human-readable name for the Subsystem, used for logging and debugging purposes. Finally, the get_id()
 * method returns a unique ID assigned to the Subsystem, which is used to identify it within the MRAS system.
 */
class Subsystem {
public:
    /**
     * Get the name of the subsystem, used for logging purposes
     * @return Unique name for the subsystem, such as "Accelerometer"
     */
    virtual const char *get_name() = 0;

    /*
     * Children of subsystem should override this function and use it for running one-time setup code, analogous to
     * the Arduino setup() function
     *
     * The function should return a status code, with 0 indicating success and any other value representing an error
     */
    virtual int8_t setup() = 0;

    /*
     * Children of subsystem should override this function and use it for running their main loop, analogous to
     * the Arduino loop() function
     *
     * The function should return a status code, with 0 indicating success and any other value representing an error
     */
    virtual int8_t loop() = 0;

    /**
     * @return The unique subsystem ID
     */
    uint8_t get_id() const;

    /**
     * @return The current status of the system. 0 means no error, any other value represents an error.
     */
    int8_t get_status() const;

    /**
     * Run a self test.
     * @return -1 if the self test is not implemented. 0 if success. Any other value represents an error.
     */
    int8_t self_test() const;

    /**
     * Add a new Subsystem subscriber to the Subsystem
     *
     * The on_message() function of the subscribed Subsystem will be called whenever the publish() function is called
     * with a SystemMessage. This allows for communication between Subsystems.
     *
     * @param subscriber The Subsystem to subscribe to this Subsystem
     * @return Whether the operation was successful or not. There is a limit to the number of subscribers to each
     * Subsystem. At the moment, this is 255
     */
    bool add_subscriber(Subsystem *subscriber);

    /**
     * Constructor for Subsystem
     * @param id The unique ID of the subsystem. This must be different for all subsystems.
     */
    explicit Subsystem(uint8_t id) : id(id) {};

private:
    uint8_t id;
    Subsystem *subscribers[255] = {};
    int16_t subscriber_count = 0;
protected:
    int8_t status = 0;
    int8_t self_test_result = -1;

    void log(const char fmt[], ...);

    /**
     * Can be overridden by Subsystems to handle messages
     * @param msg The SystemMessage sent by the Publishing Subsystem
     */
    virtual void on_message(SystemMessage *msg) = 0;

    /**
     * Publish a SystemMessage to any subscribed Subsystems.
     * @param msg THe SystemMessage to publish.
     */
    void publish(SystemMessage *msg);

    /**
     * Turn the buzzer on
     * @param duration time period for which the buzzer should buzz, in seconds.
     */
    static void buzzer(uint16_t frequency, uint32_t duration);

};


#endif //MRAS_SUBSYSTEM_H
