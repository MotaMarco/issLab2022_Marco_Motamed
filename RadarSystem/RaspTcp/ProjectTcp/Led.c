#include <iostream>
#include <wiringPi.h>
#include <fstream>
#include <cmath>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define LED_BUILTIN 6

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  wiringPiSetup();
  pinMode(LED_BUILTIN, OUTPUT);
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
    remote.sin_addr.s_addr = inet_addr(address);
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
    int on;
    while(1)
    {
        //Receive a message from the client
        if( recv(sock, &on, sizeof(int), 0) < 0)
        {
            printf("recv failed");
            break;
        }
        printf("Client message : %d\n",on);
        if(on==0){
            printf("Client message : voglio spegnere");
            digitalWrite(LED_BUILTIN, LOW);
            printf("Client message : SPEGNITI");
        }else if(on==1){
            digitalWrite(LED_BUILTIN, HIGH); 
            printf("Client message : ACCENDI");
        }
        sleep(1);
    }
	close(sock);
}

int main(int argc,char *argv[]) {
	if(argc!=3){
		printf("Num argomenti errato");
		return -1;
	}else{
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
