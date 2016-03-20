/***********************************************
 * PCX File Metadata structures
 * Author: D.Nivanthaka Amerasinghe
 *
 ***********************************************/
#ifndef __PCX_LOADER__
#define __PCX_LOADER__
typedef struct {
    WORD x_min;
    WORD y_min;
    WORD x_max;
    WORD y_max;
} PCXWindow;

typedef struct {
    BYTE red;
    BYTE green;
    BYTE blue;
} PCXTriple;

typedef struct {
    BYTE manufacturer;
    BYTE version;
    BYTE encording;
    BYTE bitsperpixel;
    PCXWindow pcx_window;
    WORD h_dpi;
    WORD v_dpi;
    PCXTriple triples[16];
    BYTE reserved;
    BYTE num_planes;
    WORD bytes_per_line;
    WORD palette_info;
    WORD h_screen_size;
    WORD v_screen_size;
    BYTE filler[54];
} PCXHeader;

typedef struct {
    BYTE indicator;
    PCXTriple triples[256];
} PCXExtraPalette;
#endif
