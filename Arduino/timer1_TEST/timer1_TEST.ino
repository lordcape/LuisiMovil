#include <PWM.h>

int32_t frequency = 20000; //frequency (in Hz)


void setup() {
    InitTimersSafe(); 
    bool success = SetPinFrequencySafe(12, frequency);
    pwmWrite(12, 128);
}

void loop() {
  // put your main code here, to run repeatedly:

}
