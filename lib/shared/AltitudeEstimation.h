/*
    Written by Nikilesh Ramesh
*/



#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include "eigen.h"

// ----------- Constants ------- //
#define GAS_CONST 8.31446261815324 // Universal Gas Constant [J/(K*mol)] 
#define SPECIFIC_GAS_CONST 287.05287 // Gas Constant for air
#define GRAVITY_ACCEL 9.80665   // Gravitational acceleration [m/s^2]
#define SEALEVEL_PRESSURE 101325 // P0, sea level pressure [Pa]
#define SEALEVEL_TEMP 288.15 // sea level temperature [K]
#define AVAGADRO_CONST 6.02214076e23 // Avagadro's Constant
#define SEALEVEL_MOLARMASS  28.964420e-03 // (NOT PRIMARY, DERIVED) Molar mass of air at sea level [kg/mol]
#define SPECIFIC_GAS_CONST 287.05287 // specific gas constant (Assumed constant)
#define RADIUS_OF_EARTH 6356766     //See references for this number

// --- Other Definitions ---- // 

#define BASE_PRESSURE layer_const(0)
// to be completed, to tidy up the code....



/**
A class that calculates the altitude from the pressure values, using the ICAO 1993 standard. 
*/
class AtmosphericObject
{
    public:

        AtmosphericObject(float pressure); // constructor
        float get_altitude();
        float get_temperature();
        Eigen::Vector4f get_layer_constants(float p); 
        int To_geopotential(float alt); // additional feture to be added, right now everything is in geometric
        
    private:

        // Modifiable values
        int geometric_alt;
        int geopotential_alt;
        Eigen::Vector4f layer_const; 

        float altitude(float p);
        // matrix of layer constants
        // each Layer  =  {Geopotential [m], Temperature [K], Temp Gradient[K/m]} 
       Eigen::Matrix<float, 9, 4> layers;
        
        
};