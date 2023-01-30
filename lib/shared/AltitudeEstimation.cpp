// Written by Nikilesh

#include "AltitudeEstimation.h"

int AtmosphericObject::To_geopotential(int alt)
{

    return RADIUS_OF_EARTH*alt/(RADIUS_OF_EARTH + alt);
}

float AtmosphericObject::get_altitude()
{
    return geometric_alt;
}

// NOT SURE IF THIS IS SET UP PROPERLY
float AtmosphericObject::pressure()
{
    /* Layer constants = {Altitude, Temperature, Temp Gradient (Beta), Base pressure}*/
    geopotential_alt = To_geopotential(geometric_alt);

    /*If Beta is Non-zero the method to find the pressure is different than to when it is zero*/
    float p_pressure = 0;
    if(layer_const(2) == 0)
    {
        /*Check the equation !!!!*/
        p_pressure = layer_const(3)*exp(-(GRAVITY_ACCEL/(SPECIFIC_GAS_CONST*SEALEVEL_TEMP)) * (geopotential_alt - layer_const(0)));
        return p_pressure;
    }

    float base = 1 + (layer_const(2)/layer_const(1)) * (geopotential_alt - layer_const(0));
    float power = -GRAVITY_ACCEL/(layer_const(2)*SPECIFIC_GAS_CONST);
    p_pressure =  layer_const(3) * pow(base, power);
    //std::cout << "\ntesting: " << layer_const(0) << std::endl;
    return p_pressure;
}
/*
1. Deal with matrices, eigen might be useful 
2. Implement Newton Raphson method to derive altitude or research for other methods
3. Check with the team for other features to implement 
*/