/* *** test_comm() *** */
/* Prueba 5 veces si le llega el comando 0xBA que seria el identificador del master */
/* Ej:
    Serial.begin(115200);
    // master intenta comunicarse con arduino unos 5 intentos
    if(test_comm()) Serial.println("LUISIMOVIL CONECTADO"); else Serial.println("*** COMM ERROR ***");
*/
    
int test_comm (){
  
    int fail = 0;
    boolean test = 0;
    byte c;
    while(fail < 5){
        while(Serial.available() < 1){}
        c = Serial.read(); // 0xBA
	if(c == 0xBA){
            test = true;
            break;
        }
        else{
            fail++;
        }    
        }
        if(test) return 1; else return 0;
}

/* *** test_bat() *** */
/* Mide la batería y devuelve 1 si la tensión es mayor a 10 V. Prueba 5 veces si le llega el comando 0xBA que seria el identificador del master */
/* Ej:
    Serial.begin(115200);
    // se mide la bateria antes del uso del auto 
    if(test_bat()) Serial.println("BAT OK"); else Serial.println("*** BAT ERROR ***"); 
*/
    
int test_bat (){

    int a = analogRead(2); // pin que mide la bateria
	int vbat = map(a,0,1024,0,14); // rango de medida de 0 a 14 V.
	if (vbat > 10) return 1;
	else return 0;
}