#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "requests.h"

#define BUFFER_SIZE 255

int num_clients;
struct client clients[MAX_CONCURRENT_CLIENTS];

/**
 * parses the given log file and fills out the data structure
 *
 */
int
parse_log_file(struct client *info, FILE *fp)
{
    char buffer[BUFFER_SIZE];
    char ip[16];
    int i;
    char *f_ptr;
    char time[26];
    char file[255];

    num_clients = 0;

    for(i=0;i<MAX_CONCURRENT_CLIENTS;i++){
        clients[i].address[0] = '\0';
        clients[i].requests = NULL;
    }

    while( fgets(buffer, BUFFER_SIZE, fp) != NULL ){
        struct request *req, *tmp;
        int index, count = 0;
        // Stripping out the newline char
        buffer[BUFFER_SIZE - 1] = '\0';
        //printf("%s\n", buffer);
        //printf("%s\n", get_client_address(buffer, &ip));
        get_client_address(&buffer[0], &ip[0]);
        get_request_time(&buffer[0], &time[0]);
        get_requested_file(&buffer[0], &file[0]);

        tmp = malloc(sizeof(struct request));
        //tmp->file = file;
        //printf("file len = %d\n", (int)strlen(file));
        f_ptr = malloc( (sizeof(char) * (int)strlen(file)) + 1 );
        strcpy(f_ptr, file);
        tmp->file = f_ptr;
        //tmp->file = malloc(sizeof(char) * strlen(file));
        //strcpy(tmp->file, file);
        strcpy(tmp->time, time);
        tmp->next = NULL;

        if( (index = check_client_exists(&ip[0])) != -1){
            // we caught a persistant client


            //printf("file = %s\n", &file[0]);

            req = clients[index].requests;
            //printf("index = %d\n", index);
            //printf("req = %p\n", req);
            //printf("address = %s\n", clients[index].address);
            
            if(req != NULL){
                while(req->next != NULL)
                    req = req->next;
                //req = req->next;
                //printf("kkkkkkkkk\n");
                //printf("new req = %p\n", req);

                req->next = tmp;
            }else{
                req = tmp;
            }

            //printf("new req1 = %p\n", req);
            //printf("new requests = %p\n", clients[index].requests);

            /*
            count = 0;
            req = clients[index].requests;
            printf("new requestsxx = %p\n", clients[index].requests);
            while(req != NULL){
                 printf("=====================\n");
                 printf("new req3 = %p\n", req);
                 printf("file = %s\n", req->file);
                 printf("count = %d\n", ++count);
                 printf("=====================\n");
                 req = req->next;
            }
            */
        }else{
            strcpy(clients[num_clients].address, ip);
            //clients[num_clients].requests = NULL;
            clients[num_clients].requests = tmp;
            //printf("tmp = %p\n", tmp);
            num_clients++;
        }
        //printf("%s\n", ip);
    }

    print_clients();

    return 0;
}

void
print_clients()
{
    int i;
    char addr[MAX_ADDR_LEN];
    struct request *req;

    for(i=0;i<num_clients;i++){
        strcpy(addr, clients[i].address);
        printf("addr = %s\n", addr);
        //printf("%p\n", clients[i].requests);
        if(clients[i].requests != NULL){
            req = clients[i].requests;
            printf("==== Client requests ====\n");
            while(req != NULL){
                printf("file = %s\n", req->file);
                printf("time = %s\n", req->time);
                req = req->next;
            }
        }else{
            printf("No requests\n");
        }
    }
}

/*
 * Returns the the index of the clients array, if a matching entry is found.
 *
 */
int
check_client_exists(char *ip)
{
    int i;
    int ret = -1;

    for(i=0;i<num_clients;i++){
        if(strcmp(clients[i].address, ip) == 0){
            ret = i;
            break;
        }
    }

    return ret;
}

void
get_client_address(char *str, char *ip)
{
    char *q1, *q2, *q3, *q4;

    if(strlen(str) > 0){
        //strncpy(ip, str, 15);
        q1 = strtok(str, ".");
        q2 = strtok(NULL, ".");
        q3 = strtok(NULL, ".");
        q4 = strtok(NULL, " ");

        //printf("%s.%s.%s.%s\n",q1, q2, q3, q4);
        snprintf(ip, 16, "%s.%s.%s.%s", q1, q2, q3, q4);
        //ip[15] = '\0';
    }
}

void
get_request_time(char *str, char *time)
{
    int br_pos_st = 0, br_pos_end = 0;

    if(strlen(str) > 0){
        //br_pos_st = strcspn(str, "200");
        br_pos_st  = chpos(str, "[");
        br_pos_end = chpos(str, "]");
        strncpy(time, &str[br_pos_st + 1], (br_pos_end - br_pos_st));
        // Remove the trailing ] and insert terminate char
        time[(br_pos_end - br_pos_st) - 1] = '\0';
        //br_pos_st = chpos(str, "200");
        //br_pos_end = strcspn(&str[br_pos_st + 1], "]");
        //printf("st = %d, end = %d\n", br_pos_st, br_pos_end);
        //printf("str = %s\n", time);
    }
}

/*
 * Returns the the absolute path of the requested file.
 *
 */
void
get_requested_file(char *str, char *file)
{
    int qt_st = 0, 
    qt_len = 0,
    sp_len = 0,
    sla_len = 0;

    if(strlen(str) > 0){
        qt_st   = chpos(str, "\"");
        sla_len = chpos(&str[qt_st], "/");
        sp_len  = chpos(&str[qt_st+sla_len], " ");
        qt_len  = chpos(&str[qt_st+1], "\"");

        strncpy(file, &str[qt_st + sla_len], sp_len);
        file[sp_len] = '\0';
        //printf("file = %s\n", file);
        //printf("st = %d, end = %d\n", qt_st, qt_end);
        //printf("sp_len = %d\n", sp_len);
    }
}

/*
 * Returns the index of the specified char, -1 if not found.
 *
 */
int
chpos(char *haystack, char *needle)
{
    char *tmp;
    tmp = haystack;
    int pos = -1;

    while((int)*(&tmp[++pos]) != (int)*needle);

    return pos;
}
