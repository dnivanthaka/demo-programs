#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config_api.h"

struct config_data * 
parse_config(char *filename)
{
    char line_buff[158];
    FILE *fp;
    int read_count = 0;
    int line_number = 0;
    struct config_data *conf;

    conf = malloc(sizeof(struct config_data));
    // make sure we assign this to zero
    conf->current_key_count = 0;

    fp = fopen(filename, "r");
    if(fp == NULL){
        perror("fopen");
        fprintf(stderr, "%s\n", filename);
        //return -1;
        exit(1);

    }
         printf("key                  value\n");
         printf("==========================\n");

    //printf("%d\n", (int)fread(line_buff, sizeof(char), 158, fp ));
    while(fgets(line_buff, 158,  fp ) != NULL){
    //while((read_count = fread(line_buff, sizeof(char), 158, fp )) == 158){
        //we dont need the "\n" character
        read_count = strlen(line_buff) - 1;
        int eq_len = 0;
        char key[80];
        //char value[80];

        line_buff[read_count] = '\0';
        line_number++;

        if(line_buff[0] == '#')
            continue;

        if((eq_len = strcspn(line_buff, "=")) != read_count){
            if(eq_len < 80){
                //conf->current_key_count++;
                strncpy(key, line_buff, eq_len);
                key[eq_len] = '\0';
                if( get_config_variable(conf, key) == NULL ){
                    strncpy(conf->keys[conf->current_key_count], line_buff, eq_len);
                    conf->keys[conf->current_key_count][eq_len] = '\0';
                    //key[eq_len] = '\0';
                    //deduct 1 from eq_len to strip out '='
                    //strncpy(value, &line_buff[eq_len + 1], (read_count - eq_len));
                    strncpy( conf->values[conf->current_key_count], 
                        &line_buff[eq_len + 1], (read_count - eq_len) );
                    conf->values[conf->current_key_count][read_count - eq_len] = '\0';
                    //value[read_count - eq_len] = '\0';
                    //conf->keys[conf->current_key_count]
                    //printf("%-10s %-10s\n", key, value);
                    printf("%-10s %-10s\n", conf->keys[conf->current_key_count], conf->values[conf->current_key_count]);
                conf->current_key_count++;
                }else{
                    fprintf(stderr, "Warning: Duplicate Configuration value, Line Number %d\nLine: %s\n", line_number, line_buff);
                }
            }else{
                fprintf(stderr, "Warning: Too Long Variable/Value, Line Number %d\nLine: %s\n", line_number, line_buff);
            }
        }else{
            fprintf(stderr, "Warning: bad syntax, Line number %d\nLine: %s\n", line_number, line_buff);
        }
    }

    if(fclose(fp) != 0){
        fprintf(stderr, "Error closing input file.\n");
        //return -1;
        exit(1);
    }

    return conf;
}
char * 
get_config_variable(struct config_data *conf_data, char *search_key)
{
    int i;
    int key_count = conf_data->current_key_count;
    int key_found = 0;
    //printf("search key = %s\n", search_key);

    for(i=0;i<key_count;i++){
        if( strcmp(conf_data->keys[i], search_key) == 0 ){
            //printf("Found key\n");
            key_found = 1;
            break;
        }
    }

    if(key_found == 1){
        return conf_data->values[i];
    }else{
        return NULL;
    }
}
void 
delete_config_data(struct config_data *conf_data)
{
    if(conf_data)
        free(conf_data);
}
