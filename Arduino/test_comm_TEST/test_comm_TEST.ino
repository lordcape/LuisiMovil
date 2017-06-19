

void setup() {
  /* serial init */
  Serial.begin(115200);
  /* master intenta comunicarse con arduino unos 5 intentos*/
  if(test_comm()) Serial.println("LUISIMOVIL CONECTADO"); else Serial.println("*** COMM ERROR ***"); 
}

void loop() {
  // put your main code here, to run repeatedly:

}

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
