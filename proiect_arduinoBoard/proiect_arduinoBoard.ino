//COD PLACA ARDUINO MEGA 2560
#include "dht.h"
#define dht_apin A0 

//senzor temperatură și umiditate
dht DHT;
//transmitem catre modulul ESP8266
String str;
//snezor umiditate sol
int moisturePin = A1;
int sensorValue = 0;
int percentM = 0;
//led temperatura
int redPin = 9;
int greenPin = 10;
int bluePin = 11;
//led umiditate
int redPin1 = 12;
int greenPin1 = 13;
int bluePin1 = 8;
//led umiditate sol
int redPin2 = 2;
int greenPin2 = 3;
int bluePin2 = 4;
 
void setup(){
 
  Serial.begin(115200); 
  Serial1.begin(115200);
  delay(500);//Delay to let system boot
  Serial.println("Wait for accessing sensor...\n\n");
  delay(1000);//Wait before accessing Sensor
  
}
 
void loop(){
    DHT.read11(dht_apin);
    //umiditatea
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    if(DHT.humidity > 50.00 && DHT.humidity < 75.00){
      digitalWrite(greenPin1, HIGH);
      digitalWrite(redPin1, LOW);
      digitalWrite(bluePin1, LOW);
    }else{
      digitalWrite(greenPin1, LOW);
      digitalWrite(redPin1, HIGH);
      digitalWrite(bluePin1, LOW);
    }
    //temperatura
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.print("C  ");
    if(DHT.temperature > 20.00 && DHT.temperature < 40.00){
      digitalWrite(greenPin, HIGH);
      digitalWrite(redPin, LOW);
      digitalWrite(bluePin, LOW);
    }else{
      digitalWrite(greenPin, LOW);
      digitalWrite(redPin, HIGH);
      digitalWrite(bluePin, LOW);
    }
    //umiditatea solului
    sensorValue = analogRead(moisturePin);
    percentM = map(sensorValue, 1017, 244, 0 , 100);
    Serial.print("soil moisture =  ");
    Serial.print(percentM);
    Serial.println("% ");
    //Serial.print(sensorValue);
     if(percentM > 50 && percentM < 80){
      digitalWrite(greenPin2, HIGH);
      digitalWrite(redPin2, LOW);
      digitalWrite(bluePin2, LOW);
    }else{
      digitalWrite(greenPin2, LOW);
      digitalWrite(redPin2, HIGH);
      digitalWrite(bluePin2, LOW);
    }

    //transmitem datele catre modulul ESP8266 Wireless
    str = String(DHT.temperature) + String(DHT.humidity) + String(percentM);
    Serial1.println(str);
    
    //asteptam 10 secunde pana sa reaccesam senzorii si sa recitim datele
    delay(10000);
     
} 
