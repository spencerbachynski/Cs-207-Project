// Smooth RGB mood lamp
// Changes an RGB LED's color smoothly that only turns on 
// when it's dark around it.
// Author: Ricardo Ouvina
// Date: 19/07/2012
// Version: 2.0
// ---------------------------------------------------
// The brightness of the leds follows these equations:
// Red = sin(x)
// Green = sin(x + PI/3)
// Blue = sin(x + 2PI/3)
// for x from 0 to PI
// ---------------------------------------------------
// 
// Smooth RGB mood lamp with temperature fan
// added a motor to spin a fan when it gets hot. 
// Author: Spencer Bachynski
// Date: 10/04/20


float RGB[3];
int ldrPin = 0;     // LDR in Analog Input 0 to read the ambient light
int ambientLight;   // variable to store the value of the ambient light
int redLed   = 11;  // red LED in Digital Pin 11 (PWM)
int greenLed = 10;  // green LED in Digital Pin 10 (PWM)
int blueLed  = 9;   // blue LED in Digital Pin 9 (PWM)
int motor = 6;
float AnalogToVolts(int reading);
float VoltsToCelsius(float volts);
float CelsiusToFahrenheit(float Celsius);

void setup(){
  pinMode(redLed,OUTPUT);  // tell arduino it's an output
  pinMode(greenLed,OUTPUT);// tell arduino it's an output
  pinMode(blueLed,OUTPUT); // tell arduino it's an output
  pinMode(motor, OUTPUT);
  // set all the outputs to low 
  digitalWrite(redLed,LOW);
  digitalWrite(greenLed,LOW);
  digitalWrite(blueLed,LOW);
  Serial.begin(9600);
}

void loop()
{
 int reading;
  float volts;
  float Celsius;
  reading = analogRead(A1);
  volts = AnalogToVolts(reading);  
  Celsius = VoltsToCelsius(volts); 
 
  if (Celsius >= 21 && Celsius <= 24)
 {
  analogWrite(motor,50);
 }

  if (Celsius >24 && Celsius <= 27)
 {
  analogWrite(motor,90);
 }
  else if (Celsius > 27 && Celsius <= 30)
 {
  analogWrite(motor,150);
 }
 else if (Celsius > 30 )
 {
   analogWrite(motor,255);
 }
 else  
 {
  analogWrite(motor,0);
 }
delay(1500);
  
  for (float x=0;x<PI;x=x+0.00001)
  {
    RGB[0]=255*abs(sin(x*(180/PI)));           // calculate the brightness for the red led
    RGB[1]=255*abs(sin((x+PI/3)*(180/PI)));    // calculate the brightness for the green led
    RGB[2]=255*abs(sin((x+(2*PI)/3)*(180/PI)));// calculate the brightness for the blue led
    
    ambientLight=analogRead(ldrPin); // read an store the ambient light
    
 

    if(ambientLight>800)
    { // start only if the ambient light is very low
      //  write the brightness on the leds
      
      analogWrite(redLed,RGB[0]); 
      analogWrite(greenLed,RGB[1]);
      analogWrite(blueLed,RGB[2]);
    }
    else
    {
      digitalWrite(redLed,LOW);
      digitalWrite(greenLed,LOW);
      digitalWrite(blueLed,LOW);
    }
    
    for(int i=0;i<3;i++)
    {
      if(RGB[i]<3)
      {
        delay(50);
      }
    }
    delay(1);
  }
}

float AnalogToVolts(int reading)
{
  float volts;
  volts = reading/1023.0 * 5.0;  
  return volts; 
}

// conversion from volts to celsius
float VoltsToCelsius(float volts)
{
  float Celsius;
  Celsius = volts * 100.0 - 50.0;
  return Celsius;
}
