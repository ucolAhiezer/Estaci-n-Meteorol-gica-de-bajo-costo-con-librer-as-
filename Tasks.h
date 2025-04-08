#ifndef Tasks_h
#define Tasks_h
/*****************************************************************************************
*      DESCRIPCIÓN DE LA LIBRERÍA: El objetivo de esta librería es generar tiempos de    *
*       espera de ejecución sin la implementación de la función "delay()".               *
******************************************************************************************/

#define TIEMPO1 1000                 // Constante para indicar 1 segundo (1000 ms).
#define TIEMPO2 2000                 // Constante para indicar 2 segundos (2000 ms).
#define TIEMPO3 3000                 // Constante para indicar 3 segundos (3000 ms).
#define TIEMPO_RTC 1000
#define TIEMPO_MSD 10000
#define TIEMPO_LCD 2000
#define TIEMPO_SENS 2000



class millis_tasks {

  public:
    uint64_t tiempo_anterior1 = 0,   // Contador de tiempo que tendrá múltiplos de TIEMPO1.
             tiempo_anterior2 = 0,   // Contador de tiempo que tendrá múltiplos de TIEMPO2.
             tiempo_anterior3 = 0,   // Contador de tiempo que tendrá múltiplos de TIEMPO3.
             tiempo_actual = 0,      // Contador de tiempo que tendrá múltiplos de TIEMPO.
             tiempo_anterior_RTC = 0,
             tiempo_anterior_MSD = 0,
             tiempo_anterior_SENS = 0,
              tiempo_anterior_LCD = 0;
    
  public:

    void tarea1 ( void );            // Función que ejecuta una acción cada segundo.
    void tarea2 ( void );            // Función que ejecuta una acción cada dos segundos.
    void tarea3 ( void );            // Función que ejecuta una acción cada tres segundos.
    void actualizar_tareas (void );  // Función que actualiza el conteo obtenido de la función "millis()".
    void tarea_RTC ( void );
    void tarea_MSD ( void );
    void tarea_LCD ( void );
    void tarea_SENS ( void );


 
};

/*
   Al arranque del sistema la variable "tiempo_anterior1" tendrá el valor de 0, 
   cuando "tiempo_actual" sea igual a "TIEMPO1" es decir cuando hayan pasado
   1000 ms, "tiempo_anterior" tomará el valor de "tiempo_actual", para que la
   diferencia entre ellos siempre se cumpla cuando pase el tiempo asignado en "TIEMPO1".
*/


/*~~~~~~~~~~~~~~~~~~~~~~~~ tarea1 - Función que se ejecuta cada TIEMPO1( 1 SEGUNDO) ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_tasks :: tarea1 ( void ) {

  /*
      _____________________________________________
      | tiempo_actual | tiempo_anterior1 | TIEMPO1 |
      ----------------------------------------------
      |       0       |       0          |  1000   |
      ----------------------------------------------
      |       1       |       0          |  1000   |
      ----------------------------------------------
      |       2       |       0          |  1000   |
      ----------------------------------------------
      ----------------------------------------------
      |       3       |       0          |  1000   |
      ----------------------------------------------
      ----------------------------------------------
      | . . 1000      |       0          |  1000   |   Se cumple la condicional 1000 - 0 = 1000.
      ----------------------------------------------
      ----------------------------------------------
      |    10001      |       1000       |  1000   |
      ----------------------------------------------

  */

  if ( ( tiempo_actual - tiempo_anterior1 ) >= TIEMPO1 ){
    
    Serial.println ( "1.- Ejecutando tarea 1" );
    tiempo_anterior1 = tiempo_actual;

  }

}

/*~~~~~~~~~~~~~~~~~~~~~~~~ tarea2 - Función que se ejecuta cada TIEMPO2 ( 2 SEGUNDOS ) ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_tasks :: tarea2 ( void ) {
  if ( ( tiempo_actual - tiempo_anterior2 ) >= TIEMPO2 ){

     Serial.println ( "2.- Ejecutando tarea 2" );
     tiempo_anterior2 = tiempo_actual;

  }
 
}

void millis_tasks :: tarea_RTC ( void ) {
  if ( ( tiempo_actual - tiempo_anterior_RTC ) >= TIEMPO_RTC ){

     Serial.println ( "2.- Ejecutando tarea 2" );
     tiempo_anterior_RTC = tiempo_actual;

  }
 
}

void millis_tasks :: tarea_MSD ( void ) {
  if ( ( tiempo_actual - tiempo_anterior_MSD ) >= TIEMPO_MSD ){
    Myrtc.get_time();
    MSD.SaveFile(Json.FAC_Json(Myrtc.format_time(), Myrtc.format_date()));
    MSD.ReadFile();
     tiempo_anterior_MSD = tiempo_actual;

  }
 
}

void millis_tasks :: tarea_LCD ( void ) {
  if ( ( tiempo_actual - tiempo_anterior_RTC ) >= TIEMPO_LCD ){

     Myrtc.get_time();
     ACT.show_LCD(Myrtc.format_date(), Myrtc.format_time());
     tiempo_anterior_LCD = tiempo_actual;

  }
 
}




/*~~~~~~~~~~~~~~~~~~~~~~~~ tarea3 - Función que se ejecuta cada TIEMPO3 ( 3 SEGUNDOS ) ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_tasks :: tarea3 ( void ) {

  if ( ( tiempo_actual - tiempo_anterior3 ) >= TIEMPO3 ){

     Serial.println ( "3.- Ejecutando tarea 3" );
     tiempo_anterior3 = tiempo_actual;

  }
  
}

/*~~~~~~~~~~~~~~~~~~~~~~~~ actualizar_tareas - Función que actualiza el contador de "millis()" ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_tasks :: actualizar_tareas ( void ) {

  tiempo_actual = millis( );

}


void millis_tasks :: tarea_SENS ( void ) {

  if ( ( tiempo_actual - tiempo_anterior_SENS ) >= TIEMPO_SENS ){

     Serial.println ( SEN.LDR_read() );
     tiempo_anterior_SENS = tiempo_actual;

  }
  
}

#endif