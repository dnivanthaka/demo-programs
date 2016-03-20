#ifndef __EVENTS_HEADER__
#define __EVENTS_HEADER__

#define MAXEVENTS 4

typedef enum {
    ev_keyup,
    ev_keydown
} evtype_t;

typedef struct {
    evtype_t type;
    SDL_keysym sym;
} event_t;

void init_event_queue();
void enqueue_event( event_t *ev );
event_t *dequeue_event();
/*
void process_events();
void ev_responder( event_t *ev );
*/

#endif
