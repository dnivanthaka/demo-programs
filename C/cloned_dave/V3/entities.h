#ifndef __ENITIES_HEADER__
#define __ENITIES_HEADER__

//int get_collision_ob( struct player *, SDL_Surface *, int );
void add_object( struct ga_object *, int, int, int, int, int );
void print_ga_objects( struct ga_object *go );
collision_info * get_object( struct ga_object *, int , int, int, int );
#endif
