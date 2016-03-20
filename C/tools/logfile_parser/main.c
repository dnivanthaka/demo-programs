#include <stdio.h>
#include <getopt.h>

#include "requests.h"

int
main(int argc, char *argv[])
{
    int opt;
    FILE *fp;
    struct client cli;

    if((opt = getopt(argc, argv, "f:")) != -1){
        //printf("%s\n", optarg);
        //printf("%c\n", opt);
        //printf("%d\n", optind);
        fp = fopen(optarg, "r");
    }else{
        fp = NULL;
    }
    parse_log_file(&cli, fp);
    if(fp != NULL)
        fclose(fp);
    
    return 0;
}
