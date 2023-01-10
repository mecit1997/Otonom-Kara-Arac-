#ifndef LOCATION_H_
#define LOCATION_H_
typedef struct{
    double distance;
    double angle;
    double location_result_latitude;
    double location_result_longitude;
    double latitude_destination;
    double longitude_destination;

}KonumDatalari_values_t;

#define motor1Pin1 14 
#define motor1Pin2 13
#define enable1Pin 15


#define motor2Pin1 11
#define motor2Pin2 10 
#define enable2Pin 12

const int freq = 30000;
#define pwmChannel 0
#define resolution 8
#define dutyCycle 200
#endif