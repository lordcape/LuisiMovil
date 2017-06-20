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

#define EN_M  15 // PIN A1

void setup() {
   Serial.begin(9600);
   init_motores(INA_M1,INB_M1,INA_M2,INB_M2,EN_M); 
   apagar_motores(EN_M);
}

void loop() {
  
  Serial.println(m_cs(CS_M1));
  delay(50);
  
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

float m_cs(int cs_m) {
    float current = analogRead(cs_m);  
    return current;
}
