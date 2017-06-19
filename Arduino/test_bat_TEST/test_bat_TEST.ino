

void setup() {
  /* serial init */
  Serial.begin(115200);
  /* se mide la bateria antes del uso del auto */
  if(test_bat()) Serial.println("BAT OK"); else Serial.println("*** BAT ERROR ***"); 
}

void loop() {
  // put your main code here, to run repeatedly:

}

/* *** test_bat() *** */
/* Mide la batería y devuelve 1 si la tensión es mayor a 10 V. Prueba 5 veces si le llega el comando 0xBA que seria el identificador del master */
/* Ej:
    Serial.begin(115200);
    /* se mide la bateria antes del uso del auto */
    if(test_bat()) Serial.println("BAT OK"); else Serial.println("*** BAT ERROR ***"); 
*/
    
int test_bat (){

    int a = analogRead(2); // pin que mide la bateria
	int vbat = map(a,0,1024,0,14); // rango de medida de 0 a 14 V.
	if (vbat > 10) return 1;
	else return 0;
}
