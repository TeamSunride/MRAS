//
// Created by Tom Danvers on 10/02/2023.
//

#ifndef MRAS_TEXTLOGMSG_H
#define MRAS_TEXTLOGMSG_H

#include "SystemMessage.h"

/**
 * @brief A message containing text to be logged
 *
 * This message is emitted by the TextLogger subsystems and allows the SDLogger to log text to the SD card.
 */
struct TextLogMsg : public SystemMessage {
    TextLogMsg() : SystemMessage(TextLogMsg_t) {}

    /**
     * @brief The text to be logged. Max 255 chars in length.
     */
    char text[255] = {};
};

#endif //MRAS_TEXTLOGMSG_H
