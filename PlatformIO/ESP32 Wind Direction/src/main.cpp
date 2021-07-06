// FOR ADC MCU 12 BIT. IF YOUR MCU 10 BIT, JUST CHANGE 512 TO 128 
#include <Arduino.h>
#include <stdio.h>

#define DIRECTION_DIVIDER 45

String Wind_Direction;
String Last_Wind_Direction;
int Degree;
int Sensor_Pin = 36;
char *Hasil_Pembacaan;
int Threshold_Direction;
int Temp[20],counter;
int LastDegree;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Sensor_Pin , INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Degree = analogRead(Sensor_Pin);
  // if(abs(Degree - LastDegree) > DIRECTION_DIVIDER){  
    // Degree = LastDegree;
  // }
  // Temp = ;
  Serial.print("Hasil Baca Sensor Gua = ");
  Serial.println(Degree);
  // Wind_Direction = Degree/THRESHOLD_DIRECTION;
  for(int i=0; i<8; i++){
    Threshold_Direction = abs(Degree-(DIRECTION_DIVIDER*i));
    if((i==0 && Threshold_Direction<20) || (i==7 && Threshold_Direction>20 && Threshold_Direction<45)){
      counter++;
      if(counter >= 10){ 
        Wind_Direction = "Utara";
        counter=0;
        Last_Wind_Direction = Wind_Direction;
      }
      else
        Wind_Direction = Last_Wind_Direction;
    }
    else if((i==1 && Threshold_Direction<20) || (i==2 && Threshold_Direction>20 && Threshold_Direction<45)){
      counter++;
      if(counter >= 10){ 
        Wind_Direction = "Timur Laut";
        counter=0;
        Last_Wind_Direction = Wind_Direction;
      }
      else
        Wind_Direction = Last_Wind_Direction;
    }
    else if((i==2 && Threshold_Direction<20) || (i==3 && Threshold_Direction>20 && Threshold_Direction<45)){
      counter++;
      if(counter >= 10){ 
        Wind_Direction = "Timur";
        counter=0;
        Last_Wind_Direction = Wind_Direction;
      }
      else
        Wind_Direction = Last_Wind_Direction;
    }
    else if((i==3 && Threshold_Direction<20) || (i==4 && Threshold_Direction>20 && Threshold_Direction<45)){
      counter++;
      if(counter >= 10){ 
        Wind_Direction = "Tenggara";
        counter=0;
        Last_Wind_Direction = Wind_Direction;
      }
      else
        Wind_Direction = Last_Wind_Direction;
    }
    else if((i==4 && Threshold_Direction<20) || (i==5 && Threshold_Direction>20 && Threshold_Direction<45)){
      counter++;
      if(counter >= 10){ 
        Wind_Direction = "Selatan";
        counter=0;
        Last_Wind_Direction = Wind_Direction;
      }
      else
        Wind_Direction = Last_Wind_Direction;
    }
    else if((i==5 && Threshold_Direction<20) || (i==6 && Threshold_Direction>20 && Threshold_Direction<45)){
      counter++;
      if(counter >= 10){ 
        Wind_Direction = "Barat Laut";
        counter=0;
        Last_Wind_Direction = Wind_Direction;
      }
      else
        Wind_Direction = Last_Wind_Direction;
    }
    else if((i==6 && Threshold_Direction<20)|| (i==7 && Threshold_Direction>20 && Threshold_Direction<45)){
      counter++;
      if(counter >= 10){ 
        Wind_Direction = "Barat";
        counter=0;
        Last_Wind_Direction = Wind_Direction;
      }
      else
        Wind_Direction = Last_Wind_Direction;
    }
    else if(i==7 && Threshold_Direction<20){
      counter++;
      if(counter >= 10){ 
        Wind_Direction = "Barat Daya";
        counter=0;
        Last_Wind_Direction = Wind_Direction;
      }
      else
        Wind_Direction = Last_Wind_Direction;
    }
    else
      Wind_Direction = Last_Wind_Direction;
  }
  Serial.print("Threshold Gua = ");
  Serial.println(Threshold_Direction);
  Serial.print("Arah Angin Gua = ");
  Serial.println(Wind_Direction);
  LastDegree = Degree;
  // delay(1000);
}