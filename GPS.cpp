#include <Wire.h>
#include <TinyGPS++.h>


#define RXD2 18
#define TXD2 17
HardwareSerial neogps(1);

TinyGPSPlus gps;

void print_speed();
void lat_long();
double get_latitude();
double get_longitude();



void lat_long(){
    neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);
    boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (neogps.available())
    {
      if (gps.encode(neogps.read()))
      {
        newData = true;
      }
    }
  }

  //If newData is true
  if(newData == true)
  {
    newData = false;
    Serial.println(gps.satellites.value());
    //print_speed();
  }
  else
  {
    Serial.println("fail:");
  } 
}


void print_speed()
{
       
  if (gps.location.isValid() == 1)
  {
   //String gps_speed = String(gps.speed.kmph());

    Serial.println("Lat:");
    Serial.println(gps.location.lat(),6);

    Serial.println("Lng:");

    Serial.println(gps.location.lng(),6);

    Serial.println("Speed:");

    Serial.println(gps.speed.kmph());
    

    Serial.println("SAT:");
    Serial.println(gps.satellites.value());


    Serial.println("ALT:");

    Serial.println(gps.altitude.meters(), 0);

    
  }
  else
  {
  Serial.println("error");
  }  

}

double get_latitude(){
  return (gps.location.lat());
}

double get_longitude(){
  return (gps.location.lng());
}