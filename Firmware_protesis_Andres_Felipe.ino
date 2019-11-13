
#include <Servo.h>

Servo indicecorazon;                  //Declaración de servos
Servo anularmenique;


int sensor = 0;                    //VARIABLE DE SENSOR
          

int posminindice = 180;           //Posiciones minimas y maximas de servos para dedos indice y medio
int posmaxindice = 0;

int posminanular = 0;             //Posiciones minimas y maximas de servos para dedos anular y meñique
int posmaxanular = 180;

///////////////////////////////////////////////////////Variables para filtrado de señal

const int numReadings = 10;     //numerode lecturas a promediar

int readings[numReadings];      // array de lecturas
int readIndex = 0;              // indice de lectura actual
int total = 0;                  // total de lecturas

///////////////////////////////////////////////////////Variables para filtrado de señal

void setup() {

 
  indicecorazon.attach(2);                            //ASIGNACION DE PINES DE SALIDA PARA SERVOS
  anularmenique.attach(3);

  Serial.begin(9600);

}

void loop() {

  total = total - readings[readIndex];        //Se toma el promedio de 10 muestras de la señal para tener una lectura estable
  readings[readIndex] = analogRead(A3);
  total = total + readings[readIndex];                   
  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }



  sensor = map((total / numReadings), 0, 1023, 0, 10000);   //Se amplifica la señal 10 veces para hacer mas facil el filtrado
  Serial.println(sensor);                                   //Reporta el promedio calculado por serial
  

  if (sensor < 500 ) {                      //Cuando la lectura del sensor es menor a 500 los dedos se extienden
                                            //este valor de umbral de desactivación debe ser igual al tomado cuando 
                                            //el beneficiario relaja la extremidad
                                            
    indicecorazon.write(posminindice);               //POSICIONAMIENTO DE LOS DEDOS EN MODO EXTENDIDO
    anularmenique.write(posminanular);
    
    
    delay(50);
  }

  if (sensor > 500 && sensor < 3000) {         //Cuando la lectura del sensor esta entre 500 y 3000 
                                               //se acciona el servo correspondiente a los dedos indice y corazon

    indicecorazon.write(posmaxindice);                    //POSICIONAMIENTO DE LOS DEDOS INDICE Y CORAZON
    
    Serial.println("INDICE_CORAZON");                 //REPORTE DEL ESTADO POR PUERTO SERIAL
    
    delay(20);
  }


  if (sensor > 3500 && sensor < 6500) {        //Cuando la lectura del sensor esta entre 3500 y 6500 
                                               //se acciona el servo correspondiente a los dedos anular y meñique
    indicecorazon.write(posmaxindice); 
    anularmenique.write(posmaxanular);
                      //POSICIONAMIENTO DE LOS DEDOS 
    
    Serial.println("ANULAR_MEÑIQUE");          //REPORTE DEL ESTADO POR SERIAL
    
    delay(20);
  }

  delay(5);
}
