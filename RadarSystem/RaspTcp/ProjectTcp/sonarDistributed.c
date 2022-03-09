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

int setupSocket(char *address,int port){
	int socket_desc, sock, read_size;
    struct sockaddr_in server;
    //int port=strtol(porta, NULL, 10);
	//uint32_t address;
	//memcpy(&address, indirizzo, 4);
	//CREATE SOCKET
	printf("Create the socket\n");
   	socket_desc=socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1)
    {
        printf("Could not create socket");
        return -1;
    }
    printf("Socket created\n");
	
	//BIND
    
    struct sockaddr_in  remote= {0};
    /* Internet address family */
    remote.sin_family = AF_INET;
    /* Any incoming interface */
    remote.sin_addr.s_addr = inet_addr(address);//htonl(INADDR_ANY);
    remote.sin_port = htons(port); /* Local port */
    if( bind(socket_desc,(struct sockaddr *)&remote,sizeof(remote))< 0)
    {
        //print the error message
        perror("bind failed.");
        return -1;
    }
    printf("bind done\n");
	return socket_desc;
}

int listenSocket(int socket_desc){
	//char client_message[200]= {0};
	int clientLen,sock;
	struct sockaddr_in client;
	//Listen
    listen(socket_desc, 3);
    //Accept and incoming connection
	printf("Waiting for incoming connections...\n");
	clientLen = sizeof(struct sockaddr_in);
	//accept connection from an incoming client
	sock = accept(socket_desc,(struct sockaddr *)&client,(socklen_t*)&clientLen);
	if (sock < 0)
	{
		perror("accept failed");
		return -1;
	}
	printf("Connection accepted\n");
    while(1)
    {
        // Send some data
		int cm = getCM();
        if( send(sock , &cm , sizeof(int) , 0 ) < 0)
        {
            printf("Send failed");
            return -1;
        }
        printf("Send value %d",cm);
        sleep(1);
    }
	close(sock);
}

int main(int argc,char *argv[]) {
	if(argc!=3){
		printf("Num argomenti errato");
		return -1;
	}else{
		int cm;
		setup();
		int port=atoi(argv[2]);
		int sock=setupSocket(argv[1],port);
		if(sock<0){
			printf("\nConnection Failed \n");
			return -1;
		}else{
			listenSocket(sock);
		}
	}
	
 	return 0;
}
