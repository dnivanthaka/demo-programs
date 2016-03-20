// HEADER FILES ------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gtypedef.h"
#include "level.h"

// MACROS ------------------------------------------------------------------

// TYPES -------------------------------------------------------------------

// EXTERNAL FUNCTION PROTOTYPES --------------------------------------------

// PUBLIC FUNCTION PROTOTYPES ----------------------------------------------

// PRIVATE FUNCTION PROTOTYPES ---------------------------------------------

// EXTERNAL DATA DECLARATIONS ----------------------------------------------

// PUBLIC DATA DEFINITIONS -------------------------------------------------

// PRIVATE DATA DEFINITIONS ------------------------------------------------

// CODE --------------------------------------------------------------------

bool
load_level_map( char *levelfile, level *lvl )
{
    FILE *fp;
    int w, h, offset = 0;
    char buffer[ LINE_BUFF_SIZE ];
    int st_pos = 0;
    char *chr_s;

    fp = fopen( levelfile, "r" );

    if( fp == NULL ){
        printf("%s: Cannot open level file %s\n", __FILE__, levelfile);
        return false;
    }

    if ( fgets( buffer, sizeof(int), fp ) == NULL  ){
        printf("%s: Cannot read level file %s\n", __FILE__, levelfile);
        return false;    
    }

    buffer[ strlen(buffer) - 1 ] = '\0';
    w = atoi( buffer );

    if ( fgets( buffer, sizeof(int), fp ) == NULL  ){
        printf("%s: Cannot read level file %s\n", __FILE__, levelfile);
        return false;    
    }

    buffer[ strlen(buffer) - 1 ] = '\0';
    h = atoi( buffer );

    lvl->width  = w;
    lvl->height = h;
    lvl->data   = (char *)malloc( sizeof(char) * w * h );

    if( lvl->data == NULL ){
        printf("%s: Malloc Failed \n", __FILE__);
        return false;
    }

    while( fgets( buffer, LINE_BUFF_SIZE, fp ) != NULL ){
        buffer[ strlen(buffer) - 1 ] = '\0';    
        //printf("offset %d\n", offset);
        //printf("%s\n", buffer);

        //memcpy( lvl->data + offset, buffer, strlen(buffer) );
        chr_s = strchr( buffer, 'S' );
        if( chr_s != NULL ){
            st_pos = chr_s - buffer;
            lvl->start_pos.x = st_pos;
            lvl->start_pos.y = (offset / (lvl->width - 1));
        }
        memcpy( lvl->data + offset, buffer, strlen(buffer) );
        //strncpy( lvl->data, buffer, strlen(buffer) );
        //printf("%s\n", lvl->data);
        offset += strlen(buffer);
    }

    return true;
}

int 
get_obj_type_ofsset( level *lvl, int offset )
{
    char b[3];
    int ret = -1;

    //if( (offset % 2) == 1 )
        //offset += 1;
    // since we are going in two numebr per block, multiply offset by 2
    memcpy( b, &lvl->data[ offset * 2 ], 2 );
    b[3] = '\0';
    ret = atoi( b );
}

int
get_obj_type( level *lvl, int x, int y )
{
    int offset, ret = -1;

    //offset = ( ( ((lvl->width - 1) / 2) * x ) + y ) % (lvl->width * lvl->height);
    offset = ( ( ((lvl->width - 1) / 2) * y ) + x );
    ret = get_obj_type_ofsset( lvl, offset );
    return ret;
}

