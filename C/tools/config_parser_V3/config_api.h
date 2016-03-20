#ifndef __CONFIG_API__
#define __CONFIG_API__
struct config_data_header {
    int current_key_count;
    struct config_data *next;
};
struct config_data {
    char key[80];
    char value[80];
    unsigned int line_number;
    short int is_changed;
    struct config_data *next;
};

struct config_data * parse_config(char *);
char * get_config_variable(struct config_data *, char *);
void delete_config_data(struct config_data *);
int update_config_variable(struct config_data *conf_data, char *name, char *value);
int add_config_variable(struct config_data *conf_data, char *name, char *value);
int delete_config_variable(struct config_data *conf_data, char *name);
int write_config(struct config_data *conf_data, char *filename);
#endif //__CONFIG_API__
