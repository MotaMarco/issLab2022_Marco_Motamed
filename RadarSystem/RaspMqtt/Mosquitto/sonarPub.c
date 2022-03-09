
#include <mosquitto.h>
#include <iostream>
#include <wiringPi.h>
#include <fstream>
#include <cmath>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


#define TRIG 0
#define ECHO 2

#define CLOSE 18
#define MEDIUM 21
#define FAR 60

#define POS_LEFT 0.055
#define POS_RIGHT 0.24
#define POS_FORWARD 0.14
using namespace std;
struct mosquitto * mosq;

void setup() {
	//cout << "setUp " << endl;
	wiringPiSetup();
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);
	//TRIG pin must start LOW
	digitalWrite(TRIG, LOW);
	delay(30);
}

int getCM() {
	//Send trig pulse
	digitalWrite(TRIG, HIGH);
	delayMicroseconds(20);
	digitalWrite(TRIG, LOW);

	//Wait for echo start
	while(digitalRead(ECHO) == LOW);

	//Wait for echo end
	long startTime = micros();
	while(digitalRead(ECHO) == HIGH);
	long travelTime = micros() - startTime;

	//Get distance in cm
	int distance = travelTime / 58;

	return distance;
}

int setupMqtt(char *address,int port){
	mosquitto_lib_init();
	int rc;
	mosq = mosquitto_new("publisher-sonar", true, NULL);

	rc = mosquitto_connect(mosq, address, port, 60);
	if(rc != 0){
		printf("Client could not connect to broker! Error Code: %d\n", rc);
		mosquitto_destroy(mosq);
		return -1;
	}
	printf("We are now connected to the broker!\n");
}
void send(){
	int cm;
	char char_arr [100];
	while(1){
		cm = getCM();
		sprintf(char_arr, "%d", cm);
		mosquitto_publish(mosq, NULL, "sonar/t1", 4, char_arr, 0, false);
		sleep(0.2);
	}
	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);

	mosquitto_lib_cleanup();
}

int main(int argc,char **argv){
	int rc;
	
	int port=atoi(argv[2]);
	setup();
	setupMqtt(argv[1],port);
    
	send();
	
	return 0;
}