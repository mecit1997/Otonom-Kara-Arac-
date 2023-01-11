#include"math.h"
#include"location.h"
#include"Arduino.h"

#define TO_RAD (3.1415926536 / 180)
#define R 6371

double dist(double,double,double,double);
double calcAngle(double,double,double,double);
void dest(char);
void right_wheel_forward();
void left_wheel_forward();
void forward();
void right_wheel_stop();
void left_wheel_stop();



extern KonumDatalari_values_t KonumValues;

//The haversine formula determines the great-circle distance between two points on a sphere given their longitudes and latitudes

double dist(double th1, double ph1, double th2, double ph2){	 
															
double dx, dy, dz;
ph1 -= ph2;
ph1 *= TO_RAD, th1 *= TO_RAD, th2 *= TO_RAD;				//radian to degree
dz = sin(th1) - sin(th2);
dx = cos(ph1) * cos(th1) - cos(th2);
dy = sin(ph1) * cos(th1);
double res =asin(sqrt(dx * dx + dy * dy + dz * dz) / 2) * 2 * R*1000;
Serial.println("mesafe:");
Serial.println(res);
return asin(sqrt(dx * dx + dy * dy + dz * dz) / 2) * 2 * R*1000;
}
/*This functions calculates the angle between two points (from current location to destination location)*/

double calcAngle(double x1, double y1, double x2, double y2){
double X,Y;

X = cos(x2*TO_RAD) * sin((y2-y1)*TO_RAD);
Y = cos(x1*TO_RAD) * sin(x2*TO_RAD) - sin(x1*TO_RAD) * cos(x2*TO_RAD) * cos((y1-y2)*TO_RAD);

KonumValues.angle = atan2(X,Y);							//atan2 is the 2-argument arctangent
KonumValues.angle *= 180 / 3.1415926536;

if (KonumValues.angle < 0) {
	KonumValues.angle += 360;
}
Serial.println("Aci");
Serial.println( KonumValues.angle);
return KonumValues.angle;
}


/*This function starts the right wheel of the vehicle*/
void right_wheel_forward(){
digitalWrite(motor2Pin1, HIGH);
digitalWrite(motor2Pin2, LOW);
//delay(1000);
}

/*This function starts the left wheel of the vehicle*/
void left_wheel_forward(){
digitalWrite(motor1Pin1, HIGH);
digitalWrite(motor1Pin2, LOW);

}

/*This function starts both wheels so that vehicle moves forward*/
void forward(){
digitalWrite(motor1Pin1, HIGH);
digitalWrite(motor1Pin2, LOW);
digitalWrite(motor2Pin1, HIGH);
digitalWrite(motor2Pin2, LOW);
}

/*This function stops right wheel*/
void right_wheel_stop(){
digitalWrite(motor2Pin1, LOW);
digitalWrite(motor2Pin2, LOW);

}

/*This function stops left wheel*/
void left_wheel_stop(){
digitalWrite(motor1Pin1, LOW);
digitalWrite(motor1Pin2, LOW);
}
