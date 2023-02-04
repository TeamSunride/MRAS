// Written by Nikilesh

#include "AltitudeEstimation.h"

// constructor
AtmosphericObject::AtmosphericObject(float pressure)
{
    
    // initializing the layer constant matrix
    layers << -5.00e3,    360.65,   -6.50e-3,   1.77687e5,
            0.00e3,     288.15,     -6.50e-3,   1.01325e5,
            11.00e3,    216.65,     0.00e-3,    2.26320e4,
            20.00e3,    216.65,     1.00e-3,    5.47487e3,
            32.00e3,    228.65,     2.80e-3,    8.68014e2,
            47.00e3,    270.65,     0.00e-3,    1.10906e2,
            51.00e3,    270.65,     -2.80e-3,   6.69384e1,
            71.00e3,    214.65,     -2.00e-3,   3.95639e0,
            80.00e3,    196.65,     -2.00e-3,   8.86272e-1;
        
    layer_const = get_layer_constants(pressure);
    geometric_alt = altitude(pressure);
}

int AtmosphericObject::To_geopotential(float alt)
{

    return RADIUS_OF_EARTH*alt/(RADIUS_OF_EARTH + alt);
}

float AtmosphericObject::get_altitude()
{
    return To_geopotential(geometric_alt);
}

float AtmosphericObject::altitude(float p)
{

   // if beta is non-zero
   float f_altitude = 0;
   if(layer_const(2) == 0)
   {
        f_altitude = layer_const(0) + (SPECIFIC_GAS_CONST * layer_const(1))/GRAVITY_ACCEL * log(layer_const(3)/p);
        return f_altitude;
   } 

    // if beta is zero
    float base = (float)(layer_const(3)/p);
    float power = (float)((layer_const(2)*SPECIFIC_GAS_CONST)/GRAVITY_ACCEL);
    f_altitude = layer_const(0) + (layer_const(1)/layer_const(2)) * (pow(base, power) -1);

    return f_altitude;
}

Eigen::Vector4f AtmosphericObject::get_layer_constants(float p)
{
    int rows = layers.rows();
    Eigen::Vector4f _layer_const; 
    _layer_const << 0, 0, 0, 0;

    


    int i = 0;
    while(p <= layers(i, 3) && i < rows)
    {
       
        _layer_const(0) = layers(i, 0);
        _layer_const(1) = layers(i, 1);
        _layer_const(2) = layers(i, 2);
        _layer_const(3) = layers(i, 3);
    
        i++;
    }

    return _layer_const; 
}



