//ACA SE DEFINEN 2 COSAS
//---LOS METODOS QUE SE EJECUTAN EN ONRECEIVE Y ONREQUEST
//---TODAS LOS CONTROLADORES QUE SON LLAMADOS A TRAVES DE I2C

//
//METODOS sendData() y receiveData()
void sendData(){
  DEB_DO_PRINTLN(I2C_SEND_DATA);
  //Aca se confia que se ejecuto antes el mensaje receiveData()
  controllerCentralI2c(i2cCom.getCmd());
  //i2cCom.sendMessage(data);
}

void receiveData(int byteCount){
  DEB_DO_PRINTLN(I2C_REC_DATA);
  String dataReceived = i2cCom.readMessage();
  //Serial.println(dataReceived);
}

//
//CONTROLADORES
void getHumTemp(){
  String data = String("h=") + String(humTemp.getHumedad()) + String("|t=") + String(humTemp.getTemperatura());
  i2cCom.sendMessage(data);
}

void getLevelGp2(){
  String data = String("l=") + String(gp2.getLevel());
  i2cCom.sendMessage(data);
}

void getLevelLluvia(){
  String data = String("l=") + String(lluvia.getLevel());
  i2cCom.sendMessage(data);
}

void getLevelLlama(){
  String data = String("l=") + String(llama.getLevel());
  i2cCom.sendMessage(data);
}

void getLevelLuz(){
  String data = String("l=") + String(luz.getLevel());
  i2cCom.sendMessage(data);
}

