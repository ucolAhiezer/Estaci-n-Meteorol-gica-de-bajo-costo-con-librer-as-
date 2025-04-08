#ifndef Sensors_h
#define Sensors_h
#define LDR 34
class Sensores{
public:

void sensors_init(void);
uint16_t LDR_read(void);

};

void Sensores :: sensors_init(void){
 pinMode(LDR, INPUT);
}

uint16_t Sensores :: LDR_read(void){
 return analogRead(LDR);
 
}




#endif