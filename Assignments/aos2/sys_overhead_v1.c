/*
 * sys_overhead - Measures the overhead of calling sys calls.
 * Author: D.N. Amerasinghe
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

int num_samples = 0, 
    average     = 0, 
    max         = 0, 
    min         = 0, 
    std_div     = 0;

void run_getsid(int);
void run_getpid(int);
void run_gettimeofday(int);
void run_read(int ,int);
void print_help();
float get_elapsed_time();

// Report the number of samples collected, average value, maximum value, minimum value and standard deviation (jitter)

struct measurement {
   int num_samples;
   unsigned int average_value;
   unsigned int max_value;
   unsigned int min_value;
   unsigned int std_deviation;
   unsigned int result_values;
} measurement;

int
main(int argc, char *argv[])
{
    
    int opt, fd;
    int cflag = 0;
    //char sys_call[10];
    char *sys_call;
    int sflag = 0;
    int s_time = 0;

    float stt_time = 0,
          end_time = 0;

    char *input = "/dev/null";

    if(argc < 5){
        print_help();
        return 1;
    }

    while( (opt = getopt(argc, argv, ":c:s:")) != -1 ){
    
        switch(opt)
        {
            case 'c':
                //strncpy( sys_call, argv[optind], strlen(argv[optind]) );
                sys_call = argv[optind - 1];
                break;
            case 's':
                s_time = atoi(argv[optind - 1]);
                break;
            case ':':
                printf("Missing argument for -%c\n", optopt);
                break;
            case '?':
                printf("Unknown option character -%c\n", optopt);
                break;
            default:
                break;
        }
    }
/*
    if(strlen(sys_call) == 0 || s_time == 0)
        return 1;
*/

#ifdef DEBUG
    printf("sys call - %s\n", sys_call);
    printf("samples  - %d\n", s_time);
#endif


    if(strcmp(sys_call, "getsid") == 0){
        stt_time = get_elapsed_time();
        run_getsid(s_time);
        end_time = get_elapsed_time();
    }else if(strcmp(sys_call, "getpid") == 0){
        stt_time = get_elapsed_time();
        run_getpid(s_time);
        end_time = get_elapsed_time();
    }else if(strcmp(sys_call, "gettimeofday") == 0){
        stt_time = get_elapsed_time();
        run_gettimeofday(s_time);
        end_time = get_elapsed_time();
    }else if(strcmp(sys_call, "read") == 0){

        fd = open(input, O_RDONLY);

        if(fd == -1){
            perror("open");
            return 1;
        }

        stt_time = get_elapsed_time();
        run_read(fd, s_time);
        end_time = get_elapsed_time();

        close(fd);
    }else{
        printf("Invalid argument %s\n", sys_call);
        return 1;
    }

#ifdef DEBUG
    printf("stt_time = %f\n", stt_time);
    printf("end_time = %f\n", end_time);
#endif

    printf("Elapsed time = %d\n", (unsigned int)(end_time - stt_time));

    return 0;
}

float
get_elapsed_time()
{
    struct timeval tv;
    int ret;

    ret = gettimeofday(&tv, NULL);

    if(ret == -1){
        printf("Error occured on getting time\n");
        exit(1);    
    }
    //printf("usec = %d\n", (unsigned int)tv.tv_usec);
    // Converting microseconds to milliseconds
    //return (tv.tv_usec / (suseconds_t)1000);
    return tv.tv_usec;
}

void 
print_help()
{

     //printf("Usage: [program] [sys call] [sampling times]\n");
     printf("====================================================\n");
     printf("Usage: [program] -c [sys call] -s [sampling times]\n");
     printf("------------------ SYS CALLS LIST ------------------\n");
     printf("(1) getsid\n");
     printf("(2) getpid\n");
     printf("(3) gettimeofday\n");
     printf("(4) read\n");
     printf("====================================================\n");
}

void
run_getsid(int samples)
{
    int i;


    for(i = 0; i< samples; i++){
        getsid();
    }
}

void
run_getpid(int samples)
{
    int i;

    for(i = 0; i< samples; i++){
        getpid();
    }
}

void
run_gettimeofday(int samples)
{
    int i;
    struct timeval tv;

    for(i = 0; i< samples; i++){
        gettimeofday(&tv, NULL);
    }
}

void
run_read(int fd, int samples)
{
    int i;
    char b;

    for(i = 0; i< samples; i++){
        read(fd, &b, 1);
    }
}
