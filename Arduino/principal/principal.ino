#include <PWM.h>
#include <SoftwareSerial.h>

// M1

#define INA_M1  7
#define INB_M1  8
#define PWM_M1  9 
#define CS_M1   A0

// M2

#define INA_M2  6
#define INB_M2  5
#define PWM_M2  10 
#define CS_M2   A2

// M1 y M2

#define FREQUENCY 700 // pwm freq. Hz
#define EN_M  A1      // PIN A1
#define VEL_MAX 80    // max speed %

SoftwareSerial mySerial(12, 11); // RX, TX 

char Buffer = 0;
int baseSpeed = 175;

void setup() {
    /* motores init */
    init_motores(INA_M1,INB_M1,INA_M2,INB_M2,EN_M);
    /* apago motores antes de hacer nada */
    apagar_motores(EN_M);
    /* serial init */
    mySerial.begin(9600);
    /* master intenta comunicarse con arduino unos 5 intentos*/
    if(test_comm()) mySerial.println("LUISIMOVIL CONECTADO"); else {mySerial.println("*** COMM ERROR ***"); while(1){} }
    delay(100);
    /* se mide la bateria antes del uso del auto */
    if(test_bat()) mySerial.println("BAT OK"); else {mySerial.println("*** BAT ERROR ***"); while(1){}; }
    delay(100);
    
}

void loop() {

    if(mySerial.available() > 0){
    
        Buffer = mySerial.read();delay(20);
        //mySerial.flush();

        switch (Buffer)
        {
          case 'F':
            mover_motores(INA_M1, INB_M1, INA_M2, INB_M2, EN_M, PWM_M1, PWM_M2, baseSpeed, baseSpeed);
            mySerial.println("CASO F");
            break; 
    
          case 'B':
            mover_motores(INA_M1, INB_M1, INA_M2, INB_M2, EN_M, PWM_M1, PWM_M2,  -baseSpeed, -baseSpeed);
            mySerial.println("CASO B"); 
            break;
    
          case 'L':
            mover_motores(INA_M1, INB_M1, INA_M2, INB_M2, EN_M, PWM_M1, PWM_M2,  baseSpeed, -baseSpeed);
            mySerial.println("CASO L"); 
            break;
    
          case 'R':
            mover_motores(INA_M1, INB_M1, INA_M2, INB_M2, EN_M, PWM_M1, PWM_M2,  -baseSpeed, baseSpeed);
            mySerial.println("CASO R"); 
            break;
    
          case 'G': /*Forward left*/
            mover_motores(INA_M1, INB_M1, INA_M2, INB_M2, EN_M, PWM_M1, PWM_M2,  1.2 * baseSpeed, 0.5 * baseSpeed);
            break;
    
          case 'I': /*  Forward Right */
            mover_motores(INA_M1, INB_M1, INA_M2, INB_M2, EN_M, PWM_M1, PWM_M2,  0.5 * baseSpeed, 1.2 * baseSpeed);
            break;
    
          case 'H': /*  Back Left  */
            mover_motores(INA_M1, INB_M1, INA_M2, INB_M2, EN_M, PWM_M1, PWM_M2,  -1.2 * baseSpeed, -0.5 * baseSpeed);
            break;
    
          case 'J':  /* Back Right  */
            mover_motores(INA_M1, INB_M1, INA_M2, INB_M2, EN_M, PWM_M1, PWM_M2,  -0.5 * baseSpeed, -1.2 * baseSpeed);
            break;

          default:
            apagar_motores(EN_M);
            mySerial.println("APAGAR"); 
            break;

        }
    }
  
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
    char c;
    while(fail < 5){
        while(mySerial.available() < 1){}
        c = mySerial.read(); // 0x6C
  if(c == 'l'){
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

/* *** test_bat() *** */
/* Mide la baterìa y la envía por BT. Si la tensiòn es < 10 V entonces el programa queda ahí. */

int test_bat (){
    int a = analogRead(A3); // pin que mide la bateria
    float vbat = a/1024.0*5.0; // rango de medida de 0 a 14 V.
    mySerial.println(vbat);
    //if (vbat > 10.0) return 1;
    if (vbat > 4) return 1;
    else return 0;
}

/* *** init_motores() *** */
/* Init de los pines de los puentes H. */

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

/* *** apagar_motores() *** */
/* Poner en bajo el ENABLE de los motores. */

void apagar_motores(int en) {
    digitalWrite(en,0);
}

/* *** mover_motores() *** */
/* Para mover los motores. La velocidad se da en porcentaje siendo el maximo VEL_MAX. */

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

