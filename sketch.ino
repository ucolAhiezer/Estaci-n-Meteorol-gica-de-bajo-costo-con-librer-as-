#include "DHT.h"

#define pinDHT 4
#define DHTTYPE DHT22

WiFiClient Cliente;
DHT dht(pinDHT, DHTTYPE);
/*
const int p0 = 34;
int valor = 0;
*/
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include <WiFi.h>
#include <HTTPClient.h>

Adafruit_MPU6050 mpu;



#include "DataLogger.h"


// Configuración de WiFi
const char* ssid = "INFINITUM712F_2.4";
const char* password = "z3FAW3EAMP";

// Configuración de WUnderground
const char* WEATHER_STATION_ID = "ICOLIMAC2"; // ID de tu estación en WUnderground
const char* API_KEY = "2f2eaea3"; // Tu API Key



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando...");
    }
    Serial.println("Conectado a WiFi!");

  /*// pinMode(p0, INPUT);
  while (!mpu.begin()) {
    Serial.println("MPU6050 not connected!");
    delay(1000);
  }
  Serial.println("MPU6050 ready!");
*/
  Serial.println("Hello, ESP32!");
  Myrtc.RTC_init();
  MSD.MicroSD_init();
  ACT.init_LCD();
  //ACT.show_LCD();

  //SEN.sensors_init();
    dht.begin();
    
    mpu.begin();

}

//sensors_event_t event;


void loop() {

    float tempC = dht.readTemperature();
    float tempF = (tempC * 9.0 / 5.0) + 32.0; 
 float  hum = dht.readHumidity();

    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        String serverPath = "https://rtupdate.wunderground.com/weatherstation/updateweatherstation.php?";
        serverPath += "ID=" + String(WEATHER_STATION_ID);
        serverPath += "&PASSWORD=" + String(API_KEY);
        serverPath += "&dateutc=now";  // Tiempo actual en UTC
        serverPath += "&tempf=" + String(tempF, 1);   // Temperatura en Fahrenheit
        serverPath += "&humidity=" + String(hum, 1);  // Humedad en %
        serverPath += "&baromin=29.92"; // Presión en inHg
        serverPath += "&action=updateraw";

        Serial.println("Enviando datos a WUnderground...");
        http.begin(serverPath);
        int httpResponseCode = http.GET();
        
        if (httpResponseCode > 0) {
            Serial.print("Respuesta del servidor: ");
            Serial.println(httpResponseCode);
        } else {
            Serial.print("Error en la conexión: ");
            Serial.println(httpResponseCode);
        }
        
        http.end();
    }
 // sensors_event_t acc, gcc, temp;
  // put your main code here, to run repeatedly:
  /*Myrtc.get_time();
  Myrtc.show_time();
  MSD.SaveFile();
  MSD.ReadFile();
  */
  //Json.FAC_Json();
  //Serial.println(Json.FAC_Json("Hola", "Test"));
  //Myrtc.get_time();
  MSD.SaveFile(Json.FAC_Json(Myrtc.format_time(), Myrtc.format_date()));
  MSD.ReadFile();
  Tasks.actualizar_tareas();
  //Tasks.tarea_MSD();
    Tasks.tarea_LCD();

  //delay(4000); // this speeds up the simulation

Tasks.tarea_SENS();
/*delay(2000);
  float humedad = dht.readHumidity();
  float temperatura = dht.readTemperature();
  if((isnan(humedad))||(isnan(temperatura)))
  {
    Serial.println("error al leer datos");
    return;
  }

  Serial.print("Humedad ");
  Serial.print(humedad);
  Serial.print("%");
  Serial.print("Temperatura");
  Serial.print(temperatura);
  Serial.println("°C");
*/
/*
valor = analogRead(p0);
  Serial.println(valor);
 // delay(200);
   Serial.print("LDR:");
   Serial.println(analogRead(p0));
  delay(1000);
*/
///////////////////EXITO
/*mpu.getAccelerometerSensor()->getEvent(&event);

 Serial.println("Rotation of x axes: ");
Serial.println((gcc.gyro.x)*180/3.14);
  delay(500);
  */
}
