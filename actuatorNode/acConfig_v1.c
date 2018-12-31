#include "open62541.h"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <wiringPi.h>
#include <errno.h>

#define ACTUATOR_LED  4
UA_Boolean running = true;
/***********************************************************/
static void stopHandler(int sign) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_CLIENT, "Received Ctrl-C");
    running = 0;
}
/************* SET/RESET ACTUATOR *************************/
static void setActuator(bool bOverheat){
    if(bOverheat){
	  digitalWrite (ACTUATOR_LED, HIGH);
    }else{
	  digitalWrite (ACTUATOR_LED, LOW);
    }
}
/***************** MAIN LOOP ******************************/
int main(void) {
    //>>>>>>>>>>>>>>>>>>>>>>>>  INIT WIRING PI
     if(wiringPiSetup() == -1){
    	fprintf(stderr, "Unable to start WiringPi: %s\n", strerror (errno));
    return 1;
    }
    pinMode (ACTUATOR_LED, OUTPUT) ;
    //>>>>>>>>>>>>>>>>>>>>>>>>  INIT SERVER
    signal(SIGINT, stopHandler); /* catches ctrl-c */
    UA_ClientConfig config = UA_ClientConfig_default;
    config.timeout = 1000;
    UA_Client *client = UA_Client_new(config);
    UA_Variant value; /* Variants can hold scalar values and arrays of any type */
    UA_Variant_init(&value);

    /* Endless loop reading the server time */
    while(running) {

        UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://localhost:4840");
        if(retval != UA_STATUSCODE_GOOD) {
            UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_CLIENT, "Not connected. Retrying to connect in 1 second");
            sleep(1);
            continue;
        }
        /* NodeId of the variable holding the current time */
        const UA_NodeId nodeId =
                UA_NODEID_STRING(1, "OVERHEAT");

        retval = UA_Client_readValueAttribute(client, nodeId, &value);
        if(retval == UA_STATUSCODE_BADCONNECTIONCLOSED) {
            UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_CLIENT,
                         "Connection was closed. Reconnecting ...");
            continue;
        }
        if(retval == UA_STATUSCODE_GOOD &&
           UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_BOOLEAN])) {
           UA_Boolean rawdata = *(UA_Boolean *) value.data;
           setActuator(rawdata);   // set LED according to value
	}
        sleep(1);
    };

    /* Clean up */
    UA_Client_delete(client); /* Disconnects the client internally */
    return UA_STATUSCODE_GOOD;
}
