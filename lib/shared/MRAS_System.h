//
// Created by Tom Danvers on 13/12/2022.
//

#ifndef MRAS_MRAS_SYSTEM_H
#define MRAS_MRAS_SYSTEM_H

#include "Subsystem.h"
#include "TextLogger.h"
#include "BuzzerInterfaceSystem.h"

/**
 * @brief The main class of the MRAS system
 *
 * This class is the main class of the MRAS system. It is a singleton class that is responsible for
 * managing all of the Subsystems. For more information, see the `Software Architecture Overview` page.
 */
class MRAS_System {
private:
    /**
     * @brief The array of Subsystems that are currently registered with the system.
     *
     * Note that this array contains many zeros if less than 255 Subsystems are registered. Therefore, we must also
     * keep track of the number of Subsystems that are registered. This is done by the subsystem_count variable
     */
    Subsystem* subsystems[255] = {};

    /**
     * @brief The number of Subsystems that are currently registered with the system
     */
    uint8_t subsystem_count = 0;

    /**
     * @brief A pointer to the instance of the MRAS_System singleton
     */
    static MRAS_System *instance;

    /**
     * @brief A pointer to the TextLogger that is used to log messages
     */
    TextLogger* logger = nullptr;

    /**
     * @brief A pointer to the TextLogger that is used to log messages
     */
    Buzzer* buzzer = nullptr;
public:

    /**
     * Singletons should not be cloneable
     */
    MRAS_System(MRAS_System &other) = delete;

    void operator=(const MRAS_System &) = delete;

    MRAS_System() = default;

    /**
     * This is the static method that controls the access to the singleton
     * instance. On the first run, it creates a singleton object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */
    static MRAS_System* get_instance();

    /**
     * @brief Add a Subsystem to the system
     *
     * @param subsystem A pointer to the Subsystem to add
     * @return `true` If the Subsystem was successfully added
     * @return `false` If the Subsystem was not successfully added
     * (e.g. if the maximum number of Subsystems has been reached)
     */
    bool add_subsystem(Subsystem* subsystem);

    void setup();

    void loop();

    /**
     * @brief Set the TextLogger that is used to log messages
     *
     * @param logger A pointer to the TextLogger that is used to log messages
     */
    void set_logger(TextLogger *logger);

    /**
     * @brief Get the TextLogger that is used to log messages
     *
     * @return TextLogger* A pointer to the TextLogger that is used to log messages
     */
    TextLogger* get_logger();

    /**
     * @brief Set the Buzzer that is used to buzz when called
     *
     * @param buzzer A pointer to the Buzzer that is used to buzz
     */
    void set_buzzer(Buzzer  *buzzer);

    /**
     * @brief Get the Buzzer that is used to buzz
     *
     * @return Buzzer* A pointer to the Buzz
     */
    Buzzer* get_buzzer();

};


#endif //MRAS_MRAS_SYSTEM_H
