#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "process.h"

struct m_process *
new_process(char *filename)
{
    FILE *fp;

    fp = fopen(filename, "r");

    if(fp == NULL){
        printf("Error: Cannot read program file %s\n", filename);
        exit(1);
    }

    //while(fgets(buff, 5, fp) != NULL){}

    struct m_process p;
    //p.m_stack = NULL;
    //p.m_data = NULL;
    //p.m_txt = NULL;
    get_file_offsets(fp, &p);
    //printf("m_stack = %s\n", p.m_stack[0]);
    //printf("m_stack = %s\n", p.m_stack[1]);
    //printf("m_stack = %s\n", p.m_stack[2]);
    //printf("m_data = %s\n", p.m_data[0]);
    //printf("m_data = %s\n", p.m_data[1]);
    //printf("m_txt = %s\n", p.m_txt[0]);
    //printf("m_txt = %s\n", p.m_txt[1]);

    return NULL;
}

int
get_file_offsets(FILE *fp, struct m_process *p)
{
    char buff[12];
    int stackCounter = 0, 
        dataCounter  = 0, 
        txtCounter   = 0;
    char *tmp;

    while(fgets(buff, 12, fp) != NULL){
    //printf("Mbuff = %s\n", buff);
    buff[strlen(buff) - 1] = '\0';
    //printf("buff = %s\n", buff);
    //printf("%d\n", strcmp("#startSS", buff));
         // reading the stack segment
         if(strcmp("#startSS", buff) == 0){
             //while( strcmp( "#endSS", fgets(buff, 12, fp) ) != 0 ){
             while( fgets(buff, 12, fp)  != NULL ){
                 //tmp = malloc((sizeof(char) * strlen(buff)) + 1);
                 // removing newline char
                 buff[strlen(buff) - 1] = '\0';
                 if(strcmp("#endSS", buff) == 0)
                    break;
                 //printf("stbuff = %s\n", buff);
                 //p->m_stack = NULL;
                 //p->m_stack = realloc(p->m_stack, sizeof(char) * (strlen(buff) + 1));
                 //strncpy(&p->m_stack[stackCounter], buff, strlen(buff));
                 //stackCounter += strlen(buff) + 1;
                 //strcpy(p->m_stack[stackCounter], buff);
                 strcpy(p->m_stack[stackCounter], buff);
                 //printf("m_stack = %s\n", p->m_stack[stackCounter]);
                 stackCounter++;
                 //stackCounter += strlen(buff) + 1;
                 //strcpy(tmp, buff);
                 //strcpy(&p->m_stack[stackCounter], tmp);
                 if(stackCounter == 10)
                    break;
             }
         }
         // reading the data segment
         if(strcmp("#startData", buff) == 0){
             //while( strcmp( "#endData", fgets(buff, 12, fp) ) != 0 ){
             while( fgets(buff, 12, fp)  != NULL ){
                 buff[strlen(buff) - 1] = '\0';
                 //printf("data buff = %s\n", buff);
                 if(strcmp("#endData", buff) == 0)
                    break;
                 //p->m_data = realloc(p->m_data, strlen(buff) + 1);
                 //printf("data buff = %s\n", buff);
                 //strncpy(&p->m_data[dataCounter], buff, strlen(buff) + 1);
                 //dataCounter += strlen(buff) + 1;
                 strcpy(p->m_data[dataCounter], buff);
                 dataCounter++;

                 if(dataCounter == 10)
                    break;
             }
         }
         // reading the Text segment
         if(strcmp("#startTxt", buff) == 0){
             //while( strcmp( "#endTxt", fgets(buff, 12, fp) ) != 0 ){
             while( fgets(buff, 12, fp)  != NULL ){
                 buff[strlen(buff) - 1] = '\0';
                 if(strcmp("#endText", buff) == 0)
                    break;
                 //p->m_txt = realloc(p->m_txt, strlen(buff) + 1);
                 //strncpy(&p->m_txt[txtCounter], buff, strlen(buff) + 1);
                 //txtCounter += strlen(buff) + 1;
                 strcpy(p->m_txt[txtCounter], buff);
                 txtCounter++;

                 if(txtCounter == 10)
                    break;
             }
         }
    }

    return 0;
}
