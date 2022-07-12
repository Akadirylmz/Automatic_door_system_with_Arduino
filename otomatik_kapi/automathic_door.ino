
#include <Servo.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20,16,2);
int light = 0;
Servo servo_motor;
const int rgbLed1 = 5; 
const int rgbLed2 = 4; 
const int rgbLed3 = 3; 

int latch=11;  //STCP //74HC595
int clk=13; //SHCP
int data=12;   //DS
int buzzer=7;
int i = 0;

int numbers[] = {0b11111100, 0b01100000, 0b11011010, 0b11110010, 0b01100110, 0b10110110, 0b10111110,
0b11100000, 0b11111110, 0b11110110};

void setup()
{
  lcd.init();
  pinMode(A0, INPUT);
  servo_motor.attach(9, 500, 2500);
  pinMode(10, OUTPUT);
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  
  pinMode(rgbLed1, OUTPUT); 
  pinMode(rgbLed2, OUTPUT); 
  pinMode(rgbLed3, OUTPUT);  

  pinMode(latch,OUTPUT);
  pinMode(clk,OUTPUT);
  pinMode(data,OUTPUT);
}



void loop()
{
    light = analogRead(A0);
{
  digitalWrite(latch,LOW);  
  shiftOut(data,clk, LSBFIRST, numbers[i]);  
  digitalWrite(latch,HIGH);
}
  if (light > 500) {
    servo_motor.write(90);

    digitalWrite(rgbLed2, LOW); 
    digitalWrite(rgbLed1, HIGH); 
    digitalWrite(rgbLed3, LOW); 
    
    lcd.clear();
    lcd.print("KAPI KAPALI");
    digitalWrite(10, LOW);
    digitalWrite(2, HIGH);
    Serial.println(light);
    noTone(7);
    delay(500); 

    
  } else {
    servo_motor.write(0);

    digitalWrite(rgbLed2, HIGH); 
    digitalWrite(rgbLed1, LOW); 
    digitalWrite(rgbLed3, LOW);
    
    lcd.clear();
    lcd.print("KAPI ACIK");
    digitalWrite(10, HIGH);
    digitalWrite(2, LOW);
    Serial.println(light);
    tone(7, 523, 500); 
    delay(500); 
  }

  for(i = 0; i < 10; i++)
  {
     digitalWrite(latch,LOW);  
     shiftOut(data,clk, LSBFIRST, numbers[i]);  
     digitalWrite(latch,HIGH);
    delay(1000);
  }
  delay(500); 
  servo_motor.write(90);
}
