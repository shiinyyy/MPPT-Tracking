#include <PWM.h>

int pin_PWM = 10;
const int pin_ADC1 = A0;
const int pin_ADC2 = A1;
unsigned long duty = 0;   //
float InValue = 0;
float OutValue = 0;
float PVstart = 0;
float PVnew = 0;
int32_t frequency = 100000; // Hz

// volatile unsigned long highTime = 0;      // start
// volatile unsigned long lowTime = 0;       // stop
// volatile unsigned long lastTime = 0;
// volatile bool measuringHigh = true;

void setup() {
  InitTimersSafe();
  // Set frequency for pin
  bool success = SetPinFrequencySafe(pin_PWM, frequency);
  if(success) {
    pinMode(pin_PWM, OUTPUT);
    pinMode(pin_ADC1, INPUT);
    pinMode(pin_ADC2, INPUT);
    Serial.begin(9600);
    // attachInterrupt(digitalPinToInterrupt(pin_PWM), measureDutyCycle, CHANGE);
  }
}

void loop() {
  InValue = analogRead(pin_ADC1)*(5.0/1023.0);
  
  OutValue = analogRead(pin_ADC2)*(5.0/1023.0);

  PVnew = InValue * OutValue;

  if(PVnew > PVstart) {
    duty += 1;
  } else {
    duty -= 1;
  }

  // delay in between reads
  if (duty > 40){                  // if value > 50%, keep 50% as maximum
    duty = 40;
  }
  if (duty < 8) {                  // if value < 10%, keep 10% as minimum
    duty = 8;
  }
  analogWrite(pin_PWM, duty);      // update the PWM signal
  PVstart = PVnew;

  Serial.print("Duty Cycle: ");
  Serial.print(duty);
  Serial.println("%");

  Serial.print("Vin: ");
  Serial.print(InValue);
  Serial.println("V");

  Serial.print("Vout: ");
  Serial.print(OutValue);
  Serial.println("V");
  delay(300); // delay in between reads
}