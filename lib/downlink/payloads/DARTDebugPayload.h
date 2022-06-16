//
// Created by tomto on 14/06/2022.
//

#ifndef MRASV2_DARTDEBUGPAYLOAD_H
#define MRASV2_DARTDEBUGPAYLOAD_H

#include "downlink.h"
#include "LineProtocolBuilder.h"
#include "Vector3D.h"

struct DARTDebugPayload {
    downlink::PayloadType type = downlink::PayloadType::DARTDebugPayload;
    Vector3D mpuAccel{};
    Vector3D mpuGyro{};

    uint64_t timestamp = 0;

    String toLineProtocol() const {
        return LineProtocolBuilder("DARTDebugPayload")
                .addField("mpuAccelX", mpuAccel.getX())
                .addField("mpuAccelY", mpuAccel.getY())
                .addField("mpuAccelZ", mpuAccel.getZ())
                .addField("mpuGyroX", mpuGyro.getX())
                .addField("mpuGyroY", mpuGyro.getY())
                .addField("mpuGyroY", mpuGyro.getY())
                .setTimestamp(timestamp)
                .build();
    }

    DARTDebugPayload(Vector3D _mpuAccel, Vector3D _mpuGyro) {
        mpuAccel = _mpuAccel;
        mpuGyro = _mpuGyro;
    }

    DARTDebugPayload() = default;
};

#endif //MRASV2_DARTDEBUGPAYLOAD_H
