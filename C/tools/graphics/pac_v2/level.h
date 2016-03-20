#ifndef __LEVEL_H__
#define __LEVEL_H__
struct layout{
    unsigned short level;
    unsigned int width;
    unsigned int height;
    unsigned char *data;
}

void draw_layout();
void read_layout(struct layout *, int, char **);
#endif // __LEVEL_H__
