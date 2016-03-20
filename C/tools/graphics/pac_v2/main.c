#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <string.h>

#define NUM_BUGS 7 
#define MAX_X    180
#define MAX_Y    60

struct bug {
    int x;
    int y;
};

void print_at(int, int, char *);
void sigalarm_handler();
void sigint_handler();
void init_bugs();
void print_bugs();
void update_bug_loc();
int rand_val(int);
//void draw_level();

struct bug bugs[NUM_BUGS];
void *screen_mem;

int
main(int argc, char *argv[])
{
    srand( (unsigned)time(NULL) );

    signal(SIGALRM, sigalarm_handler);
    signal(SIGINT, sigint_handler);

    struct itimerval delay;

    delay.it_value.tv_sec     = 0;
    delay.it_value.tv_usec    = 100000;
    delay.it_interval.tv_sec  = 0;
    delay.it_interval.tv_usec = 100000;

    // clearing the screen
    printf("\033[2J");
    // placing the cursor at top left
    printf("\033[H");
    printf("\033[?25l");

    //draw_level();

    init_bugs();
    print_bugs();

    setitimer(ITIMER_REAL, &delay, 0);

    while(1){
        //pause();
    }

    return 0;
}

void
print_intro()
{
    printf("\t***********************************");
    printf("\t*                                 *");
    printf("\t*                                 *");
    printf("\t***********************************");
}

void
print_at(int x, int y, char *str)
{
    printf("\033[%d;%dH%s", y, x, str);
    //printf("\033[%d;%dH%s", x, y, str);
    fflush(stdout);
    //printf("\033[%d;%dH%s", x, y, str);
}

void
sigalarm_handler()
{
    //printf("alarm went\n");
    //printf(".");
    // update bug positions
    print_bugs();
    update_bug_loc();
}

void
sigint_handler()
{
    // clearing the screen
    printf("\033[2J");
    // placing the cursor at top left
    printf("\033[H");
    printf("\033[?25h");
    signal(SIGALRM, SIG_DFL);
    signal(SIGINT, SIG_DFL);
    exit(1);
}

int
rand_val(int max)
{
    //srand( (unsigned)time(NULL) );
    return ((1 + rand()) % max);
}

void
init_bugs()
{
    int i;

    for(i=0;i<NUM_BUGS;i++){
        bugs[i].x = rand_val(10);
        bugs[i].y = rand_val(20);
    }
}

void
update_bug_loc()
{
    int i;

    for(i=0;i<NUM_BUGS;i++){
        //if((rand_val(2) - 1) == 0){
        if(rand_val(8) > 1){
            //bugs[i].x += 1;
            bugs[i].x = (bugs[i].x + 1) % MAX_X;
            //bugs[i].y = (bugs[i].y + 1) % MAX_Y;
        }else{
            //bugs[i].y += 1;
            //bugs[i].x = (bugs[i].x + 1) % MAX_X;
            bugs[i].y = (bugs[i].y + 1) % MAX_Y;
        }
    }
}

void
print_bugs()
{
    int i;

    printf("\033[2J");

    //draw_level();

    for(i=0;i<NUM_BUGS;i++){
        //bugs[i].x = rand_val(10);
        //bugs[i].y = rand_val(20);
        //printf("bug%d x = %d\n", (i + 1), bugs[i].x);
        //printf("bug%d y = %d\n", (i + 1), bugs[i].y);
        //printf("\n");
        //printf("");
        //printf("\033[%d;%dH@", bugs[i].x, bugs[i].y);
        //fflush(stdout);
        print_at(bugs[i].x, bugs[i].y, "@");
        //print_at(bugs[i].x, bugs[i].y, "@");
    }

    //update_bug_loc();
}
// FIXME Write a better level drawer than this.
/*
void
draw_level()
{
    FILE *fp;
    char *file = "levels/level1.txt";
    char line_buff[256];
    int line_count = 0;
    int cols, rows, i = 0, j;
    //char *s_mem[41];
    char **s_mem;

    if((fp = fopen(file, "r")) == NULL){
        perror("Opening level file");
    }else{
        while( fgets(line_buff, 256, fp) != NULL ){
            line_buff[ strlen(line_buff) - 1 ] = '\0';
            if(++line_count == 1){
                cols = atoi(strtok(line_buff, " "));
                rows = atoi(strtok(NULL, "\n"));

                //char tmp[cols][rows];
                //s_mem = &tmp[0];
                s_mem = (int **)malloc(cols * sizeof(char *));
                for(k=0;k<cols;k++){
                
                }
            }else{
                for(j=0;j<strlen(line_buff);j++){
                    s_mem[i][j] = line_buff[j];
                }

                i++;
            }
                
            //printf("%s\n", line_buff);
            printf("cols = %d\nrows = %d\n", cols, rows);
        }

        screen_mem = (char *)&s_mem;
    }

    if( feof(fp) )
        fclose(fp);
}
*/
