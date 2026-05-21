#include "readJSON.h"

void getJsonContent(char *strContent, char * fileAddr){
        FILE *fp;
        int intTemp;
        fp = fopen(fileAddr, "r");
        if(fp == NULL) {
        //printf("COULD NOT OPEN FILE!\n");
        }else
        {
                //printf("INIT JSON SUCCESSFULLY OPENED\n");
                while((intTemp = fgetc(fp))!=EOF)
                {
                sprintf(strContent, "%s%c",strContent ,intTemp);
                }
                fclose(fp);
        }
        sprintf(strContent, "%s%s",strContent ,"\n");
} 

void getValue(char *strContent, char *strValue, char* key){
        int length = strlen(strContent);
        char tempChar;
        char tempWord[100] = "";
        int  flagWord = 0;
        int  flagKey  = 0;
        for(int i = 0; i <= length; i++){
                /* Get the Keys as Words */
                tempChar = strContent[i];
                if(flagWord == 0 && tempChar == '"'){
                        flagWord = 1;
                        sprintf(tempWord,"%s","");
                }
                else if(flagWord == 1 && tempChar == '"'){
                        flagWord = 0;
                        /* Check if Word is desired Key */
                        if ((strcmp(tempWord, key) == 0) && (flagKey == 0)){
                                flagKey = 1;
                                sprintf(tempWord,"%s","");
                        }
                        /* Check if Word is desired Value */
                        else if(flagKey == 1){
                                sprintf(strValue,"%s",tempWord);
                                flagKey = 0;
                        }
                }
                else if(flagWord == 1 && !(tempChar == '"')){
                        sprintf(tempWord,"%s%c", tempWord,tempChar);
                }
        } //endFor
}
