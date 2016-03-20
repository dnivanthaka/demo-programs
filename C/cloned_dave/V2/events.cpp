#include "SDL/SDL.h"
#include "gtypedef.h"

#include "events.h"

static event_t events[ MAXEVENTS ];
static int eventhead;
static int eventtail;

void
init_event_queue()
{
    eventhead = 0;
    eventtail = MAXEVENTS - 1;
}

void
enqueue_event( event_t *ev )
{
    printf("Adding event\n");
    eventtail = (eventtail + 1) % MAXEVENTS;
    events[ eventtail ] = *ev;
}

event_t *
dequeue_event()
{
    event_t *ret;
    printf("Removing event\n");

    if( eventhead == eventtail ){
        return NULL;
    }

    ret = &events[ eventhead ];
    eventhead = (eventhead + 1) % MAXEVENTS;

    printf("ppp %d\n", ret->type);

    return ret;
}

void
process_events()
{
    event_t *ev;

    while( (ev = dequeue_event()) != NULL ){
        ev_responder( ev );
    }
}

void
ev_responder( event_t *ev ){
    if(ev->type == ev_keydown){
         if( ev->sym.sym == SDLK_RIGHT ){
              //right_pressed = true;
              //printf("XXXXXXXXX");
         }
         if( ev->sym.sym == SDLK_LEFT ){
                //left_pressed = true;
              //printf("YYYYYYYY");
         }
    }
    if( ev->type == ev_keyup ){
        printf("Im here");
        if( ev->sym.sym == SDLK_RIGHT ){
            //right_pressed = false;
        }
        if( ev->sym.sym == SDLK_LEFT ){
            //left_pressed = false;
        }
    }
}
