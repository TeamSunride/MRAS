//
// Created by tomto on 14/06/2022.
//

#ifndef MRAS_DARTDEBUGPAYLOAD_H
#define MRAS_DARTDEBUGPAYLOAD_H

#include "downlink.h"
#include "LineProtocolBuilder.h"
#include "Vector.h"
#include "Vector3D.h"
#include "IMU.h"
#include "GPS.h"
#include "Barometer.h"
#include "Accelerometer.h"

struct DARTDebugPayload {
    downlink::PayloadType type = downlink::PayloadType::DARTDebugPayload;

    // MPU6050 data
    Vector<float, 3> mpuAccel {0,0,0};
    Vector<float, 3> mpuGyro {0,0,0};

    // GPS data
    float latitude = 0;
    float longitude = 0;
    float altitude = 0;
    uint8_t satellitesInView = 0;
    uint8_t fixType = 0;

    // barometer data
    float pressure = 0;
    float temperature = 0;

    // accelerometer data
    Vector<float, 3> adxlAccel{};

    uint8_t DAQTime = 0;


    uint64_t timestamp = 0;

    void toLineProtocol(char* output) const {
        sprintf(output, "DARTDebugPayload "
                       "mpuAX=%f,"
                       "mpuAY=%f,"
                       "mpuAZ=%f,"
                       "mpuGX=%f,"
                       "mpuGY=%f,"
                       "mpuGZ=%f,"
                       "lat=%f,"
                       "long=%f,"
                       "altGPS=%f,"
                       "SIV=%du,"
                       "fixType=%du,"
                       "pressure=%f,"
                       "temp=%f,"
                       "DAQTime=%du,"
                       "adxlX=%f,"
                       "adxlY=%f,"
                       "adxlZ=%f %llu",
                       mpuAccel[0], mpuAccel[1], mpuAccel[2],
                       mpuGyro[0], mpuGyro[1], mpuGyro[2],
                       latitude, longitude, altitude, satellitesInView, fixType,
                       pressure, temperature,
                       DAQTime,
                       adxlAccel[0], adxlAccel[1], adxlAccel[2],
                       timestamp);

        /*
        return LineProtocolBuilder("DARTDebugPayload")
                .addField("mpuAX", mpuAccel[0])
                .addField("mpuAY", mpuAccel[1])
                .addField("mpuAZ", mpuAccel[2])
                .addField("mpuGX", mpuGyro[0])
                .addField("mpuGY", mpuGyro[1])
                .addField("mpuGZ", mpuGyro[2])
                .addField("lat", latitude)
                .addField("long", longitude)
                .addField("altGPS", altitude)
                .addField("SIV", satellitesInView)
                .addField("fixType", fixType)
                .addField("pressure", pressure)
                .addField("temp", temperature)
                .addField("DAQTime", DAQTime)
                .addField("adxlX", adxlAccel[0])
                .addField("adxlY", adxlAccel[1])
                .addField("adxlZ", adxlAccel[2])
                .setTimestamp(timestamp)
                .build();
        */
    }

    DARTDebugPayload(IMU *imu, GPS *gps, Barometer *barometer, Accelerometer *accelerometer) {
        // 6dof IMU data
        mpuAccel = imu->getAcceleration();
        mpuGyro = imu->getGyroVector();

        // GPS data
        latitude = gps->getLatitude();
        longitude = gps->getLongitude();
        altitude = gps->getAltitude();
        satellitesInView = gps->getSatellitesInView();
        fixType = gps->getFixType();

        // barometer data
        pressure = barometer->getPressure();
        temperature = barometer->getTemperature();

        adxlAccel = accelerometer->getAcceleration();
    }

    DARTDebugPayload() = default;
};

#endif //MRAS_DARTDEBUGPAYLOAD_H
