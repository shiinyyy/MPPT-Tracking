#include <PWM.h>

int pin_PWM = 10;
const int pin_ADC1 = A0;
unsigned long duty = 0; 
const int Vref = 19;                // Reference voltage
int32_t frequency = 100000; // Hz

void setup() {
  InitTimersSafe();
  // Set frequency for pin
  bool success = SetPinFrequencySafe(pin_PWM, frequency);
  if(success) {
    pinMode(pin_PWM, OUTPUT);
    pinMode(pin_ADC1, INPUT);
    Serial.begin(9600);
  }
}

void loop() {
  // Read the value of the potentiometer
  int adcValue = analogRead(pin_ADC1);
  
  // Scale the value to match reference voltage range
  float voltage = (adcValue)/(5.0*1023.0); // Assuming 5V ADC reference
  
  // Adjust duty cycle based on reference voltage
  if (voltage > Vref) {
    duty -= 1; // Decrease duty cycle if voltage is higher than reference
  } else if (voltage < Vref) {
    duty += 1; // Increase duty cycle if voltage is lower than reference
  }

  // Ensure duty cycle stays within limits
  if (duty > 72) {
    duty = 72;                    // maximum 90%
  } 
  if (duty < 8) {                 // minimum 10%
    duty = 8;
  }

  // Update the PWM signal
  analogWrite(pin_PWM, duty);
  Serial.print("Duty Cycle: ");
  Serial.print(duty);
  Serial.println("%");
  delay(300); // Delay in between reads
}