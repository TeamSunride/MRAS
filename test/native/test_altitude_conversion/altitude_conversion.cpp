#include "unity.h"
#include "AltitudeEstimation.h"

void setUp(){}
void tearDown(){}


void test_altitude_conversion(void)
{
    int pressure = [101325, 80000, 22600, 10280, 5500];
    float altitude = [-5.20301488e-13,  1.94958557e+03, 1.10280719e+04,  1.60449752e+04, 2.00338957e+04];
    float error = 0.001;

    for (int i = 0; i < (sizeof(pressure)/sizeof(pressure[0])); i++)
    {
        AtmosphericObject Rocket(pressure(i));
        TEST_ASSERT_TRUE((Rocket.get_altitude() - altitude(i)) < error);
    }

    return;
}

/*
void test_layerValues(void)
{
    int pressure[10];


    for (int i = 0; i < 10; i++)
    {
        
    }
    
    return;
}
*/

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_altitude_conversion);
    UNITY_END();
}