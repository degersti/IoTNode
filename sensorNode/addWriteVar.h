#include "open62541.h"

void addDouble(UA_Server *server, char *name, double init_val);

void addBoolean(UA_Server *server, char *name, bool bool_val);

void writeDouble(UA_Server *server, char *name, double val);

void writeBoolean(UA_Server *server, char *name, bool val);
