#include <signal.h>
#include <stdio.h>

void termination_handler( int );

int
main(int argc, char *argv[])
{
   struct sigaction new_action, old_action; 

   new_action.sa_handler = termination_handler;
   sigemptyset( &new_action.sa_mask );
   new_action.sa_flags = 0;

   sigaction(SIGINT, NULL, &old_action);
   if(old_action.sa_handler != SIG_IGN)
        sigaction(SIGINT, &new_action, NULL);
   sigaction(SIGHUP, NULL, &old_action);
   if(old_action.sa_handler != SIG_IGN)
        sigaction(SIGHUP, &new_action, NULL);
   sigaction(SIGTERM, NULL, &old_action);
   if(old_action.sa_handler != SIG_IGN)
        sigaction(SIGTERM, &new_action, NULL);

   while(1);

   return 0;
}

void
termination_handler( int signum )
{
    printf("Signal Recieved with value %d\n", signum);
}
