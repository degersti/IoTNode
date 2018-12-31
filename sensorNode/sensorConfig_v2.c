#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include "addWriteVar.h"
#include "open62541.h"

UA_Boolean 	running = true;
UA_Double	dTemp;
UA_Boolean	bOverheat;
int		fd;
/********************* CLOSE SERVER ON CTRL-C ****************************/
static void stopHandler(int sign) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");
    running = false;
}
/********************* BEFORE READ DOUBLE  ****************************/
static void beforeReadDouble(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data) {
    UA_Variant value;
    UA_Variant_setScalar(&value, &dTemp, &UA_TYPES[UA_TYPES_DOUBLE]);
    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "TEMP");
    UA_Server_writeValue(server, currentNodeId, value);
}
static void beforeReadBoolean(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data) {
    //UA_Boolean  bVal = bOverheat ;
    UA_Variant value;
    UA_Variant_setScalar(&value, &bOverheat, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "OVERHEAT");
    UA_Server_writeValue(server, currentNodeId, value);
}
/********************* CALLBACK FUNCTION  ****************************/
static void addCallbackDouble(UA_Server *server) {
    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "TEMP");
    UA_ValueCallback callback ;
    callback.onRead = beforeReadDouble;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void addCallbackBoolean(UA_Server *server) {
    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "OVERHEAT");
    UA_ValueCallback callback ;
    callback.onRead = beforeReadBoolean;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
/****************** READ VALUE FROM UART ********************************/
int readSerial(){
  char buffer[10];
  serialFlush(fd);              //clear Output
  while(serialDataAvail(fd) <= 0){
        // Do nothing if there is no Data available but leave if an error occures
        if(serialDataAvail(fd) == -1) break;
        delay(100);
  }
  int nChar = serialDataAvail(fd);
  for(int i=1; i<=nChar; i++){
    sprintf(buffer,"%s%c",buffer, serialGetchar(fd));
  }
  return atoi(buffer);
}
/*********************  THREADs **************************************/
//>>>>>>>>>>>>>>>> THREAD 1 >>>>>>>>>>>>>>>>>>>>
static void *reNewVariablesThread(void* val) {
    while(running){
	dTemp = readSerial() * 0.1;
	if(dTemp >= 70.0){
		bOverheat = true;
	}else{
		bOverheat = false;
	}
	//printf("%f.1,%i",dTemp,bOverheat);
	sleep(1);
   }
   return NULL;
}
//>>>>>>>>>>>>>>>> THREAD 1 >>>>>>>>>>>>>>>>>>>>
static void *opcServerThread(void* val) {
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    UA_ServerConfig *config = UA_ServerConfig_new_default();
    UA_Server *server = UA_Server_new(config);

    addDouble(server, "TEMP", 0.0);
    addCallbackDouble(server);
    addBoolean(server,"OVERHEAT",false);
    addCallbackBoolean(server);

    UA_Server_run(server, &running);
    UA_Server_delete(server);
    UA_ServerConfig_delete(config);
    return NULL;
}
/****************** main *****************************************/
int main (void) {
    pthread_t thread1, thread2;
    int rc;
    // >>>>>>>>>>>>>>Init serial Connection
    if(wiringPiSetup() == -1){
    	fprintf(stderr, "Unable to start WiringPi: %s\n", strerror (errno));
    return 1;
    }
    fd = serialOpen("/dev/ttyS0",9600);
    if(fd < 0){
    	fprintf(stderr, "Unable to open serial device: %s\n", strerror (errno));
    return 1;
    }
    //>>>>>>>>>>>>>>>>> Thread 1 erzeugen
    rc = pthread_create( &thread1, NULL, &reNewVariablesThread, NULL );
    if( rc != 0 ) {
        printf("Konnte Thread 1 nicht erzeugen\n");
        return EXIT_FAILURE;
    }
    //>>>>>>>>>>>>>>>>> Thread 2 erzeugen
    rc = pthread_create( &thread2, NULL, &opcServerThread, NULL );
    if( rc != 0 ) {
        printf("Konnte Thread 2 nicht erzeugen\n");
        return EXIT_FAILURE;
    }
    // Main-Thread wartet auf beide Threads.
    pthread_join( thread1, NULL );
    pthread_join( thread2, NULL );

    return 0;
}
