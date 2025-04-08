#ifndef DataLogger_h
#define DataLogger_h
#include <ArduinoJson.h>
//#include "DHTesp.h"


#include "RTC.h"
DS1307_RTC Myrtc;

#include "MicroSD.h"
MicroSD MSD;

#include "Json.h"
JsonClass Json;

#include "Actuators.h"
Actuators ACT;

#include "Sensors.h"
Sensores SEN;

#include "Tasks.h"
millis_tasks Tasks;



#endif