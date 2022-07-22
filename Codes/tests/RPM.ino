#include <PID_v1.h>
#define ENCODEROUTPUTr 270
#define ENCODEROUTPUTl 300

const int HALLSEN_ml = 3;
const int HALLSEN_mr = 2;
const int M1A = 7;
const int M1B = 8;
const int M2A = 4;
const int M2B = 5;

//The sample code for driving one way motor encoder
volatile long encoderValuel = 0;
volatile long encoderValuer = 0;

int interval = 70;
long previousMillis = 0;
long currentMillis = 0;

float ml_rpm = 0,mr_rpm=0;;
boolean measureRpm = false;
int motorPwm = 0;
// For PID 

double inp,setp,outl,outr;

void setup() {

  Serial.begin(9600);//Initialize the serial port
  attachInterrupt(digitalPinToInterrupt(HALLSEN_ml), updateEncoderl, RISING);
  attachInterrupt(digitalPinToInterrupt(HALLSEN_mr), updateEncoderr, RISING);
//  EncoderInit();//Initialize the module
  
   pinMode( M1A , OUTPUT);
   pinMode( M1B , OUTPUT);
   pinMode(M2A,  OUTPUT);
   pinMode(M2B, OUTPUT);
   pinMode(11, OUTPUT);
   pinMode(10, OUTPUT);
   analogWrite(10, 255);
   analogWrite(11, 255);
   digitalWrite(M1A,HIGH);
   digitalWrite(M1B,LOW);
   digitalWrite(M2A,HIGH);
   digitalWrite(M2B,LOW);
   encoderValuel = 0;
   encoderValuer=0;
   setp=200;
   outl=0;
   outr=0;
   previousMillis = millis();
   
}

void loop() {
  // put your main code here, to run repeatedly:

  // Update RPM value on every second  


    // Only update display when there have readings

    currentMillis=millis();
    if (currentMillis-previousMillis >=interval){
      ml_rpm = (double)((double)encoderValuel * 60.000 / (double)ENCODEROUTPUTl)*(1000.0)/(double)interval;
    mr_rpm = (double)((double)encoderValuer * 60.000 / (double)ENCODEROUTPUTr)*(1000.0)/(double)interval;
    outl=(int)(outl+(setp - ml_rpm)*0.1)%255;
    outr=(int)(outr+(setp - mr_rpm)*0.1)%255;
    if(outl<0) outl=0;
    if(outr<0) outr=0;
    Serial.println(mr_rpm);
    //Serial.println(setp);  
//    Serial.println(outl);
//    Serial.println(outr);
    analogWrite(10,outr);
    analogWrite(11,outl);
    encoderValuel = 0;
    encoderValuer= 0;
    previousMillis=currentMillis;
    }
  

}

void EncoderInit()
{
 // Attach interrupt at hall sensor A on each rising signal
  attachInterrupt(digitalPinToInterrupt(HALLSEN_ml), updateEncoderl, RISING);
  attachInterrupt(digitalPinToInterrupt(HALLSEN_mr), updateEncoderr, RISING);

}


void updateEncoderl()
{
  // Add encoderValue by 1, each time it detects rising signal
  // from hall sensor A
  encoderValuel++;
}

void updateEncoderr()
{
  // Add encoderValue by 1, each time it detects rising signal
  // from hall sensor A
  encoderValuer++;
}
