//
// Created by Nikilesh Ramesh on 04/04/2023.
//

#ifndef MRAS_EVENTDETECTORMSG_H
#define MRAS_EVENTDETECTORMSG_H

#include "../SystemMessage.h"


struct EventDetectorMsg : public SystemMessage {
    explicit EventDetectorMsg() : SystemMessage(EventDetectorMsg_t) {}

    char event = 0;
    char phase = 0;
};
#endif //MRAS_EVENTDETECTORMSG_H
