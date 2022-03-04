#include <iostream>
#include <wiringPi.h>
#include <fstream>
#include <cmath>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 6666

#define TRIG 0
#define ECHO 2

#define CLOSE 18
#define MEDIUM 21
#define FAR 60

#define POS_LEFT 0.055
#define POS_RIGHT 0.24
#define POS_FORWARD 0.14
using namespace std;
/*
g++  SonarAlone.c -l wiringPi -o  SonarAlone
 */
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

int main(void) {
	int cm ;
	setup();

	 int sock = 0, valread;
    struct sockaddr_in serv_addr;
    
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "192.168.41.134", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
	int blink=0;
	while(1) {
		int tempo=1000;
		char buf[32];
 		cm = getCM();
		send(sock , &cm , sizeof(int) , 0 );
    		printf("Hello message sent\n");
		if(cm<20 && blink ==0){
                system("/home/pi/ledBlink.sh &"  );                
		blink =1;
                 //system("/home/pi/led25GpioTurnOn.sh");
                }
                if(cm>=20){
                 system("/home/pi/led25GpioTurnOff.sh");
		 blink =0;
                }
		printf("DOLGIO\n");
		cout <<  cm   << endl ;  //flush after ending a new line
		delay(tempo);
	}
 	return 0;
}
