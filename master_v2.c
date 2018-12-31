#include "readJSON.h"

int main()
{
	//printf("MASTER PROGRAMM HAS STARTED!\n");
	char strContent[1000] = "";
	char strAddress[100]  = "";
	getJsonContent(strContent,"/home/pi/Node/init.json");
	getValue(strContent, strAddress, "Config");
	//printf("RUN CONFIGURATION\n");
	system(strAddress);
}
