#include "open62541.h"

UA_Double	dTemp;
UA_Boolean	bOverheat;

void addDouble(UA_Server *server, char *name, double init_val);

void addBoolean(UA_Server *server, char *name, bool bool_val);

void beforeReadDouble(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data);
void beforeReadBoolean(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data);

void addCallbackDouble(UA_Server *server);

void addCallbackBoolean(UA_Server *server);

void writeDouble(UA_Server *server, char *name, double val);

void writeBoolean(UA_Server *server, char *name, bool val);
