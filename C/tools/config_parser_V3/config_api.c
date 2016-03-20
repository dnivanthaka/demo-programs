#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "config_api.h"

struct config_data * 
parse_config(char *filename)
{
    char line_buff[158];
    FILE *fp;
    int read_count = 0;
    int line_number = 0;
    struct config_data *conf = NULL;
    // This will act as the starting pointer to the config_data struct
    struct config_data *header_conf = NULL;
    //struct config_data_header *conf_head;

    //conf_head = malloc(sizeof(struct config_data_header));
    // make sure we assign this to zero
    //conf_head->current_key_count = 0;

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
                if( get_config_variable(header_conf, key) == NULL ){
                    if(conf == NULL){
                        // This will create the initial node
                        conf = malloc(sizeof(struct config_data));
                        conf->next = NULL;
                        header_conf = conf;
                    }else{
                        struct config_data *tmp; 
                        tmp = malloc(sizeof(struct config_data));

                        while(conf->next != NULL)
                            conf = conf->next;

                        conf->next = tmp;
                        conf = conf->next;
                        conf->next = NULL;
                    }
                    strncpy(conf->key, line_buff, eq_len);
                    conf->key[eq_len] = '\0';
                    strncpy( conf->value, 
                        &line_buff[eq_len + 1], (read_count - eq_len) );
                    conf->value[read_count - eq_len] = '\0';

                    // Inserting the actual line number
                    conf->line_number = line_number;
                    conf->is_changed  = 0;
                    printf("%-10s %-10s %-10d\n", conf->key, conf->value, conf->line_number);
                //conf->current_key_count++;
                }else{
                    fprintf(stderr, "Warning: Duplicate Configuration value, Line Number %d\nLine: %s\n", line_number, line_buff);
                }
            }else{
                fprintf(stderr, "Warning: Too Long Variable/Value, Line Number %d\nLine: %s\n", line_number, line_buff);
            }
        }else{
            fprintf(stderr, "Warning: Bad syntax, Line number %d\nLine: %s\n", line_number, line_buff);
        }
    }

    if(fclose(fp) != 0){
        fprintf(stderr, "Error closing input file.\n");
        //return -1;
        exit(1);
    }

    return header_conf;
}
char * 
get_config_variable(struct config_data *conf_data, char *search_key)
{
    int key_found = 0;
    if(conf_data == NULL)
        return NULL;
    //printf("search key = %s\n", search_key);

    // assuming that the struct pointer is reset
      while(conf_data->next != NULL){
        //printf("search key = %s\n", conf_data->key);
        if( strcmp(conf_data->key, search_key) == 0 ){
            //printf("Found key\n");
            key_found = 1;
            break;
        }
        conf_data = conf_data->next;
      }

    if(key_found == 1){
        return conf_data->value;
    }else{
        return NULL;
    }
}
void 
delete_config_data(struct config_data *conf_data)
{
    struct config_data *tmp;

    if(conf_data == NULL)
        return;

    // Initially this should point to the first node
    tmp = conf_data;
    // Go on freeing memory till we move to the last node
    while(conf_data->next != NULL){
        tmp = conf_data->next;
        free(conf_data);
        conf_data = tmp;
     }
    // Free the memory in the last node too
     if(conf_data != NULL)
        free(conf_data);
}

int 
update_config_variable(struct config_data *conf_data, char *name, char *value)
{

    if(get_config_variable(conf_data, name) == NULL)
        return 0;

    // assuming that the struct pointer is reset
    while(conf_data->next != NULL){
        //printf("search key = %s\n", conf_data->key);
        if( strcmp(conf_data->key, name) == 0 ){
            //printf("Found key\n");
            strcpy( conf_data->value, value );
            conf_data->is_changed = 1;
            break;
        }
        conf_data = conf_data->next;
    }

    return 1;
}

int 
add_config_variable(struct config_data *conf_data, char *name, char *value)
{
    struct config_data *tmp;

    if(get_config_variable(conf_data, name) != NULL)
        return 0;

    tmp = malloc(sizeof(struct config_data));

    while(conf_data->next != NULL)
        conf_data = conf_data->next;

    strcpy(tmp->key, name);
    strcpy(tmp->value, value);
    tmp->line_number = 0;
    tmp->is_changed  = 1;

    conf_data->next = tmp;
    return 1;
}

int 
delete_config_variable(struct config_data *conf_data, char *name)
{
    if(get_config_variable(conf_data, name) == NULL)
        return 0;

    while(conf_data->next != NULL){
        if( strcmp(conf_data->key, name) == 0 ){
            //strcpy( conf_data->key, "\0" );
            memset( conf_data->key, (int)'\0', strlen(conf_data->key) );
            memset( conf_data->value, (int)'\0', strlen(conf_data->value) );
            conf_data->is_changed = 1;
            //strcpy( conf_data->value, "\0" );
            break;
        }
    }

    return 1;
}

int 
write_config(struct config_data *conf_data, char *filename)
{
    int file_exists = 0;
    int ret;
    struct stat buff;
    FILE *fp;
    int line_number = 0;
    char line_buff[158];

    ret = stat(filename, &buff);
    if(ret == 0)
        file_exists = 1;

    if(file_exists == 1){
        fp = fopen(filename, "r+");
    }else{
        fp = fopen(filename, "w+");
    }
    // Resetting file pointer in-case
    fseek(fp, 0, SEEK_SET);

    
    //while(fgets(line_buff, 158,  fp ) != NULL){
       /*
        * TODO Complete this
        */
    //}

    return 0;
}
