#ifndef _MEASUREMENT_H_
#define _MEASUREMENT_H_

enum MeasurementType {
    Pressure,
    Temperature,
    Acceleration,
    Rotation_Rate,
    Magnetic_Field,
    GPS
};

class Measurement {
    public:
        MeasurementType Type();
        float * value(unsigned int* count);
        Measurement(MeasurementType, float);
        Measurement(MeasurementType, float, float, float);
    private:
        float _value[3];
        MeasurementType type;
};
#endif