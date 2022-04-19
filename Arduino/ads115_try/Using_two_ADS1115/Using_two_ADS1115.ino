/***************************************************************************
* Example sketch for the ADS1115_WE library
*
* This sketch shows how to use two ADS1115 modules. In order to set the address, 
* connect the address pin to:
* 
* GND -> 0x48 (or leave unconnected)
* VCC -> 0x49
* SDA -> 0x4A
* SCL -> 0x4B
*/


#include<ADS1115_WE.h> 
#include<Wire.h>
#define I2C_ADDRESS_1  0x4A
//#define I2C_ADDRESS_2  0x49

ADS1115_WE adc_1 = ADS1115_WE(I2C_ADDRESS_1);
//ADS1115_WE adc_2 = ADS1115_WE(I2C_ADDRESS_2);

void setup() {
  Wire.begin();
  Serial.begin(9600);
  
  if(!adc_1.init()){
    Serial.print("ADS1115 No 1 not connected!");
  }
  adc_1.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc_1.setMeasureMode(ADS1115_CONTINUOUS); 
  adc_1.setCompareChannels(ADS1115_COMP_3_GND);
  
//  if(!adc_2.init()){
//    Serial.print("ADS1115 No 2 not connected!");
//  }
//  adc_2.setVoltageRange_mV(ADS1115_RANGE_6144);
//  adc_2.setMeasureMode(ADS1115_CONTINUOUS); 
//  adc_2.setCompareChannels(ADS1115_COMP_0_GND);
}

void loop() {
  float voltage = 0.0;
  
  voltage = adc_1.getResult_V();
  Serial.println("Voltage [V], ADS1115 No 1: ");
  Serial.println(voltage);

//  voltage = adc_2.getResult_V();
//  Serial.println("Voltage [V], ADS1115 No 2: ");
//  Serial.println(voltage);
 
  Serial.println("****************************");  
  delay(1000);
}
