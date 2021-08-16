#include <Wire.h>
#include <Adafruit_Sensor.h>

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include "DHT.h"
#define dhtPin 2  
DHT dht(2,DHT11);
#include <OneWire.h> 
#include <DallasTemperature.h>
OneWire oneWire(3);
#include <virtuabotixRTC.h>  
#define clkPin 6
#define datPin 7
#define rstPin 8
#define mtrPin 10
#define heatPin 9
#define viyolPin 11
virtuabotixRTC myRTC(clkPin,datPin,rstPin);
DallasTemperature ds18(&oneWire);
DeviceAddress ds18Adres;
float dstemp, mintemp=37.5, maxtemp=37.7;

int dhtemp,dhthum,menu=0,setting=0,viyolstart=0;
int viyolhours,viyolminutes,viyolseconds;
int firsthour,firstminute,firstsecond,firstday;
void setup() {
  Serial.begin(9600);
  dht.begin();
  ds18.begin();
 ds18.getAddress(ds18Adres, 0);
 ds18.setResolution(ds18Adres, 11);
lcd.begin();
pinMode(heatPin,OUTPUT);
pinMode(mtrPin,OUTPUT);

pinMode(viyolPin,INPUT);
digitalWrite(heatPin, HIGH);
digitalWrite(mtrPin,HIGH);
}

void loop() {
  sensorRead();
        int value=analogRead(A0);
        Serial.println(value);
  myRTC.updateTime();
  if(viyolstart==0){
    viyolhours=myRTC.hours;
    viyolminutes=myRTC.minutes;
    viyolseconds=myRTC.seconds;
    viyolstart=1;
      
    }
  
  checkTemp();
  buttonRead();
  checkViyol();
  

//if(dstemp<23)
//digitalWrite(heatPin, LOW);
//else 
//digitalWrite(heatPin, HIGH);


lcdPrint();
//lcd.backlight();
//lcd.home();
//lcd.print(myRTC.hours);
//lcd.print(":");
//lcd.print(myRTC.minutes);
//lcd.print(":");
//lcd.print(myRTC.seconds);
//lcd.print(" hum:");
//lcd.print(dhthum);
//lcd.setCursor(0,1);
//lcd.print("ds:");
//lcd.print(dstemp);
//lcd.print(" dht:");
//lcd.print(dhtemp);



 

 





}
void turnViyol(){
  while(digitalRead(viyolPin)==LOW){
       Serial.println("1. while'ın içindeyim motorun dönmesi lazım");
       lcd.print(Viyol Dönüyor);
  digitalWrite(mtrPin,LOW);  
    }
    
     
    while(digitalRead(viyolPin)==HIGH){
     Serial.println("2. while'ın içindeyim, motorun tekrar çalışması lazım");
    digitalWrite(mtrPin,LOW); 
    }
        digitalWrite(mtrPin,HIGH);
        Serial.println("2. whiledan çıkıldı, motorun durması lazım. ");
        
  
  
  }
  
void checkViyol(){
 
  int saat,dakika,san;
  
  saat=myRTC.hours - viyolhours;
  dakika=myRTC.minutes - viyolminutes;
  san=myRTC.seconds - viyolseconds;
  

  if (saat==4 && dakika==0 &&san>=0){
  lcd.clear();
  viyolstart=0;
  turnViyol();
  }
  }
void lcdPrint(){
  if(menu==0){
    lcd.backlight();
lcd.home();
if(myRTC.hours<10)
lcd.print("0");
lcd.print(myRTC.hours);

lcd.print(":");
if(myRTC.minutes<10)
lcd.print("0");
lcd.print(myRTC.minutes);
lcd.print(":");
if(myRTC.seconds<10)
lcd.print("0");
lcd.print(myRTC.seconds);
lcd.setCursor(9,0);
lcd.print("Nem:%");
lcd.print(dhthum);
lcd.setCursor(0,1);
lcd.print("Sic:");
lcd.print(dstemp);
lcd.print(" dht:");
lcd.print(dhtemp);
    
    }
   else if(menu==1){
        
        if(setting=0){
         /* saat ayarı*/ 
          lcd.clear();
          lcd.home();
          lcd.print("Saati ayarla");
          
          
          }
          else if(setting=1){
         /* sıcaklık ayarı*/ 
          
          
          
          }
           else if(setting=2){
         /* gün sayacı ayarı*/ 
          
          
          
          }
    
    } 
 
    }
  
  
  
  

void sensorRead(){
  
  ds18.requestTemperatures();
  dstemp = ds18.getTempC(ds18Adres);
  dhtemp=dht.readTemperature();
  dhthum=dht.readHumidity();
  }

  void checkTemp(){

    if(dstemp<=mintemp)
        digitalWrite(heatPin, LOW);
    else if(dstemp>=maxtemp)
        digitalWrite(heatPin, HIGH); 
   }

   void buttonRead(){
      int bvalue=analogRead(A0);
      if(bvalue>999)
        return;
      else if (bvalue>750){
        
        while(bvalue<999){
          lcd.clear();
          lcd.println("OK button pressed");
          delay(1000);
            bvalue=analogRead(A0); 

        
        }
      }
      else if(bvalue>670)
      while(bvalue<999){
          lcd.clear();
          lcd.println("Right button pressed");
          delay(1000);
            bvalue=analogRead(A0); 
        
        }

        else if(bvalue>530)
      while(bvalue<999){
          lcd.clear();
          lcd.println("Left button pressed");
          delay(1000);
            bvalue=analogRead(A0); 
        
        }
        

    
   }


   
