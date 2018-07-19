//
//Con esta clase definimos una forma facil de recibir y enviar mensajes a traves de comunicacion I2C

//Formas de Conexion: Master-(Slave*x)
#ifndef I2cCom_h
#define I2cCom_h
//#include "WConstants.h"
#include <Wire.h> 
#include <Arduino.h>

struct RouteI2c {
  uint8_t cmd;
  void (* functionPointer)();
};

class I2cCom{
  protected:
    uint8_t address;
    bool useCmd = true;
    uint8_t cmd = 0;

  public: 
    I2cCom();
    
    void init(uint8_t address, bool useCmd);

    uint8_t getAddress();
    bool getUseCmd();
    uint8_t getCmd();

    void sendMessage(String &msg);
    String readMessage();
};

#endif
