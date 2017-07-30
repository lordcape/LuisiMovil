#include <SoftwareSerial.h>

SoftwareSerial mySerial(12, 11); // RX, TX

char rec = '0';

void setup() {
  /* serial init */
  mySerial.begin(9600);
  Serial.begin(115200);
  /* master intenta comunicarse con arduino unos 5 intentos*/
  //if(test_comm()) mySerial.println("LUISIMOVIL CONECTADO"); else {mySerial.println("*** COMM ERROR ***"); while(1){} }
}

void loop() {
  // put your main code here, to run repeatedly:

     while(mySerial.available() < 1){}
     rec = mySerial.read();
     Serial.println(rec);
     delay(20);

}

/* *** test_comm() *** */
/* Prueba 5 veces si le llega el comando 0xBA que seria el identificador del master */
/* Ej:
    mySerial.begin(9600);
    // master intenta comunicarse con arduino unos 5 intentos
    if(test_comm()) mySerial.println("LUISIMOVIL CONECTADO"); else {mySerial.println("*** COMM ERROR ***"); while(1){} }
*/
    
int test_comm() {
  
    int fail = 0;
    boolean test = 0;
    byte c;
    while(fail < 5){
        while(mySerial.available() < 1){}
        c = mySerial.read(); // 0xBA
	if(c == 0xBA){
            test = true;
            break;
        }
        else{
            fail++;
            mySerial.println(fail);
        }    
        }
        if(test) return 1; else return 0;
}
