#ifndef __LEVELS_HEADER__
#define __LEVELS_HEADER__

#define LINE_BUFF_SIZE 255
/*
struct level {
    int width;
    int height;
    void *data;
};
*/

bool load_level_map( char *levelfile, level *lvl );
int get_obj_type_ofsset( level *lvl, int offset );
int get_obj_type( level *lvl, int x, int y );

#endif
