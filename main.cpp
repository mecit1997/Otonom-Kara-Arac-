#include"Arduino.h"
#include"location.h"
#include<stdio.h>
#include <iostream>

#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

/*Wi-Fi*/
AsyncWebServer server(80);

// REPLACE WITH YOUR NETWORK CREDENTIALS
const char* ssid     = "MCD";
const char* password = "mecidinternet";

const char* PARAM_INPUT_1 = "input1";
const char* PARAM_INPUT_2 = "input2";
const char* PARAM_INPUT_3 = "input3";

// HTML web page to handle 3 input fields (input1, input2, input3)
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <h2>Innovate Yourself<h2>
  <h3>  HTML Form ESP32</h3>
  <form action="/get">
    Latitude: <input type="text" name="input1"><br>
    Longitude: <input type="text" name="input2"><br>
    <input type="submit" value="Submit">
  </form><br>
  https://www.google.com/maps/place/40%C2%B055'02.0%22N+29%C2%B013'17.7%22E/@40.917225,29.221579,17z
</body></html>)rawliteral";


void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}





extern double get_angle();
extern void lat_long();
extern double dist(double,double,double,double);
extern double calcAngle(double,double,double,double);
extern void dest(char);
KonumDatalari_values_t KonumValues;
extern void right_wheel_forward();
extern void left_wheel_forward();
extern void forward();
extern void right_wheel_stop();
extern void left_wheel_stop();
extern double get_latitude();
extern double get_longitude();
static double pusula_acisi;
String dest_latitude;
String dest_longitude;
extern void print_speed();
extern void lat_long();

void setup(void) 
{
  Serial.begin(9600);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("ESP32","Arac123456");
  //WiFi.begin(ssid, password);
  Serial.print("IP address:");
  Serial.println(WiFi.softAPIP());

 /* if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }*/
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  
  
  // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;

    Serial.println(request->getParam(PARAM_INPUT_1)->value());
    Serial.println(request->getParam(PARAM_INPUT_2)->value());
    
    dest_latitude = request->getParam(PARAM_INPUT_1)->value();
    dest_longitude = request->getParam(PARAM_INPUT_2)->value();

    KonumValues.latitude_destination  = (double)dest_latitude.toFloat();
    KonumValues.longitude_destination = (double)dest_longitude.toFloat();




    request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                     + inputParam + ") with value: " + inputMessage +
                                     "<br><a href=\"/\">Return to Home Page</a>");


  });
  server.onNotFound(notFound);
  server.begin();


  Serial.println("HMC5883 Magnetometer Test"); Serial.println("");
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  
  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(enable1Pin, pwmChannel);
  ledcWrite(pwmChannel, dutyCycle);

  /*Motor 2*/
   //ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(enable2Pin, pwmChannel);
  ledcWrite(pwmChannel, dutyCycle);

}




void loop(void) 
{
    KonumValues.location_result_latitude = get_latitude();
    KonumValues.location_result_longitude = get_longitude();

   /*DEBUG*/
    Serial.printf("lat dest: %f\n",KonumValues.location_result_latitude); 
    Serial.printf("long dest: %f\n ",KonumValues.location_result_longitude);



    lat_long();
    pusula_acisi = get_angle();
    KonumValues.angle = calcAngle(KonumValues.location_result_latitude,KonumValues.location_result_longitude,
      KonumValues.latitude_destination, KonumValues.longitude_destination);

    Serial.printf("KonumValues.angle= %f\n ",KonumValues.angle);

    //Calculates the Distance Between Car and Destination
    KonumValues.distance = dist(KonumValues.location_result_latitude, KonumValues.location_result_longitude,
                            KonumValues.latitude_destination, KonumValues.longitude_destination);

    if(KonumValues.latitude_destination >25 && KonumValues.longitude_destination >25)
    {










    if(pusula_acisi < KonumValues.angle){
      Serial.printf("deneme");
      delay(500);
        left_wheel_forward();
        right_wheel_stop();
    }
    if(pusula_acisi > KonumValues.angle){
      delay(500);
      Serial.printf("deneme2");
      right_wheel_forward();
      left_wheel_stop();
    }
    if(pusula_acisi < (KonumValues.angle + 15) && pusula_acisi > (KonumValues.angle - 15)){
      right_wheel_forward();
      left_wheel_forward();
    }
    if(KonumValues.distance < 10){
      left_wheel_stop();
      right_wheel_stop();
    }
    }


}