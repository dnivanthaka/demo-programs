#ifndef __INPUT_H__
#define __INPUT_H__
extern bool keyevents[];
//extern static SDL_Event event;

void init_events();
void handle_events_input();
bool get_event_status(Uint16 e);

#endif
