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

#include "Payload.h"

class DARTDebugPayload : public Payload {
public:
    // IMU data
    Vector<float, 3> imuAccel {0, 0, 0};
    Vector<float, 3> imuGyro {0, 0, 0};
    Vector<float, 3> imuMag {0, 0, 0};

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
                       "imuAX=%f,"
                       "imuAY=%f,"
                       "imuAZ=%f,"
                       "imuGX=%f,"
                       "imuGY=%f,"
                       "imuGZ=%f,"
                       "imuMX=%f,"
                       "imuMY=%f,"
                       "imuMZ=%f,"
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
                       "adxlZ=%f",
                imuAccel[0], imuAccel[1], imuAccel[2],
                imuGyro[0], imuGyro[1], imuGyro[2],
                imuMag[0], imuMag[1], imuMag[2],
                latitude, longitude, altitude, satellitesInView, fixType,
                pressure, temperature,
                DAQTime,
                adxlAccel[0], adxlAccel[1], adxlAccel[2]);
    }

    void toCSVformat(char* output) const {
        sprintf(output, "DARTDebugPayload,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%d,%f,%f,%d,%f,%f,%f",
                imuAccel[0], imuAccel[1], imuAccel[2],
                imuGyro[0], imuGyro[1], imuGyro[2],
                imuMag[0], imuMag[1], imuMag[2],
                latitude, longitude, altitude, satellitesInView, fixType,
                pressure, temperature,
                DAQTime,
                adxlAccel[0], adxlAccel[1], adxlAccel[2]);
    }

    DARTDebugPayload(IMU *imu, GPS *gps, Barometer *barometer, Accelerometer *accelerometer) {
        type = PayloadType::DARTDebugPayload_t;

        // 6dof IMU data
        imuAccel = imu->getAcceleration();
        imuGyro = imu->getGyroVector();
        imuMag = imu->getMagnetometerVector();

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
