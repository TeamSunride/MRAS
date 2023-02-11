//
// Created by Tom Danvers on 13/12/2022.
//

#ifndef MRAS_SYSTEMMESSAGE_H
#define MRAS_SYSTEMMESSAGE_H

#include <cstdint>

enum SystemMessageType {
    UNDEFINED_SYSTEM_MESSAGE,
    AccelerometerDataMsg_t,
    HighGAccelerometerDataMsg_t,
    BarometerDataMsg_t,
    GyroDataMsg_t,
    MagnetometerDataMsg_t,
    GNSSDataMsg_t,
    QueueTelemetryMessageMsg_t,
    ReceivedTelemetryMessageMsg_t,
    TextLogMsg_t
};

/**
 * @brief A base class for all system messages
 *
 * This class is used to provide a common interface for all system messages.
 *
 * System messages are used to communicate between subsystems. See `Software Architecture Overview` for more information.
 */
class SystemMessage {
public:
    explicit SystemMessage(SystemMessageType type) : type(type) {};

    /**
     * @brief Get the type of the message
     *
     * @return The SystemMessageType of the SystemMessage
     */
    SystemMessageType get_type() { return type; };
protected:
    SystemMessageType type;
};

#endif //MRAS_SYSTEMMESSAGE_H
