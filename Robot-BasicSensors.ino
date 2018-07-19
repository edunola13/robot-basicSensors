#include <SPI.h>
#include <EEPROM.h>
//#include <MemoryFree.h>
//Serial.println(freeMemory());

// Uncomment to enable printing out nice debug messages.
#define DOMO_DEBUG
//#define DOMO_SPEED 9600
//#define USE_WDT 
//#define WDT_TIME WDTO_8S
#include "vendor/igniteit/arduino-general-use/common_initial.h"
#include "messages.h"

#include "vendor/igniteit/arduino-sensors-oo/AnalogSensor.h"
#include "vendor/igniteit/arduino-sensors-oo/AnalogSensor.cpp"
#include "vendor/igniteit/arduino-sensors-oo/HumTempDHT.h"
#include "vendor/igniteit/arduino-sensors-oo/HumTempDHT.cpp"
#include "vendor/igniteit/arduino-basic-oo/JsonHelper.cpp"
#include "vendor/igniteit/arduino-basic-oo/ElementAbstract.cpp"

HumTempDHT humTemp = HumTempDHT(4, 22);
AnalogSensor gp2 = AnalogSensor(0);
AnalogSensor lluvia = AnalogSensor(1);
AnalogSensor llama = AnalogSensor(2);
AnalogSensor luz = AnalogSensor(3);

#include "I2cCom.h"
#define SLAVE_ADDRESS 0x04
I2cCom i2cCom;

//Routes
void getHumTemp();
void getLevelGp2();
void getLevelLluvia();
void getLevelLlama();
void getLevelLuz();
#define routesSize 5
RouteI2c routes[routesSize]= {
  {1, getHumTemp},
  {2, getLevelGp2},
  {3, getLevelLluvia},
  {4, getLevelLlama},
  {5, getLevelLuz}
};
#include "general_controller_i2c.h"
#include "controllers.h"

//CONFIGURACION
//Tiempos de Actualizacion
uint16_t timeSensors= 30000;
//USO INTERNO
//Tiempos de Actualizacion
unsigned long lasttimeSensors= 0;

void setup() {
  //BASIC
  initialGeneric();
  //WIRE I2C
  DEB_DO_PRINTLN(INIT_I2C);
  i2cCom.init(SLAVE_ADDRESS, true);  
  Wire.onRequest(sendData);
  Wire.onReceive(receiveData);
}

void loop() {
  //El loop lo unico que hace es actualizar los sensores cada x cantidad de tiempo
  //Luego a traves de Wire recibe para ejecutar acciones
  actualizeSensors();
}

//ACTUALIZACION DE SENSORES
void actualizeSensors(){
  if(millis() - lasttimeSensors >= timeSensors || millis() - lasttimeSensors < 0){
    DEB_DO_PRINTLN(ACT_SEN);
    
    humTemp.updateSensor();
    gp2.updateSensor();
    lluvia.updateSensor();
    llama.updateSensor();
    luz.updateSensor(); 

    lasttimeSensors= millis();
  }
}
