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
#include <math.h>

struct measurement {
   int num_samples;
   float average_value;
   unsigned int max_value;
   unsigned int min_value;
   float std_deviation;
   unsigned int *result_values;
} measurement;

int num_samples = 0, 
    average     = 0, 
    max         = 0, 
    min         = 0, 
    std_div     = 0;

void run_getsid(struct measurement *);
void run_getpid(struct measurement *);
void run_gettimeofday(struct measurement *);
void run_read(int, struct measurement *);
void print_help();
float get_elapsed_time();
void calculate_std_dev(struct measurement *);

//extern int getsid();
//extern int getpid();

// Report the number of samples collected, average value, maximum value, minimum value and standard deviation (jitter)


int
main(int argc, char *argv[])
{
    
    int opt, fd;
    int cflag = 0;
    //char sys_call[10];
    char *sys_call;
    int sflag = 0;
    int s_time = 0;

    struct measurement *mt;
    int *m_values;

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

    mt                = malloc(sizeof(struct measurement));
    mt->num_samples   = s_time;
    mt->result_values = (int *)malloc(sizeof(int) * s_time);
    //m_values = malloc(sizeof(int) * s_time);

    if(strcmp(sys_call, "getsid") == 0){
        //stt_time = get_elapsed_time();
        //run_getsid(s_time);
        run_getsid(mt);
        //end_time = get_elapsed_time();
    }else if(strcmp(sys_call, "getpid") == 0){
        //stt_time = get_elapsed_time();
        //run_getpid(s_time);
        run_getpid(mt);
        //end_time = get_elapsed_time();
    }else if(strcmp(sys_call, "gettimeofday") == 0){
        //stt_time = get_elapsed_time();
        //run_gettimeofday(s_time);
        run_gettimeofday(mt);
        //end_time = get_elapsed_time();
    }else if(strcmp(sys_call, "read") == 0){

        fd = open(input, O_RDONLY);

        if(fd == -1){
            perror("open");
            return 1;
        }

        //stt_time = get_elapsed_time();
        //run_read(fd, s_time);
        run_read(fd, mt);
        //end_time = get_elapsed_time();

        close(fd);
    }else{
        printf("Invalid argument %s\n", sys_call);
        return 1;
    }

    calculate_std_dev(mt);

    printf("================= Results =================\n");
    printf("Number of Samples = %-8d \n", mt->num_samples);
    printf("Average           = %-8f microseconds\n", mt->average_value);
    printf("Max Value         = %-8d microseconds\n", mt->max_value);
    printf("Min Value         = %-8d microseconds\n", mt->min_value);
    printf("Std. Deviation    = %-8f microseconds\n", mt->std_deviation);
    printf("===========================================\n");
    return 0;
}

void
calculate_std_dev(struct measurement *mt)
{
    int i;
    float result = 0;

    for(i=0;i<mt->num_samples;i++){
        result += powf(mt->result_values[i] - mt->average_value, 2);
        /*
        result += ((mt->result_values[i] - mt->average_value) * 
        (mt->result_values[i] - mt->average_value));
        */
    }

    result = result / mt->num_samples;
    //result = sqrtf(result);
    result = sqrt((double)result);

    mt->std_deviation = result;
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
run_getsid(struct measurement *mt)
{
    int i;
    float stt_time = 0, end_time = 0, total = 0;

    //int (*fp)();

    //fp = &getsid;

    for(i = 0; i< mt->num_samples; i++){
        stt_time = get_elapsed_time();
        getsid();
        //(*fp)();
        //sleep(1);
        end_time = get_elapsed_time();

        if(i == 0){
            mt->average_value = end_time - stt_time;
            mt->min_value     = end_time - stt_time;
            mt->max_value     = end_time - stt_time;
            mt->std_deviation = 0;
            mt->result_values[i] = (unsigned int)(end_time - stt_time);

            continue;
        }

        if(end_time - stt_time < mt->min_value){
            mt->min_value = end_time - stt_time;
            #ifdef DEBUG
            printf("at min_val: end_time = %d\n", (unsigned int)end_time);
            printf("at min_val: stt_time = %d\n", (unsigned int)stt_time);
            #endif
        }
        if(end_time - stt_time > mt->max_value){
            mt->max_value = end_time - stt_time;
            #ifdef DEBUG
            printf("at max_val: end_time = %d\n", (unsigned int)end_time);
            printf("at max_val: stt_time = %d\n", (unsigned int)stt_time);
            #endif
        }

        total += (end_time - stt_time);

        mt->result_values[i] = (unsigned int)(end_time - stt_time);
    }

    //mt->average_value = (unsigned int)(total / mt->num_samples);
    mt->average_value = (total / mt->num_samples);

    #ifdef DEBUG
        int d;

        printf("num_samples   = %d\n", mt->num_samples);
        printf("total         = %f microseconds\n", total);
        printf("min_value     = %d microseconds\n", mt->min_value);
        printf("max_value     = %d microseconds\n", mt->max_value);
        printf("average_value = %f microseconds\n", mt->average_value);
        printf("std_deviation = %f microseconds\n", mt->std_deviation);

        for(d=0;d<mt->num_samples;d++){
            printf("value %d = %d\n", (d + 1), mt->result_values[d]);
        }
    #endif
}

void
run_getpid(struct measurement *mt)
{
    int i;
    float stt_time = 0, end_time = 0, total = 0;

    //int (*fp)();

    //fp = &getsid;

    for(i = 0; i< mt->num_samples; i++){
        stt_time = get_elapsed_time();
        getpid();
        //(*fp)();
        //sleep(1);
        end_time = get_elapsed_time();

        if(i == 0){
            mt->average_value = end_time - stt_time;
            mt->min_value     = end_time - stt_time;
            mt->max_value     = end_time - stt_time;
            mt->std_deviation = 0;
            mt->result_values[i] = (unsigned int)(end_time - stt_time);

            continue;
        }

        if(end_time - stt_time < mt->min_value){
            mt->min_value = end_time - stt_time;
            #ifdef DEBUG
            printf("at min_val: end_time = %d\n", (unsigned int)end_time);
            printf("at min_val: stt_time = %d\n", (unsigned int)stt_time);
            #endif
        }
        if(end_time - stt_time > mt->max_value){
            mt->max_value = end_time - stt_time;
            #ifdef DEBUG
            printf("at max_val: end_time = %d\n", (unsigned int)end_time);
            printf("at max_val: stt_time = %d\n", (unsigned int)stt_time);
            #endif
        }

        total += (end_time - stt_time);

        mt->result_values[i] = (unsigned int)(end_time - stt_time);
    }

    //mt->average_value = (unsigned int)(total / mt->num_samples);
    mt->average_value = (total / mt->num_samples);

}

void
run_gettimeofday(struct measurement *mt)
{
    int i;
    struct timeval tv;
    float stt_time = 0, end_time = 0, total = 0;

    //int (*fp)();

    //fp = &getsid;

    for(i = 0; i< mt->num_samples; i++){
        stt_time = get_elapsed_time();
        gettimeofday(&tv, NULL);
        //(*fp)();
        //sleep(1);
        end_time = get_elapsed_time();

        if(i == 0){
            mt->average_value = end_time - stt_time;
            mt->min_value     = end_time - stt_time;
            mt->max_value     = end_time - stt_time;
            mt->std_deviation = 0;
            mt->result_values[i] = (unsigned int)(end_time - stt_time);

            continue;
        }

        if(end_time - stt_time < mt->min_value){
            mt->min_value = end_time - stt_time;
            #ifdef DEBUG
            printf("at min_val: end_time = %d\n", (unsigned int)end_time);
            printf("at min_val: stt_time = %d\n", (unsigned int)stt_time);
            #endif
        }
        if(end_time - stt_time > mt->max_value){
            mt->max_value = end_time - stt_time;
            #ifdef DEBUG
            printf("at max_val: end_time = %d\n", (unsigned int)end_time);
            printf("at max_val: stt_time = %d\n", (unsigned int)stt_time);
            #endif
        }

        total += (end_time - stt_time);

        mt->result_values[i] = (unsigned int)(end_time - stt_time);
    }

    //mt->average_value = (unsigned int)(total / mt->num_samples);
    mt->average_value = (total / mt->num_samples);
}

void
run_read(int fd, struct measurement *mt)
{
    int i;
    char b;
    float stt_time = 0, end_time = 0, total = 0;

    //int (*fp)();

    //fp = &getsid;

    for(i = 0; i< mt->num_samples; i++){
        stt_time = get_elapsed_time();
        read(fd, &b, 1);
        //(*fp)();
        //sleep(1);
        end_time = get_elapsed_time();

        if(i == 0){
            mt->average_value = end_time - stt_time;
            mt->min_value     = end_time - stt_time;
            mt->max_value     = end_time - stt_time;
            mt->std_deviation = 0;
            mt->result_values[i] = (unsigned int)(end_time - stt_time);

            continue;
        }

        if(end_time - stt_time < mt->min_value){
            mt->min_value = end_time - stt_time;
            #ifdef DEBUG
            printf("at min_val: end_time = %d\n", (unsigned int)end_time);
            printf("at min_val: stt_time = %d\n", (unsigned int)stt_time);
            #endif
        }
        if(end_time - stt_time > mt->max_value){
            mt->max_value = end_time - stt_time;
            #ifdef DEBUG
            printf("at max_val: end_time = %d\n", (unsigned int)end_time);
            printf("at max_val: stt_time = %d\n", (unsigned int)stt_time);
            #endif
        }

        total += (end_time - stt_time);

        mt->result_values[i] = (unsigned int)(end_time - stt_time);
    }

    //mt->average_value = (unsigned int)(total / mt->num_samples);
    mt->average_value = (total / mt->num_samples);
}
