//
// Created by tomto on 14/06/2022.
//

#ifndef MRASV2_DARTDEBUGPAYLOAD_H
#define MRASV2_DARTDEBUGPAYLOAD_H

#include "downlink.h"
#include "LineProtocolBuilder.h"
#include "Vector3D.h"
#include "IMU.h"
#include "GPS.h"

struct DARTDebugPayload {
    downlink::PayloadType type = downlink::PayloadType::DARTDebugPayload;

    // MPU6050 data
    Vector3D mpuAccel{};
    Vector3D mpuGyro{};

    // GPS data
    float latitude = 0;
    float longitude = 0;
    float altitude = 0;
    uint8_t satellitesInView = 0;
    uint8_t fixType = 0;


    uint64_t timestamp = 0;

    String toLineProtocol() const {
        return LineProtocolBuilder("DARTDebugPayload")
                .addField("mpuAX", mpuAccel.getX())
                .addField("mpuAY", mpuAccel.getY())
                .addField("mpuAZ", mpuAccel.getZ())
                .addField("mpuGX", mpuGyro.getX())
                .addField("mpuGY", mpuGyro.getY())
                .addField("mpuGZ", mpuGyro.getZ())
                .addField("lat", latitude)
                .addField("long", longitude)
                .addField("altGPS", altitude)
                .addField("SIV", satellitesInView)
                .addField("fixType", fixType)
                .setTimestamp(timestamp)
                .build();
    }

    DARTDebugPayload(IMU *imu, GPS *gps) {
        // 6dof IMU data
        mpuAccel = imu->getAcceleration();
        mpuGyro = imu->getGyroVector();

        // GPS data
        latitude = gps->getLatitude();
        longitude = gps->getLongitude();
        altitude = gps->getAltitude();
        satellitesInView = gps->getSatellitesInView();
        fixType = gps->getFixType();
    }

    DARTDebugPayload() = default;
};

#endif //MRASV2_DARTDEBUGPAYLOAD_H
