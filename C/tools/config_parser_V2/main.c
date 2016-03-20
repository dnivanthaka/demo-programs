#include <stdio.h>
#include <stdlib.h>

#include "config_api.h"

int main(int argc, char *argv[])
{
    char *home_dir; 
    struct config_data *conf_data;
    
    if(argc == 1){
        fprintf(stdout, "Usage: [program] [config file name]\n");
        exit(1);
    }

    home_dir = getenv("HOME");
    if(!home_dir){
        fprintf(stderr, "Error, Environment variable 'HOME' not defined\n");
        exit(1);
    }

    //parse_config((*home_dir)+'/'+argv[1]);
    conf_data = parse_config(argv[1]);
    printf("%s\n", get_config_variable(conf_data, "name2"));
    delete_config_data(conf_data);


    return 0;
}
