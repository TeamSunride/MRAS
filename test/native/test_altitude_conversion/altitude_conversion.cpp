#include "unity.h"
#include "AltitudeEstimation.h"
#include <fstream>


void setUp(){}
void tearDown(){}


float error = 0.025; // 2.5%

void test_altitude_conversion_layer1(void)
{
    
   AtmosphericObject Rocket(1.77687e5);
   
   float delta = (float)(Rocket.get_altitude() - -5.00e3);
   

   TEST_ASSERT_TRUE(abs((delta/-5.00e3)) < error);
   


    return;
}

void test_altitude_conversion_layer2(void)
{
    
   AtmosphericObject Rocket(101325);
   
   float delta = (float)(Rocket.get_altitude() - -5.20301488e-13);
   

   TEST_ASSERT_TRUE(abs(delta) < error); //not tested for error as div by zero
   


    return;
}
void test_altitude_conversion_layer3(void)
{


   AtmosphericObject Rocket(2.26999e4);


   float delta = (float)(Rocket.get_altitude() - 1.10000103e+04);



   TEST_ASSERT_TRUE((abs(delta)/1.10000103e+04) < error);



    return;
}
void test_altitude_conversion_layer4(void)
{
    
   AtmosphericObject Rocket(5.52929e3);

   float delta = (float)(Rocket.get_altitude() - 2.00000009e+04);
 
   TEST_ASSERT_TRUE((abs(delta)/2.00000009e+04) < error);
  



    return;
}
void test_altitude_conversion_layer5(void)
{
    
    
  
   AtmosphericObject Rocket(8.89060e2);
   
   float delta = (float)(Rocket.get_altitude() - 3.20000019e+04);
   
   TEST_ASSERT_TRUE((abs(delta)/3.20000019e+04) < error);
   


    return;
}

void test_altitude_conversion_layer6(void)
{
    
   AtmosphericObject Rocket(1.10906e2);
  
   float delta = (float)(Rocket.get_altitude() - 4.73500593e+04);

  
   TEST_ASSERT_TRUE((abs(delta)/4.73500593e+04) < error);



    return;
}

void test_altitude_conversion_layer7(void)
{
    
    
  
   AtmosphericObject Rocket(7.04576e1);
   
   float delta = (float)(Rocket.get_altitude() - 5.10000220e+04);
   
   TEST_ASSERT_TRUE((abs(delta)/5.10000220e+04) < error);
   


    return;
}
void test_altitude_conversion_layer8(void)
{
    
    
  
   AtmosphericObject Rocket(4.47955);
   
   float delta = (float)(Rocket.get_altitude() - 7.09999610e+04);
   
   TEST_ASSERT_TRUE((abs(delta)/7.09999610e+04) < error);
   


    return;
}
void test_altitude_conversion_layer9(void)
{
    
    
  
   AtmosphericObject Rocket(1.05247);
   
   float delta = (float)(Rocket.get_altitude() - 7.99999687e+04);
   
   TEST_ASSERT_TRUE((abs(delta)/7.99999687e+04) < error);
   


    return;
}

void CSVwrite(void)
{
    std::ofstream altitudeFile;
    altitudeFile.open("test/native/test_altitude_conversion/altPressure.csv");

    for (int i = 110000; i > 1; i = i - 1000)
    {
        AtmosphericObject Rocket(i);
        altitudeFile << i << "," << Rocket.get_altitude() << "\n";
    }

    altitudeFile.close();
    printf("this ran @@@");
}

int main()
{
    CSVwrite();
    UNITY_BEGIN();
    RUN_TEST(test_altitude_conversion_layer1);
    RUN_TEST(test_altitude_conversion_layer2);
    RUN_TEST(test_altitude_conversion_layer3);
    RUN_TEST(test_altitude_conversion_layer4);
    RUN_TEST(test_altitude_conversion_layer5);
    RUN_TEST(test_altitude_conversion_layer6);
    RUN_TEST(test_altitude_conversion_layer7);
    RUN_TEST(test_altitude_conversion_layer8);
    RUN_TEST(test_altitude_conversion_layer9); 
    UNITY_END();
}