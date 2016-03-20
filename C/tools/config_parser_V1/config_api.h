#ifndef __CONFIG_API__
#define __CONFIG_API__
struct config_data {
    /* It is assumed that the config file may 
     * not have more than 100 variables
     */
    char keys[100][80];
    char values[100][80];
    unsigned int current_key_count;
};

struct config_data * parse_config(char *);
char * get_config_variable(struct config_data *, char *);
void delete_config_data(struct config_data *);
#endif //__CONFIG_API__
