//
// Created by Tom Danvers on 04/02/2023.
//

#ifndef MRAS_TELEMETRYMESSAGE_H
#define MRAS_TELEMETRYMESSAGE_H

enum TelemetryMessageType {
    UNDEFINED_TELEMETRY_MESSAGE,
    /*
     * Rocket sends this message to the ground in order to
     * initiate a new transfer opportunity
     */
    TransferWindowInitMsg_t,

    /*
     * Ground sends this in response to a TransferWindowInit
     * in the case where it does not have any data to send
     * to the rocket
     */
    TransferWindowAckMsg_t,
    CommandMsg_t, // unused for now
    CommandResponseMsg_t, // unused for now
    TelemetryDataMsg_t
};

/*
 * TelemetryMessages are similar to SystemMessages but are designed for the
 * telemetry system. All data contained within the TelemetryMessage must be
 * stored within the TelemetryMessage and not referred to with pointers.
 * This is because the memory of the TelemetryMessage is copied straight into
 * the radio buffer and sent down to the ground station.
 *
 * TelemetryMessages must be allocated on the heap and will be deleted by the
 * TelemetrySystem once they have been transmitted or processed.
 */
class TelemetryMessage {
protected:
    TelemetryMessageType type;
public:
    explicit TelemetryMessage(TelemetryMessageType type) : type(type) {};
    TelemetryMessageType get_type() { return type; };
};


#endif //MRAS_TELEMETRYMESSAGE_H
