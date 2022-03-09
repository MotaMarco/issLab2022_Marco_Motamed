#include <stdio.h>
#include <mosquitto.h>

int main(int argc,char **argv){
	int rc;
	struct mosquitto * mosq;

	mosquitto_lib_init();

	mosq = mosquitto_new("publisher-test", true, NULL);

	rc = mosquitto_connect(mosq, "localhost", 5000, 60);
	if(rc != 0){
		printf("Client could not connect to broker! Error Code: %d\n", rc);
		mosquitto_destroy(mosq);
		return -1;
	}
	printf("We are now connected to the broker!\n");

	mosquitto_publish(mosq, NULL, "test/t1", 6, argv[1], 0, false);

	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);

	mosquitto_lib_cleanup();
	return 0;
}
