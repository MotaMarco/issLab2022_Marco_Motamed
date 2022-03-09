#include <stdio.h>
#include <stdlib.h>

#include <mosquitto.h>

struct mosquitto * mosqPLed;
struct mosquitto * mosqPRadar;

void on_connect(struct mosquitto *mosq, void *obj, int rc) {
	printf("ID: %d\n", * (int *) obj);
	if(rc) {
		printf("Error with result code: %d\n", rc);
		exit(-1);
	}
	mosquitto_subscribe(mosq, NULL, "sonar/t1", 0);
}

void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg) {
	printf("New message with topic %s: %s\n", msg->topic, (char *) msg->payload);
	mosquitto_publish(mosqPLed, NULL, "led/t1", 4, msg->payload, 0, false);
	mosquitto_publish(mosqPRadar, NULL, "radar/t1", 4, msg->payload, 0, false);

}


int main(int argc,char **argv) {
	//struct mosquitto *mosq;
    //mosq=setup();
    int port=atoi(argv[2]);

	int portLed=atoi(argv[4]);

	int portRadar=atoi(argv[6]);
	
    //listen(mosq,argv[1], port);
	int rc, id=12;

	mosquitto_lib_init();

	struct mosquitto *mosq;

	mosq = mosquitto_new("subscribe-sonar", true, &id);
	mosquitto_connect_callback_set(mosq, on_connect);
	mosquitto_message_callback_set(mosq, on_message);
	
	rc = mosquitto_connect(mosq, argv[1], port, 10);
	if(rc) {
		printf("Could not connect to Broker with return code %d\n", rc);
		return -1;
	}
	printf("SUB: We are now connected to the broker!\n");
	
	//CONTROLLER PUB led

	mosqPLed = mosquitto_new("publisher-led", true, NULL);

	rc = mosquitto_connect(mosqPLed, argv[3], portLed, 60);
	if(rc != 0){
		printf("Client could not connect to broker! Error Code: %d\n", rc);
		mosquitto_destroy(mosqPLed);
		return -1;
	}
	printf("PUB Led: We are now connected to the broker!\n");

	//Controller Pub Java
	mosqPRadar = mosquitto_new("publisher-radar", true, NULL);

	rc = mosquitto_connect(mosqPRadar, argv[5], portRadar, 60);
	if(rc != 0){
		printf("Client could not connect to broker! Error Code: %d\n", rc);
		mosquitto_destroy(mosqPRadar);
		return -1;
	}
	printf("PUB Radar: We are now connected to the broker!\n");
	
	//continue sub
	mosquitto_loop_start(mosq);
	printf("Press Enter to quit...\n");
	getchar();
	mosquitto_loop_stop(mosq, true);

	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);
	//pub led
	mosquitto_disconnect(mosqPLed);
	mosquitto_destroy(mosqPLed);

	//pub radar
	mosquitto_disconnect(mosqPRadar);
	mosquitto_destroy(mosqPRadar);

	//both
	mosquitto_lib_cleanup();

	return 0;
}