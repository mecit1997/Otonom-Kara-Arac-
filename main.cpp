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

const char* PARAM_INPUT_1 = "input1"; //These are the input values on the web server
const char* PARAM_INPUT_2 = "input2"; //These will be used to get the location values;

/************************************************************/
/**HTML web page to handle 2 input fields (input1, input2)***/
/*******HTML page can be configured according to needs*******/
/*************************************************************/
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
</body></html>)rawliteral";


void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}



/**************************************/
/**********Function externs************/
/**************************************/
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
  WiFi.softAP("ESP32","Arac123456");  //ESP32 is set to be an access point so that users can connect with the described credentials
  Serial.print("IP address:");        //Prints the ip address to connect the web server
  Serial.println(WiFi.softAPIP());

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
    
    dest_latitude = request->getParam(PARAM_INPUT_1)->value();    //dest_latitude value is fetched from web server
    dest_longitude = request->getParam(PARAM_INPUT_2)->value();   //dest_longitude value is fetched from web server

    KonumValues.latitude_destination  = (double)dest_latitude.toFloat();  //convert string values to double
    KonumValues.longitude_destination = (double)dest_longitude.toFloat(); //convert string values to double




    request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                     + inputParam + ") with value: " + inputMessage +
                                     "<br><a href=\"/\">Return to Home Page</a>");


  });
  server.onNotFound(notFound);
  server.begin();

  /********************************************/
  /****L298N Motor Driver Pin Configuration****/
  /********************************************/
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  
  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(enable1Pin, pwmChannel);
  ledcWrite(pwmChannel, dutyCycle);

  
  ledcAttachPin(enable2Pin, pwmChannel);  //pwm resolution is set to 8 bits (0 to 255)
  ledcWrite(pwmChannel, dutyCycle);       //dutyCycle value is set in the header file
                                          //it could be changed for different speeds
}




void loop(void) 
{
  //Gets vehcile's location values 
    KonumValues.location_result_latitude = get_latitude();
    KonumValues.location_result_longitude = get_longitude();

    lat_long();
    pusula_acisi = get_angle(); //Get magnetometer angle
  
    //Calculate the angle between vehicle's location and destination location 
    KonumValues.angle = calcAngle(KonumValues.location_result_latitude,KonumValues.location_result_longitude,
      KonumValues.latitude_destination, KonumValues.longitude_destination);


    //Calculates the Distance Between Car and Destination
    KonumValues.distance = dist(KonumValues.location_result_latitude, KonumValues.location_result_longitude,
                            KonumValues.latitude_destination, KonumValues.longitude_destination);

    if(KonumValues.latitude_destination  && KonumValues.longitude_destination ) // if destination values was sent from the web server
    {                                                                           // then vehicle starts to move

      if(pusula_acisi < KonumValues.angle){  //to find the correct angle start to left wheel
          left_wheel_forward();
          right_wheel_stop();
      }
      if(pusula_acisi > KonumValues.angle){ //to find the correct angle start to right wheel
         right_wheel_forward();
         left_wheel_stop();
      }
      if(pusula_acisi < (KonumValues.angle + 15) && pusula_acisi > (KonumValues.angle - 15)){ // if the angle between car and destination is in the correct range
          right_wheel_forward();                                                              // then move forward
          left_wheel_forward();
      }
      if(KonumValues.distance < 5){ // if the distance between car and destination is less then 5 meters then stop the vehicle
          left_wheel_stop();
          right_wheel_stop();
      }
    }


}
