#include <ADS1X15.h>
#include <DallasTemperature.h>
#include <EEPROM.h>
#include "GravityTDS.h"
#include <OneWire.h>
#include <Adafruit_MLX90614.h>

#define one_wire_bus 4
ADS1115 ads(0x48);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();


namespace sensors{

  void ads_init(){
	int fail_count = 0;
    while(!ads.begin()){
      fail_count = fail_count + 1;
      Serial.println("Failed to Initialize ADS");
      Serial.println("Program Halt");
      if (fail_count > 10){break;}
    }
  Serial.println("ADS successfully initialized");
  }

  int16_t read_int(int chnum) {
    int16_t readval;    
    readval = ads.readADC(chnum);
    return readval;
  }
  void sensors_init(){
    
  }
  float get_temp(){
  	float temperature = 25;
    mlx.begin();
    temperature = mlx.readObjectTempC();
    return temperature;
  }

  float get_tds(){
  	float tds = 0;
  	return tds;
  }

  float get_flow(){
  	float flow = 0;
  	return flow;
  }
  
}
