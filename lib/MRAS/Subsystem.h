//
// Created by Tom Danvers on 13/12/2022.
//

#ifndef MRAS_SUBSYSTEM_H
#define MRAS_SUBSYSTEM_H

#include <cstdint>

class Subsystem {
public:
    /**
     * Get the name of the subsystem, used for logging purposes
     * @return Unique name for the subsystem, such as "Accelerometer"
     */
    virtual const char* get_name() = 0;

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
    bool add_subscriber(Subsystem* subscriber);

    /**
     * Constructor for Subsystem
     * @param id The unique ID of the subsystem. This must be different for all subsystems.
     */
    explicit Subsystem(uint8_t id) : id(id) {};

private:
    uint8_t id;
    Subsystem* subscribers[255] = {};
    int16_t subscriber_count = 0;
protected:
    int8_t status = 0;
    int8_t self_test_result = -1;

    void log(const char* text);
};


#endif //MRAS_SUBSYSTEM_H
