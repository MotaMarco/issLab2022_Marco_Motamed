#include <iostream>
#include <wiringPi.h>
#include <fstream>
#include <cmath>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>

#define LED_BUILTIN 6
#define DLIMIT 20

struct mosquitto *mosq;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  wiringPiSetup();
  pinMode(LED_BUILTIN, OUTPUT);
}

void on_connect(struct mosquitto *mosq, void *obj, int rc) {
	printf("ID: %d\n", * (int *) obj);
	if(rc) {
		printf("Error with result code: %d\n", rc);
		exit(-1);
	}
	mosquitto_subscribe(mosq, NULL, "led/t1", 0);
}

void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg) {
	printf("New message with topic %s: %s\n", msg->topic, (char *) msg->payload);
  int cm=strtol((char *)msg->payload, NULL, 10);
  if(cm<DLIMIT){
     digitalWrite(LED_BUILTIN, HIGH);
  }else{
     digitalWrite(LED_BUILTIN, LOW);
  }
}

int setUp(char *address,int port){
  int rc,id=12;
  mosquitto_lib_init();
  mosq = mosquitto_new("subscribe-led", true, &id);
  mosquitto_connect_callback_set(mosq, on_connect);
  mosquitto_message_callback_set(mosq, on_message);
  
  rc = mosquitto_connect(mosq, address, port, 10);
  if(rc) {
      printf("Could not connect to Broker with return code %d\n", rc);
      return -1;
  }
}

int start(){
  mosquitto_loop_start(mosq);
  printf("Press Enter to quit...\n");
  getchar();
  mosquitto_loop_stop(mosq, true);

  mosquitto_disconnect(mosq);
  mosquitto_destroy(mosq);
  mosquitto_lib_cleanup();
}

int main(int argc,char **argv) {
	int rc, id=12;

    if(argc!=3){
      printf("Num argomenti errato");
      return -1;
	  }else{
      setup();
      int port=atoi(argv[2]);
      
      setUp(argv[1],port);

      start();
    }

	

	return 0;
}
