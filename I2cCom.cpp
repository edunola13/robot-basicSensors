#include <Arduino.h>
#include <Wire.h> 
#include "I2cCom.h"

I2cCom::I2cCom(){
}

void I2cCom::init(uint8_t address, bool useCmd){
  this->address = address;
  this->useCmd = useCmd;
  Wire.begin(this->address);
}

uint8_t I2cCom::getAddress(){
  return this->address;
}
bool I2cCom::getUseCmd(){
  return this->useCmd;
}
uint8_t I2cCom::getCmd(){
  return this->cmd;
}

void I2cCom::sendMessage(String &msg){
  char copy[msg.length() + 1];
  msg.toCharArray(copy, msg.length() + 1);
  Wire.write(copy);
}

String I2cCom::readMessage(){
  uint8_t i = 0;  
  String dataReceived = String("");
  while(Wire.available()) {
    if(i == 0 && this->useCmd) {      
      this->cmd = Wire.read();
    } else {
      char c = Wire.read();
      dataReceived += c;
    }
    i++;
  }
  return dataReceived;
}

