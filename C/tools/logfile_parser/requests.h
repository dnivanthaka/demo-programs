#ifndef __REQUESTS__
#define __REQUESTS__

#define MAX_TIME_LEN            26
#define MAX_ADDR_LEN            50
#define MAX_CONCURRENT_CLIENTS 200

struct request {
    char *file;
    char time[MAX_TIME_LEN];
    struct request *next;
};

struct client {
    char address[MAX_ADDR_LEN];
    struct request *requests;
};

int parse_log_file(struct client *, FILE *);
void get_client_address(char *, char *);
void get_request_time(char *, char *);
void get_requested_file(char *, char *);
int chpos(char *haystack, char *needle);
int check_client_exists(char *ip);
void print_clients();
#endif //__REQUESTS__
