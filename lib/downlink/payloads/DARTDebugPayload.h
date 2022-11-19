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

#include "Payload.h"
#include "Int64String.h"

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

    uint8_t DAQTime = 0;


    uint64_t timestamp = 0;

    void toLineProtocol(char* output) const {
        char timestamp_str[20];
        int64String(timestamp).toCharArray(timestamp_str, sizeof timestamp_str);
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
                       "SIV=%d,"
                       "fixType=%d,"
                       "pressure=%f,"
                       "temp=%f,"
                       "DAQTime=%d,"
                       "h=%f"
                       " %s",
                imuAccel[0], imuAccel[1], imuAccel[2],
                imuGyro[0], imuGyro[1], imuGyro[2],
                imuMag[0], imuMag[1], imuMag[2],
                latitude, longitude, altitude, satellitesInView, fixType,
                pressure, temperature,
                DAQTime, getAltitude(), timestamp_str);
    }

    void toCSVformat(char* output) const {
        char timestamp_str[20];
        int64String(timestamp).toCharArray(timestamp_str, sizeof timestamp_str);
        sprintf(output, "DARTDebugPayload,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%d,%f,%f,%d,%f,%s",
                imuAccel[0], imuAccel[1], imuAccel[2],
                imuGyro[0], imuGyro[1], imuGyro[2],
                imuMag[0], imuMag[1], imuMag[2],
                latitude, longitude, altitude, satellitesInView, fixType,
                pressure, temperature,
                DAQTime, getAltitude(), timestamp_str);
    }

    DARTDebugPayload(IMU *imu, GPS *gps, Barometer *barometer) {
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
    }

    float getAltitude() const {
        if (pressure == 0) return -1;
        double p = 1013.25/(pressure/100);
        return (float) (153.84615*(pow(p,0.19) - 1)*(temperature+273.15));
    }

    DARTDebugPayload() = default;
};

#endif //MRAS_DARTDEBUGPAYLOAD_H
