#include <PWM.h>
#include <SoftwareSerial.h>


/*
   Prueba de M1 o de M2. Programar la funcion moverMotores con el valor de PWM1 y PWM2 deseado y enviar caracteres por BT para 
   arrancar o frenar los motores.
     Enviar 1 para mover.
     Enviar cualquier otro caracter para frenar.

*/

// M1

#define INA_M1  7
#define INB_M1  8
#define PWM_M1  11  // 9 for NANO, 11 for MEGA
#define CS_M1   A0

// M2

#define INA_M2  6
#define INB_M2  5
#define PWM_M2  10  // 10 for NANO, 12 for MEGA
#define CS_M2   A2

// M1 y M2

#define FREQUENCY 700 // pwm freq. Hz
#define EN_M  A1 // PIN A1
#define VEL_MAX 100 // max speed %


SoftwareSerial mySerial(13, 12); // RX, TX  // (13,12) en MEGA, (12,11) en el NANO

char a = 2;

void setup() {
   mySerial.begin(9600);
   mySerial.println("Mandar '1' para arrancar.  Para frenar mandar cualquier otro caracter.");
   init_motores(INA_M1,INB_M1,INA_M2,INB_M2,EN_M); 
   apagar_motores(EN_M);
}

void loop() {
   while (mySerial.available() < 1) {}  
     a = mySerial.read(); 
   
   
   switch(a) {
       case '1': mover_motores(INA_M1, INB_M1, INA_M2, INB_M2, EN_M, PWM_M1, PWM_M2, 50, 1);
                 mySerial.println("MOVIENDO...");
               //mySerial.println(analogRead(A0));
               break;
       default : apagar_motores(EN_M);
                 mySerial.println("DETENIDO");
               break;                
     
   }
      
}


void init_motores(int ina_m1, int inb_m1, int ina_m2, int inb_m2, int en) {
    InitTimersSafe();
    SetPinFrequencySafe(PWM_M1, FREQUENCY);
    SetPinFrequencySafe(PWM_M2, FREQUENCY);
    pinMode(ina_m1,OUTPUT);
    pinMode(inb_m1,OUTPUT);
    pinMode(ina_m2,OUTPUT);
    pinMode(inb_m2,OUTPUT);
    pinMode(en,OUTPUT); 
}

void apagar_motores(int en) {
    digitalWrite(en,0);
}

void mover_motores(int ina_m1, int inb_m1, int ina_m2, int inb_m2, int en, int pwm_m1, int pwm_m2, int pwm1, int pwm2) {
  
    digitalWrite(en,1); // enable motors
    int speed_m1 = 0;
    int speed_m2 = 0;
    
    if (pwm1 > 0) {
        digitalWrite(ina_m1,0);
        digitalWrite(inb_m1,1);
        speed_m1 = pwm1;
    }
    else if (pwm1 < 0) {
        digitalWrite(ina_m1,1);
        digitalWrite(inb_m1,0);
        speed_m1 = -pwm1;  
    }
    else{
        digitalWrite(en,0);  
    }    
    pwmWrite(PWM_M1, int(((constrain(speed_m1,0,VEL_MAX)) / 100.0) * 255.0));
    if (pwm2 > 0) {
        digitalWrite(ina_m2,0);
        digitalWrite(inb_m2,1);
        speed_m2 = pwm2;
    }
    else if (pwm2 < 0) {
        digitalWrite(ina_m2,1);
        digitalWrite(inb_m2,0);
        speed_m2 = -pwm2;  
    }
    else{
        digitalWrite(en,0);  
    }
    pwmWrite(PWM_M2, int(((constrain(speed_m2,0,VEL_MAX)) / 100.0) * 255.0)); 
   
}

float m_cs(int cs_m) {
    float current = analogRead(cs_m)*500.0/1024.0;  
    return current;
}
