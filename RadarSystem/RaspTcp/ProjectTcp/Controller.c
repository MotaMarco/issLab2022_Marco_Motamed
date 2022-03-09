#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

short setupSocket(char *address,int port){
    int iRetval=-1;
    
    short hSocket;
    //int port=strtol(porta, NULL, 10);
	//uint32_t address;
	//memcpy(&address, indirizzo, 4);
    printf("Create the socket\n");
    //printf("%d %d",address,port);
    hSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(hSocket == -1)
    {
        printf("Could not create socket\n");
        return -1;
    }
    
    int ServerPort = port;
    struct sockaddr_in remote= {0};
    remote.sin_addr.s_addr = inet_addr(address); //Local Host
    remote.sin_family = AF_INET;
    remote.sin_port = htons(ServerPort);
    iRetval = connect(hSocket,(struct sockaddr *)&remote,sizeof(struct sockaddr_in));
    if(iRetval<0){
        return -1;
    }
    
    return hSocket;
}


int SocketReceive(int hSocket,int cm,short RvcSize)
{
    //while(1){
        int shortRetval = -1;
        
        struct timeval tv;
        tv.tv_sec = 5;  /* 20 Secs Timeout */
        tv.tv_usec = 0;
        if(setsockopt(hSocket, SOL_SOCKET, SO_RCVTIMEO,(char *)&tv,sizeof(tv)) < 0)
        {
            printf("Time Out\n");
            return -1;
        }
        shortRetval = recv(hSocket, &cm, RvcSize, 0);
        printf("Response %d\n",cm);
        return cm;
    //}
    
}

int SocketSend(int hSocket,int Rqst,short lenRqst)
{
    int shortRetval = -1;
    struct timeval tv;
    tv.tv_sec = 5;  /* 20 Secs Timeout */
    tv.tv_usec = 0;
    if(setsockopt(hSocket,SOL_SOCKET,SO_SNDTIMEO,(char *)&tv,sizeof(tv)) < 0)
    {
        printf("Time Out\n");
        return -1;
    }
    shortRetval = send(hSocket, &Rqst, lenRqst, 0);
    printf("Inviato %d\n",Rqst);
    return shortRetval;
}

//main driver program
int main(int argc, char *argv[])
{
    const DLIMIT=20;
    int socketSonar,socketLed,socketRadar;
    int portSonar=atoi(argv[2]);
    int portLed=atoi(argv[4]);
    int portRadar=atoi(argv[6]);
    socketSonar=setupSocket(argv[1],portSonar);
    if ( socketSonar < 0)
        {
            perror("connect failed.\n");
            return 1;
        }
    printf("Sucessfully conected with server sonar\n");
    socketLed=setupSocket(argv[3],portLed);
    if ( socketLed < 0)
        {
            perror("connect failed.\n");
            return 1;
        }
    printf("Sucessfully conected with server led\n");
    socketRadar=setupSocket(argv[5],portRadar);
    if ( socketRadar < 0)
        {
            perror("connect failed.\n");
            return 1;
        }
    printf("Sucessfully conected with server radar\n");
    int cm;
    int on;
    while(1){
        cm=SocketReceive(socketSonar, cm, sizeof(int));
        printf("WOW %d",cm);
        if(cm<DLIMIT){
            on=1;
        }else{
            on=0;
        }
        SocketSend(socketLed, on, sizeof(int));
        SocketSend(socketRadar, cm, sizeof(int));
    }
    
    return 0;
}