#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <linux/input.h>

#include "keyb_utils.h"
#include "screen_utils.h"


short alarm_fired = 0;
short power_mode  = 0;
const short num_ghosts = 4;

short pac_mv_lft = 0;
short pac_mv_rht = 0;
short pac_mv_up = 0;
short pac_mv_dwn = 0;

int screen_width, screen_height;
char *screen_buffer;
int score = 0;
int score_panel_height = 3;
int pwr_pt_ticks = 8;

// _dir could be 0 = right, 1 = left, 2 = up, 3 = down

struct pac {
    short _x;
    short _y;
    short _dir;
};

struct ghost {
    short _x;
    short _y;
    short _dir;
};

void put_ghosts( struct ghost * );
void sigint_handler( int );
void sig_init();
void reset_res();
void timer_init();
void load_level();
void show_score_panel();
void move_ghosts(struct ghost *g, struct pac *p);
void move_ghosts_i(struct ghost *g, struct pac *p);
int game_over_check(struct ghost *g, struct pac *p);

int
main( int argc, char *argv[] )
{
    struct pac p;
    struct ghost g[num_ghosts];
    //struct input_event ev[64];
    int pwr_tick = 0;
    //int kyb_val = 0;
    char kyb;
    
    p._x = 1;
    p._y = 1;
    p._dir = 0;

    //screen_width  = 80;
    screen_width  = 80;
    //screen_height = 24;
    // Without the score panel
    screen_height = 21;

    screen_buffer = malloc( screen_width * screen_height );
    memset( screen_buffer, 0, screen_width * screen_height );

    srand( (unsigned)time(NULL) );

    //tty_raw();    
    screen_clear();
    screen_cur_reset();
    screen_disable_echo();
    tty_raw();
    sig_init();
    timer_init();
    load_level();
    show_score_panel();
    put_ghosts( g );

    int i = 7; // start offset
    
    
    for(;;){
        show_score_panel();
        // keyboard reading
        //if ((read (fileno(stdin), ev, sizeof (struct input_event) * 64)) < sizeof (struct input_event))
        if ( read (fileno(stdin), &kyb, 1) > 0 ){
            //perror("read()"); 
            
                //int value = ev[0].value;
            //printf( "%dyy\n", kyb );
            //sprintf(kyb_val, "%d", kyb);
            if( kyb == 65 ){
                // up
                pac_mv_up = 1;
                //printf("xxxx");
            }else if( kyb == 66 ){
                // down
                pac_mv_dwn = 1;
            }else if( kyb == 68 ){
                // left
                pac_mv_lft = 1;
            }else if( kyb == 67 ){
               // right
                pac_mv_rht = 1;
            }
        }else{
            //pac_mv_lft = 0;
            //pac_mv_rht = 0;
            //pac_mv_up = 0;
            //pac_mv_dwn = 0;
        }
        //
        //screen_print( 0, 0, "" );
        if(alarm_fired == 1){
            move_ghosts_i( g, &p );
            //screen_print( 0, 0, &screen_buffer[ i ] );
            //printf("%c ", screen_buffer[ i ] );
            //screen_print( 0, 0, "Y" );
            //screen_print_char( p._x + 1, p._y, screen_buffer[ i ] );
            //show_score_panel();
            //read( fileno(stdin), &kyb, 1 );
            //printf( "%d\n", atoi(kyb));
            if( 
                (pac_mv_rht == 1 && screen_buffer[ (screen_width * (p._y)) + (p._x + 1) ] != 'W') || 
                (pac_mv_lft == 1 && screen_buffer[ (screen_width * (p._y)) + (p._x - 1) ] != 'W') ||
                (pac_mv_up == 1 && screen_buffer[ (screen_width * (p._y - 1)) + (p._x) ] != 'W') ||
                (pac_mv_dwn == 1 && screen_buffer[ (screen_width * (p._y + 1)) + (p._x) ] != 'W') 
            ){
                //screen_print( p._x, p._y, " " );
                // Must have ., % to remove 'c' when pac starts
                if( screen_buffer[ (screen_width * (p._y)) + (p._x) ] == '*' || 
                    screen_buffer[ (screen_width * (p._y)) + (p._x) ] == '.' ||  
                    screen_buffer[ (screen_width * (p._y)) + (p._x) ] == '%' )
                    screen_print( p._x, (p._y + score_panel_height), " " );
                //if( screen_buffer[ (screen_width * (p._y)) + (p._x) ] == '*' )
                    //screen_print( p._x, (p._y + score_panel_height), " " );
                //screen_print_char( p._x, (p._y + score_panel_height), screen_buffer[ (screen_width * p._y) + p._x ] );

                //p._x = rand() % screen_width;
                if( pac_mv_lft == 1 ){
                    p._x = p._x - 1;
                }else if( pac_mv_rht == 1 ){
                    p._x = p._x + 1;
                }else if( pac_mv_up == 1 ){
                    p._y = p._y - 1;
                }else if( pac_mv_dwn == 1 ){
                    p._y = p._y + 1;
                }
                //p._x = i;
                //p._y = rand() % screen_height;
                //p._y = 1;

                i = (i + 1) % screen_width;


                if( screen_buffer[ (screen_width * (p._y)) + (p._x) ] == '.' ){
                    //screen_print( p._x - 1, (p._y + score_panel_height), " " );
                    score++;
                    //screen_buffer[ (screen_width * (p._y)) + (p._x) ] = ' ';
                    screen_buffer[ (screen_width * (p._y)) + (p._x) ] = '*';
                    //show_score_panel();
                }else if( screen_buffer[ (screen_width * (p._y)) + (p._x) ] == '%' ){
                    power_mode = 1;
                    //screen_buffer[ (screen_width * (p._y)) + (p._x) ] = ' ';
                    //show_score_panel();
                }
                show_score_panel();
                //printf("%d ", ( (screen_width) * (p._y) ) + i);
                //printf("%d\n ", i);
                //screen_print_char( p._x, p._y, screen_buffer[ ( screen_width * (p._y) ) + i ] );
                //screen_print( p._x, p._y, &screen_buffer[ i ] );
                
            }

            if(power_mode == 0){                
                    screen_print_char( p._x, (p._y + score_panel_height), 'c' );
            }else{
                    screen_print_char( p._x, (p._y + score_panel_height), 'C' );
            }

            

            // Power mode handler
            if(power_mode == 1){
                if(pwr_tick++ == pwr_pt_ticks){
                   power_mode = 0;
                   pwr_tick = 0;
                }
            }

            alarm_fired = 0;

            //
            pac_mv_lft = 0;
            pac_mv_rht = 0;
            pac_mv_up = 0;
            pac_mv_dwn = 0;
            //
        }

        // game over check
        if( game_over_check( g, &p ) == 1 ){
            //printf("Game Over!!!");
            screen_print( 0, 1, "Game Over!!!" );
        }

    }
    tty_reset(); 
    screen_enable_echo();   

    return 0;
}

void
sigint_handler( int sig )
{
    reset_res();
    if( screen_buffer != NULL )
        free(screen_buffer);
    signal(SIGINT, SIG_DFL);
    screen_clear();
    exit(1);
}

void
sigtstp_handler( int sig )
{
    reset_res();
    signal(SIGTSTP, SIG_DFL);
}

void
sigcont_handler( int sig )
{
    screen_clear();
    screen_cur_reset();
    screen_disable_echo();
    sig_init();
    //signal(SIGTSTP, sigtstp_handler);
}

void
sigalrm_handler( int sig )
{
    struct sigaction act;    
    
    alarm_fired = 1;    

    act.sa_handler = sigalrm_handler;
    sigemptyset( &act.sa_mask );
    act.sa_flags = 0;

    sigaction( SIGALRM, &act, 0 );
}

void
reset_res()
{
    tty_reset();    
    screen_cur_reset();
    screen_enable_echo(); 
}

void
put_ghosts(struct ghost *g)
{
    int i;

    for(i=0;i<num_ghosts;i++){
        //screen_print_char( rand() % screen_width, rand() % screen_height, '@' );
        g[i]._x = rand() % screen_width;
        g[i]._y = rand() % screen_height;

        //screen_buffer[ (screen_width * (p._y)) + (p._x) ] == '*'

        
        while(screen_buffer[ (screen_width * (g[i]._y)) + (g[i]._x) ] == 'W'){
            g[i]._x = rand() % screen_width;
            g[i]._y = rand() % screen_height;

            //printf("sss");

            //if( g[i]._y <= score_panel_height ){
                //g[i]._y += score_panel_height;
            //}
        }
        

    //printf("x=%d;y=%d;c=%c ", g[i]._x, g[i]._y, screen_buffer[ (screen_width * (g[i]._y)) + (g[i]._x + 1) ]);
        

        screen_print( g[i]._x, g[i]._y + score_panel_height, "@" );
    }
}

int
game_over_check(struct ghost *g, struct pac *p)
{
    int i;

    for(i=0;i<num_ghosts;i++){
    //printf("%d ", g[i]._x);
    //printf("%d ", p->_x);
        if( g[i]._x == p->_x && (g[i]._y + score_panel_height) == (p->_y + score_panel_height) ){
            return 1;
            break;
        }
    }

    return 0;
}

void
move_ghosts(struct ghost *g, struct pac *p)
{
    int i;
    int next_x;
    int next_y;

    // move foreward, left or right

    for(i=0;i<num_ghosts;i++){
        //screen_print_char( rand() % screen_width, rand() % screen_height, '@' );
        //g[i]._x = rand() % screen_width;
        //g[i]._y = rand() % screen_height;

        //screen_buffer[ (screen_width * (p._y)) + (p._x) ] == '*'
        screen_print_char( g[i]._x, g[i]._y + score_panel_height, screen_buffer[ (screen_width * (g[i]._y)) + (g[i]._x) ] );

        //next_x = (g[i]._x + 1) % screen_width;
        //next_y = (g[i]._y + 1) % screen_height;

        if(screen_buffer[ ( screen_width * (g[i]._y % screen_height) ) + ((g[i]._x + 1) % screen_width) ] != 'W'){
            g[i]._x += 1;
        }else if(screen_buffer[ (screen_width * ((g[i]._y - 1) % screen_height) ) + (g[i]._x) ] != 'W'){
            g[i]._y -= 1;
        }else if(screen_buffer[ (screen_width * ((g[i]._y + 1) % screen_height)) + (g[i]._x) ] != 'W'){
            g[i]._y += 1;
        }

        g[i]._x = g[i]._x % screen_width;
        g[i]._y = g[i]._y % screen_height;
        
        /*        
        if(screen_buffer[ (screen_width * (next_y)) + (g[i]._x) ] == 'W'  && screen_buffer[ (screen_width * (g[i]._y)) + (next_x) ] == 'W'){
            g[i]._x += 1;
            g[i]._y += 1;
            //g[i]._y;

            //printf("sss");

            //if( g[i]._y <= score_panel_height ){
                //g[i]._y += score_panel_height;
            //}
        }else if(screen_buffer[ (screen_width * (next_y)) + (g[i]._x) ] == 'W'  && screen_buffer[ (screen_width * (g[i]._y)) + (next_x) ] != 'W'){
            g[i]._x += 1;
        }else if(screen_buffer[ (screen_width * (next_y)) + (g[i]._x) ] != 'W'  && screen_buffer[ (screen_width * (g[i]._y)) + (next_x) ] == 'W'){
            //g[i]._x += 1;
            g[i]._y += 1;
        }else if(screen_buffer[ (screen_width * (next_y)) + (g[i]._x) ] != 'W'  && screen_buffer[ (screen_width * (g[i]._y)) + (next_x) ] != 'W'){
            //g[i]._x += 1;
        }
        
        g[i]._x = g[i]._x % screen_width;
        g[i]._y = g[i]._y % screen_height;

    //printf("x=%d;y=%d ", g[i]._x, g[i]._y);
        */
        

        screen_print_char( g[i]._x, g[i]._y + score_panel_height, '@' );
    }
}

void
move_ghosts_i(struct ghost *g, struct pac *p)
{
    int i;
    int m_fwd = 0, m_left = 0, m_right = 0;

    // move foreward, left or right

    for(i=0;i<num_ghosts;i++){
        if( (p->_x - g[i]._x) > 0 )
            m_fwd = 1;
        if( (p->_y - g[i]._y) <= 0 )
            m_left = 1;
        if( (p->_y - g[i]._y) > 0 )
            m_right = 1;

        screen_print_char( g[i]._x, g[i]._y + score_panel_height, screen_buffer[ (screen_width * (g[i]._y)) + (g[i]._x) ] );

        if(m_fwd == 1 && screen_buffer[ ( screen_width * (g[i]._y) ) + ((g[i]._x + 1) % screen_width) ] != 'W'){
            // ok we can move forward            
            g[i]._x += 1;
        }
        if(m_left == 1 && screen_buffer[ (screen_width * ((g[i]._y - 1) % screen_height) ) + (g[i]._x) ] != 'W'){
            // ok we can move left            
            g[i]._y -= 1;
        }
        if(m_right == 1 && screen_buffer[ (screen_width * ((g[i]._y + 1) % screen_height)) + (g[i]._x) ] != 'W'){
            // ok we can move right
            g[i]._y += 1;
        }

        g[i]._x = g[i]._x % screen_width;
        g[i]._y = g[i]._y % screen_height;

        screen_print_char( g[i]._x, g[i]._y + score_panel_height, '@' );
    }
}


void
load_level()
{
    FILE *fp;
    int y_offset = score_panel_height;
    char buff[ 100 ];
    
    char *file = "pacman-screen_1.txt";
    int buff_p = 0;

    fp = fopen(file, "r");

    if( fp == NULL ){
        perror("fopen");
        return;
    }else{   
        while( fgets( buff, 100, fp ) != NULL ){
            //fgets( buff, 100, fp );
            buff[ strlen(buff) - 1 ] = '\0';
            //screen_print( p._x, p._y, " " );
            screen_print( 0, y_offset++, buff );
            //y_offset = y_offset + score_panel_height;
            //printf("%s\n", buff);
            //fflush(stdout);
            //printf("%s\n", buff);
            //printf("%d ", (int)strlen(buff));
            //strcpy( &screen_buffer[ buff_p + strlen(buff) ], buff );
            //strncpy( screen_buffer, "SSS", 3 );
            //memmove( screen_buffer, buff, 3 );
            //memcpy( screen_buffer, "###", 3 );
            //buff_p  = buff_p + strlen(buff);
            //screen_buffer[strlen(buff) + 1] = '\0';  
            //strncpy( screen_buffer, buff, strlen(buff) );
            strncpy( &screen_buffer[ buff_p ], buff, strlen(buff) );
            buff_p  = buff_p + strlen(buff);
            //printf("%s\n", screen_buffer); 
            //strcpy( screen_buffer, p );      
        }
    }
}

void
sig_init()
{
    //struct sigaction new_action, old_action;

    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);
    signal(SIGCONT, sigcont_handler);

    struct sigaction act;

    act.sa_handler = sigalrm_handler;
    sigemptyset( &act.sa_mask );
    act.sa_flags = 0;

    sigaction( SIGALRM, &act, 0 );

}

void
show_score_panel()
{
    char buff[40];

    sprintf( buff, "Score: %d", score );    
    
    //screen_print( 0, 0, "**********************************" );
    screen_print( 0, 0, "" );
    //screen_print( 0, 1, "*                                *" );
    screen_print( (screen_width / 2) - (strlen(buff) / 2), 1, buff );
    //screen_print( 0, 2, "**********************************" );
    screen_print( 0, 2, "" );
    //printf("%d\n", power_mode);
    //printf("%d\n", score);
    //printf("\n");
    //printf("**********************************\n");
    //printf("*                                *\n");
    //printf("*                                *\n");    
    //printf("**********************************\n");
}

void
timer_init()
{
     /* for time measurements, delay between shape movements */
     struct itimerval delay;

     /* define the first timer to set off after 40,000 micro seconds.  */
     delay.it_value.tv_sec = 0;
     delay.it_value.tv_usec = 400000;
     /* define the interval between each two timer set-offs ('clicks') */
     /* to be 40,000 micro seconds as well.                            */
     delay.it_interval.tv_sec = 0;
     delay.it_interval.tv_usec = 400000;

     /* finally, start off the timer */
     setitimer(ITIMER_REAL,&delay,0);
}

