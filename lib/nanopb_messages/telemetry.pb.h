/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.7 */

#ifndef PB_TELEMETRY_PB_H_INCLUDED
#define PB_TELEMETRY_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Enum definitions */
typedef enum _Command {
    Command_START_TRANSFER_WINDOW = 0,
    Command_ARM = 1,
    Command_DISARM = 2,
    Command_WIPE_FLASH_MEMORY = 3
} Command;

/* Struct definitions */
typedef struct _Heartbeat {
    uint64_t timestamp;
} Heartbeat;

typedef struct _BasicSensorData {
    uint64_t timestamp;
    float temperature;
    float pressure;
    float latitude;
    float longitude;
} BasicSensorData;

typedef struct _CommandMessage {
    Command command;
} CommandMessage;

typedef struct _TelemetryMessage {
    pb_size_t which_message;
    union {
        Heartbeat heartbeat;
        BasicSensorData basicSensorData;
        CommandMessage command;
    } message;
} TelemetryMessage;


#ifdef __cplusplus
extern "C" {
#endif

/* Helper constants for enums */
#define _Command_MIN Command_START_TRANSFER_WINDOW
#define _Command_MAX Command_WIPE_FLASH_MEMORY
#define _Command_ARRAYSIZE ((Command)(Command_WIPE_FLASH_MEMORY+1))



#define CommandMessage_command_ENUMTYPE Command



/* Initializer values for message structs */
#define Heartbeat_init_default                   {0}
#define BasicSensorData_init_default             {0, 0, 0, 0, 0}
#define CommandMessage_init_default              {_Command_MIN}
#define TelemetryMessage_init_default            {0, {Heartbeat_init_default}}
#define Heartbeat_init_zero                      {0}
#define BasicSensorData_init_zero                {0, 0, 0, 0, 0}
#define CommandMessage_init_zero                 {_Command_MIN}
#define TelemetryMessage_init_zero               {0, {Heartbeat_init_zero}}

/* Field tags (for use in manual encoding/decoding) */
#define Heartbeat_timestamp_tag                  1
#define BasicSensorData_timestamp_tag            1
#define BasicSensorData_temperature_tag          2
#define BasicSensorData_pressure_tag             4
#define BasicSensorData_latitude_tag             5
#define BasicSensorData_longitude_tag            6
#define CommandMessage_command_tag               1
#define TelemetryMessage_heartbeat_tag           2
#define TelemetryMessage_basicSensorData_tag     3
#define TelemetryMessage_command_tag             4

/* Struct field encoding specification for nanopb */
#define Heartbeat_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT64,   timestamp,         1)
#define Heartbeat_CALLBACK NULL
#define Heartbeat_DEFAULT NULL

#define BasicSensorData_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT64,   timestamp,         1) \
X(a, STATIC,   SINGULAR, FLOAT,    temperature,       2) \
X(a, STATIC,   SINGULAR, FLOAT,    pressure,          4) \
X(a, STATIC,   SINGULAR, FLOAT,    latitude,          5) \
X(a, STATIC,   SINGULAR, FLOAT,    longitude,         6)
#define BasicSensorData_CALLBACK NULL
#define BasicSensorData_DEFAULT NULL

#define CommandMessage_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UENUM,    command,           1)
#define CommandMessage_CALLBACK NULL
#define CommandMessage_DEFAULT NULL

#define TelemetryMessage_FIELDLIST(X, a) \
X(a, STATIC,   ONEOF,    MESSAGE,  (message,heartbeat,message.heartbeat),   2) \
X(a, STATIC,   ONEOF,    MESSAGE,  (message,basicSensorData,message.basicSensorData),   3) \
X(a, STATIC,   ONEOF,    MESSAGE,  (message,command,message.command),   4)
#define TelemetryMessage_CALLBACK NULL
#define TelemetryMessage_DEFAULT NULL
#define TelemetryMessage_message_heartbeat_MSGTYPE Heartbeat
#define TelemetryMessage_message_basicSensorData_MSGTYPE BasicSensorData
#define TelemetryMessage_message_command_MSGTYPE CommandMessage

extern const pb_msgdesc_t Heartbeat_msg;
extern const pb_msgdesc_t BasicSensorData_msg;
extern const pb_msgdesc_t CommandMessage_msg;
extern const pb_msgdesc_t TelemetryMessage_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define Heartbeat_fields &Heartbeat_msg
#define BasicSensorData_fields &BasicSensorData_msg
#define CommandMessage_fields &CommandMessage_msg
#define TelemetryMessage_fields &TelemetryMessage_msg

/* Maximum encoded size of messages (where known) */
#define BasicSensorData_size                     31
#define CommandMessage_size                      2
#define Heartbeat_size                           11
#define TelemetryMessage_size                    33

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif