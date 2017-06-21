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

#define EN_M  A1 // PIN A1
int a = 1;
float current = 0;
void setup() {
   Serial.begin(115200);
   init_motores(INA_M1,INB_M1,INA_M2,INB_M2,EN_M); 
   mover_motores(INA_M1, INB_M1, INA_M2, INB_M2, EN_M, PWM_M1, PWM_M2, 80, 0);
   delay(3000);
   apagar_motores(EN_M);
}

void loop() {
  
  
}


void init_motores(int ina_m1, int inb_m1, int ina_m2, int inb_m2, int en) {
    pinMode(ina_m1,OUTPUT);
    pinMode(inb_m1,OUTPUT);
    pinMode(ina_m2,OUTPUT);
    pinMode(ina_m2,OUTPUT);
    pinMode(en,OUTPUT); 
}

void apagar_motores(int en) {
    digitalWrite(en,0);
}

void mover_motores(int ina_m1, int inb_m1, int ina_m2, int inb_m2, int en, int pwm_m1, int pwm_m2, int pwm1, int pwm2) {
    digitalWrite(en,1); // enable motors
    if (pwm_m1 >= 0) {
        digitalWrite(ina_m1,0);
        digitalWrite(inb_m1,1);
        analogWrite(pwm_m1,pwm1);
    }
    else {
        digitalWrite(ina_m1,1);
        digitalWrite(inb_m1,0);
        analogWrite(pwm_m1,-pwm1);  
    } 
  
}

float m_cs(int cs_m) {
    float current = analogRead(cs_m)/1024*5;  
    return current;
}
