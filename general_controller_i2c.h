void controllerCentralI2c(uint8_t cmd){
  //Una vez que se realizo la lectura del mensaje I2C, en base al CMD elegimos la funcion a ejecutar.
  for(uint8_t i= 0; i < routesSize; i++){
    if(routes[i].cmd == cmd){      
      routes[i].functionPointer();
      break;
    }
  }
}
