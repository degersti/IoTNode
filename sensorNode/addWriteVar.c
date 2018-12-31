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
/************************ CREATE NEW DOUBLE VARIABLE **********************************/
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
/************************ CREATE NEW BOOLEAN VARIABLE **********************************/
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
/************************ WRITE NWE DOUBLE VALUE **********************************/
void writeDouble(UA_Server *server, char *name, double val) {
    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(1, name);
    // * Write a different integer value 
    UA_Double  myTempVar = val;
    UA_Variant myVar;
    UA_Variant_init(&myVar);
    UA_Variant_setScalar(&myVar, &myTempVar, &UA_TYPES[UA_TYPES_DOUBLE]);
    UA_Server_writeValue(server, myIntegerNodeId, myVar);

    UA_WriteValue wv;
    UA_WriteValue_init(&wv);
    wv.nodeId = myIntegerNodeId;
    wv.attributeId = UA_ATTRIBUTEID_VALUE;
    wv.value.status = UA_STATUSCODE_BADNOTCONNECTED;
    wv.value.hasStatus = true;
    UA_Server_write(server, &wv);

    /* Reset the variable to a good statuscode with a value */
    wv.value.hasStatus = false;
    wv.value.value = myVar;
    wv.value.hasValue = true;
    UA_Server_write(server, &wv);
}
/************************ WRITE NEW BOOLEAN VALUE **********************************/
void writeBoolean(UA_Server *server, char *name, bool val) {
    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(1, name);
    // * Write a different integer value
    UA_Boolean myTempVar = val;
    UA_Variant myVar;
    UA_Variant_init(&myVar);
    UA_Variant_setScalar(&myVar, &myTempVar, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, myIntegerNodeId, myVar);
}
