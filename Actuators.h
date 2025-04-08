#ifndef Actuators_h
#define Actuators_h
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd ( 0x27, 16, 2);
class Actuators{
public:
void init_LCD (void);
void show_LCD (String, String);
};

void Actuators :: init_LCD(void){
   lcd.init ( );
   lcd.backlight ( );
}


void Actuators :: show_LCD(String msg1, String msg2){
  lcd.clear();
   lcd.setCursor (0, 0);
   lcd.print(msg1);
   lcd.setCursor (0, 1);
   lcd.print(msg2);
}
#endif