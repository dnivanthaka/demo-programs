/*
 *
 *
 * Note the function LoopPerMsec is renamed into loop_per_msec
 */
#include <sys/time.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

// This is the max times each loop should run
#define MAX_LOOP 298880

float get_elapsed_time();
void loop_per_msec(unsigned int);
void calculate_duration(int);
int LoopPerMsec;
void child_calculation();

int 
main(int argc, char *argv[])
{
    int num_loops;
    pid_t pid;

    setbuf(stdout, NULL); /* Disable buffering of stdout */

    if( argc == 3 ){
        if(strcmp(argv[1], "-a") == 0){
            num_loops = atoi(argv[2]);
        }else{
            num_loops = 1;
        }
    }else{
        num_loops = 1;
    }

    printf("Parent process id is %d\n", (int)getpid());

    //pid = fork();
    //printf("Time 1 = %d\n", get_elapsed_time());
    //run_loop(MAX_LOOP);
    //printf("Time 2 = %d\n", get_elapsed_time());
    calculate_duration(num_loops);

    pid = fork();

    switch(pid){
        case -1:
            printf("Error occured on fork!!!\n");
            exit(1);
            break;
        case 0:
            // This is the child
            printf("Child process id is %ld\n", (long int)getpid());
            // do work
            child_calculation();
            exit(0);
            //break;
        default:
            //sleep(3);
            // Reusing pid variable to read output sent from wait()
            pid = wait(NULL);
            if(pid == -1){
                if(errno != ECHILD){
                    printf("Error occured when waiting on child\n");
                }

            }
                printf("Child (process id = %ld) exited with status equal to %d\n", (long int)pid,errno);
            break;
    }

    return 0;
}

/*
 * Executes a loop on specified loop count, assumes this program is executed on a 32bit or a higher machine since im measuring it using large values.
 * Params: number of times the loop should run
 */
void
loop_per_msec(unsigned int times)
{
    unsigned int i;
    unsigned int j = 0;

    for(i = 0; i < times;i++)
        j++;
}

void
calculate_duration(int times)
{
    float stt_time = 0, // Start time in microseconds 
          end_time = 0, // End time in microseconds
          min_time = 0, // Min-Time (microseconds) spent on looping MAX_LOOP
          max_time = 0, // Max-Time (microseconds) spent on looping MAX_LOOP
          total_count = 0, // Total time spent in microseconds
          average = 0; // Average time in microseconds
    
    int i;
    
    printf("Determining LoopPerMsec...\n");

    for(i=0;i<times;i++){
        stt_time = get_elapsed_time();
        loop_per_msec(MAX_LOOP);
        end_time = get_elapsed_time();
            //min_time = MAX_LOOP / (end_time - stt_time);
            //max_time = MAX_LOOP / (end_time - stt_time);
        if(i == 0){
            max_time = min_time = end_time - stt_time;
            //max_time = min_time;
            //total_count = end_time - stt_time;
        }

        //printf("\tdiff = %f\n", end_time - stt_time);
        if( (end_time - stt_time) < min_time )
            min_time = (end_time - stt_time);
        if( (end_time - stt_time) > max_time )
            max_time = (end_time - stt_time);

        //total_count += MAX_LOOP / (end_time - stt_time);
        total_count += (end_time - stt_time);
    }

    average = (total_count / times);

    //printf("\tstt value %f\n", stt_time);
    //printf("\tend value %f\n", end_time);
    LoopPerMsec = (unsigned int)(MAX_LOOP / average) * 1000;

    if(times > 1){
        printf("\tAverage value %d\n", (unsigned int)(MAX_LOOP / average) * 1000);
        // Max time turns into Min time when calculating for one microsecond
        // Min time turns into Max time when calculating for one microsecond
        printf("\tMaximum value %d\n", (unsigned int)(MAX_LOOP / min_time) * 1000);
        printf("\tMinimum value %d\n", (unsigned int)(MAX_LOOP / max_time) * 1000);
    }else{
        printf("\tLoopPerMsec = %d\n", (unsigned int)(MAX_LOOP / average) * 1000);
    }

}

/*
 * Returns the number of milliseconds elapsed since 1st Jan 1970 (Epoch)
 */
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
child_calculation()
{
    float stt_time = 0, end_time = 0, num_iterations = MAX_LOOP;

    stt_time = get_elapsed_time();
    loop_per_msec(MAX_LOOP);
    end_time = get_elapsed_time();

    printf("\tIt took %d usec to execute %d iterations of the test loop\n", 
    (unsigned int)(end_time - stt_time), 
    (unsigned int)num_iterations);
}

