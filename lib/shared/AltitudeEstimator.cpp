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

/*
1. Deal with matrices, eigen might be useful 
2. Implement Newton Raphson method to derive altitude or research for other methods
3. Check with the team for other features to implement 
*/