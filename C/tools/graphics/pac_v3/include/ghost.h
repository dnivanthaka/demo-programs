#ifndef __GHOST_H__
#define __GHOST_H__

enum direction {
    left,
    right
};

struct ghost {
    unsigned int x;
    unsigned int y;
    enum direction dir;
};
#endif
