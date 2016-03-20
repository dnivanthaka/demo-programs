#include <stdio.h>
#include <string.h>

#include "level.c"

void
read_layout(struct layout *l, int level, unsigned char **buffer)
{
    FILE *fp;
    char level_file[65];
    char buff[256];
    char *tmp;
    int c, i;

    sprintf(level_file, "levels/level%d.txt", level);
    fp = fread(level_file, "r");
    if(fp != NULL){
        read_meta(l, fp);
        char data[l->height][l->width];
        while(fgets(buff, 255, fp)){
        //while(c = (fread(buff, sizeof(char), 255, fp)) > 0){
            buff[strlen(buff) - 1] = '\0';
            tmp = malloc(sizeof(char) * (int)strlen(buff));
            strcpy(tmp, buff);
            strcpy(data[i++], tmp);
       } 

       buffer = &data[0];
    }
}

void
read_meta(struct layout *l, FILE *fp){
    char buff[50];

    fgets(buff, sizeof(char), 50, fp);
    //buff[c] = '\0';
    l->width  = atoi(strtok(buff, "\t"));
    l->height = atoi(strtok(NULL, "\n"));
}
