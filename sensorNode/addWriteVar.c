#include "addWriteVar.h"

void addNode(UA_Server *server, UA_VariableAttributes attr,char *name){
    /* Add the variable node to the information model */
    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(1, name);
    UA_QualifiedName myIntegerName = UA_QUALIFIEDNAME(1, name);
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_Server_addVariableNode(server, myIntegerNodeId, parentNodeId,parentReferenceNodeId, myIntegerName,
                                UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), attr, NULL, NULL);
}
/************************ CREATE NEW VARIABLE **********************************/
void addDouble(UA_Server *server, char *name, double init_val) {
    /* Define the attribute of the myInteger variable node */
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    UA_Double myVar = init_val;
    UA_Variant_setScalar(&attr.value, &myVar, &UA_TYPES[UA_TYPES_DOUBLE]);
    attr.description = UA_LOCALIZEDTEXT("en-US",name);
    attr.displayName = UA_LOCALIZEDTEXT("en-US",name);
    attr.dataType = UA_TYPES[UA_TYPES_DOUBLE].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ;
    /* Add node to Server*/
    addNode(server,attr,name);
}
void addBoolean(UA_Server *server, char *name, bool bool_val) {
    /* Define the attribute of the myInteger variable node */
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    UA_Boolean myVar = bool_val;
    UA_Variant_setScalar(&attr.value, &myVar, &UA_TYPES[UA_TYPES_BOOLEAN]);
    attr.description = UA_LOCALIZEDTEXT("en-US",name);
    attr.displayName = UA_LOCALIZEDTEXT("en-US",name);
    attr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ;
    /* Add node to Server*/
    addNode(server,attr,name);
}
/********************* BEFORE READ DOUBLE  ****************************/
void beforeReadDouble(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data) {
    UA_Variant value;
    UA_Variant_setScalar(&value, &dTemp, &UA_TYPES[UA_TYPES_DOUBLE]);
    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "TEMP");
    UA_Server_writeValue(server, currentNodeId, value);
}
void beforeReadBoolean(UA_Server *server,
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
void addCallbackDouble(UA_Server *server) {
    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "TEMP");
    UA_ValueCallback callback ;
    callback.onRead = beforeReadDouble;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
void addCallbackBoolean(UA_Server *server) {
    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "OVERHEAT");
    UA_ValueCallback callback ;
    callback.onRead = beforeReadBoolean;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
/************************ WRITE  VALUE **********************************/
void writeDouble(UA_Server *server, char *name, double val) {
    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(1, name);
    // * Write a different integer value 
    UA_Double  myTempVar = val;
    UA_Variant myVar;
    UA_Variant_init(&myVar);
    UA_Variant_setScalar(&myVar, &myTempVar, &UA_TYPES[UA_TYPES_DOUBLE]);
    UA_Server_writeValue(server, myIntegerNodeId, myVar);
}
void writeBoolean(UA_Server *server, char *name, bool val) {
    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(1, name);
    // * Write a different integer value
    UA_Boolean myTempVar = val;
    UA_Variant myVar;
    UA_Variant_init(&myVar);
    UA_Variant_setScalar(&myVar, &myTempVar, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, myIntegerNodeId, myVar);
}
