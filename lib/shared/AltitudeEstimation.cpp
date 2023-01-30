// Written by Nikilesh

#include "AltitudeEstimation.h"

// constructor
AtmosphericObject::AtmosphericObject(float pressure)
{
    
    // initializing the layer constant matrix
    // TODO: Check the values for base pressure.
    layers << -5.00e3,    360.65,   -6.50e-3,   1.77687e5,
            0.00e3,     288.15,     -6.50e-3,   1.01325e5,
            11.00e3,    216.65,     0.00e-3,    2.26999e4,
            20.00e3,    216.65,     1.00e-3,    5.52929e3,
            32.00e3,    228.65,     2.80e-3,    8.89060e2,
            47.00e3,    270.65,     0.00e-3,    1.10906e2,
            51.00e3,    270.65,     -2.80e-3,   7.04576e1,
            71.00e3,    214.65,     -2.00e-3,   4.47955,
            80.00e3,    196.65,     -2.00e-3,   1.05247;
        
    layer_const = get_layer_constants(pressure);
    geometric_alt = altitude(pressure);
}

int AtmosphericObject::To_geopotential(int alt)
{

    return RADIUS_OF_EARTH*alt/(RADIUS_OF_EARTH + alt);
}

float AtmosphericObject::get_altitude()
{
    return geometric_alt;
}



float AtmosphericObject::altitude(int p)
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

Eigen::Vector4f AtmosphericObject::get_layer_constants(int p)
{
    int rows = layers.rows();
    Eigen::Vector4f _layer_const; 
    _layer_const << 0, 0, 0, 0;


    int i = 0;
    while(p < layers(i, 3) && i < rows)
    {
       
        _layer_const(0) = layers(i, 0);
        _layer_const(1) = layers(i, 1);
        _layer_const(2) = layers(i, 2);
        _layer_const(3) = layers(i, 3);
    
        i++;
    }

    return _layer_const; // TODO: returns zero vector if alt is not within the limit, FIX this
}

/*
TODO:
1. Deal with matrices, eigen might be useful >>>> Done
2. Implement Newton Raphson method to derive altitude or research for other methods >>>>> Maybe not needed
3. Check with the team for other features to implement >>>>> Pending
4. write tests >>>> Pending
*/


