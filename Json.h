#ifndef Json_h
#define Json_h


class JsonClass{
  public: 
  String FAC_Json (String, String);
};

String JsonClass::FAC_Json(String msg1, String msg2){
  String temp = "";
  DynamicJsonDocument JSON ( 1024 );         /* Objeto donde se alamcenará el JSON */
  JSON [ "Hora" ] = msg1;             /* Almacena números enteros o flotantes */         
  JSON [ "Fecha" ] = msg2;

delay(2000);
  float humedad = dht.readHumidity();
  float temperatura = dht.readTemperature();
  if((isnan(humedad))||(isnan(temperatura)))
  {
    Serial.println("error al leer datos");
    return "";
  }

  JSON["Humedad"]=humedad;
  JSON["Temperatura"]=temperatura;

  serializeJsonPretty( JSON, temp); 
  return temp;
}
#endif