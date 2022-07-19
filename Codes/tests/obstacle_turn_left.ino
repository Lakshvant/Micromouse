#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
int flag=0;
volatile long eval=0;
void setup() {
  Serial.begin(115200);
  
  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
//  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
  pinMode(7, OUTPUT); //IN1 m1
  pinMode(8, OUTPUT); //IN2 m1
  pinMode(4, OUTPUT); // IN1 m2
  pinMode(5, OUTPUT); // IN2 m2
  pinMode(3, INPUT); // m2 yello enc
  pinMode(9, INPUT); //m2 green enc
//  digitalWrite(7,HIGH);
//  digitalWrite(8,LOW);
//  digitalWrite(4,HIGH);
//  digitalWrite(5,LOW);
  attachInterrupt(digitalPinToInterrupt(2),encd,RISING);
}


void loop() {
  VL53L0X_RangingMeasurementData_t measure;
    
  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
    if (measure.RangeMilliMeter < 150 ){
      eval=0;
      turn_left();
    }
    else if (measure.RangeMilliMeter >= 150) 
    {
       digitalWrite(7,HIGH);
    digitalWrite(8,LOW);
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    }
    
  } else {
    Serial.println(" out of range ");
  }
    
  delay(10);
}
void turn_left()
{
  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
  if (eval<=-150)
  {
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
    digitalWrite(5,LOW);
    digitalWrite(4,LOW);
    delay(1000);
    return ;
  }
  turn_left();
  
}


void encd()
{
  if (digitalRead(9))
  {
  eval++;
  }
  else
  {
    eval--;
  }
}
