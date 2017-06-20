#include <SoftwareSerial.h>

SoftwareSerial mySerial(12, 11); // RX, TX

void setup() {
  /* serial init */
  mySerial.begin(9600);
  /* se mide la bateria antes del uso del auto */
  if(test_bat()) mySerial.println("BAT OK"); else {mySerial.println("*** BAT ERROR ***"); while(1){}; }
}

void loop() {
  // put your main code here, to run repeatedly:

}

/* *** test_bat() *** */
/* Mide la batería y devuelve 1 si la tensión es mayor a 10 V. Manda un float con la tensión medida. */
/* Ej:
    mySerial.begin(9600);
    // se mide la bateria antes del uso del auto 
    if(test_bat()) mySerial.println("BAT OK"); else {mySerial.println("*** BAT ERROR ***");while(1){} } 
*/
    
int test_bat (){

        int a = analogRead(2); // pin que mide la bateria
	float vbat = a/1024.0*5.0; // rango de medida de 0 a 14 V.
        mySerial.println(vbat);
	if (vbat > 10.0) return 1;
	else return 0;
}
