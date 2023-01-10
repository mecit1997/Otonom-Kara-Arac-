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



double dist(double th1, double ph1, double th2, double ph2){	//Haversine formülü, boylamları ve enlemleri verilen bir küre üzerindeki 
																//iki nokta arasındaki büyük daire mesafesini belirler
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


void dest(char dest_lat_long[30]){      //bu fonksiyona telefondan gelecek enlem boylam bufferlanacak

	char latitude_chr[15] , longitude_chr[15];
	int i , j , latitude_int , longitude_int ;
	float latitude_destination,longitude_destination;

	//Getting Latitude
	latitude_chr[0] = dest_lat_long[0];
	latitude_chr[1] = dest_lat_long[1];

	//Getting latitude values
	for(i=3 ; i<10 ; i++){
		latitude_chr[i-1] = dest_lat_long[i];
	}
	latitude_int = atoi(latitude_chr);



	//Getting Longitude
	longitude_chr[0] = dest_lat_long[10];
	longitude_chr[1] = dest_lat_long[11];

	//Getting longitude values
	for(j=13 ; j<20 ; j++){
		longitude_chr[j-11] = dest_lat_long[j];
	}
	longitude_int = atoi(longitude_chr);

	//Integer to float
	latitude_destination  = latitude_int;
	longitude_destination = longitude_int;

	//Converting float values

	/*****************************************************************/
	/*********************  Destination Values  **********************/
	/*****************************************************************/
	KonumValues.latitude_destination  = latitude_destination  / 1000000;
	KonumValues.longitude_destination = longitude_destination / 1000000;

}

void right_wheel_forward(){
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  //delay(1000);
}

void left_wheel_forward(){
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);

}

void forward(){
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void right_wheel_stop(){
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);

}

void left_wheel_stop(){
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
}