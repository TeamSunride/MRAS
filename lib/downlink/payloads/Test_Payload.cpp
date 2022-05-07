//
// Created by Tom Danvers on 07/05/2022.
// 2022 TeamSunride.
//

#include "Test_Payload.h"
#include "LineProtocolBuilder.h"

String Test_Payload::toLineProtocol() const {
    return LineProtocolBuilder("Test_Payload")
            .addField("x", x)
            .addField("y", y)
            .addField("z", z)
            .setTimestamp(timestamp)
            .build();
}
