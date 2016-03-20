/***********************************************
 * PCX File Reading Routines 
 * Author: D.Nivanthaka Amerasinghe
 *
 ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// This should be loaded first
#include "dta_types.h"
#include "pcx_load.h"

#define EXTRA_PALETTE_VERSION 5


int pcx_read_header(FILE *fp, PCXHeader *h)
{
    /*
    // This should be done in the calling routine
    FILE *fp

    if( fp = fopen( file, "r" ) == NULL ){
        printf("Error reading file %s.\n", file);
        return -1;
    }
    */

    // Take us to the top of file
    // TODO: modify this to read current location and restore it when returning
    //fseek( fp, 0, SEEK_SET );
    rewind( fp );

    if( sizeof(PCXHeader) > fread( h, 1, sizeof(PCXHeader), fp ) ){
        printf("Error reading Header data.\n");
        return -1;
    }

    return 0;
}

int pcx_read_extra_palette(FILE *fp, QWORD fsize, PCXExtraPalette *p)
{
    // Take us to the bottom of file
    fseek( fp, (fsize - sizeof(PCXExtraPalette) - 1), SEEK_SET );
    if( sizeof(PCXExtraPalette) > 
    fread( p, 1, sizeof(PCXExtraPalette), fp ) ){
        printf("Error reading Palette data.\n");
        return -1;
    }

    return 0;
}

// TODO: Improve this method. This is too slow.
long pcx_get_filesize( FILE *fp )
{
    long num_bytes = 0;

    rewind( fp );
    //fseek( fp, 0, SEEK_SET );
    while( !feof( fp ) ){
        fgetc(fp);
        num_bytes += 1;
    }
    return num_bytes;
}

int pcx_byte_decode( BYTE *b_data, int *count, FILE *fp )
{
    BYTE tmp;

    if( (tmp = fgetc(fp)) == EOF )
        return EOF;

    // Set the count to one
    *count = 1;

    if( (tmp & 0xC0) == 0xC0 ){
        // We have an encoded byte
        *count = tmp & 0x3F;
        // Get the next byte
        if( (tmp = fgetc(fp)) == EOF )
            return EOF;
    }

    *b_data = tmp;

    return 0;
}

long pcx_read_data( FILE *fp, PCXHeader *h, char *buff )
{
    PCXWindow *win;
    QWORD lsize;
    BYTE chr;
    int i, j, count;
    long t_data;

    //*buff++ = 1;
    win = &h->pcx_window;

    int x_size = win->x_max - (win->x_min + 1);
    int y_size = win->y_max - (win->y_min + 1);

    //y_size = 2;

    printf("Y = %d\n", y_size);

    lsize = (long) h->bytes_per_line * h->num_planes * y_size;

    // Remember to do this
    fseek(fp, sizeof(PCXHeader) + 1, SEEK_SET);

    for(i=0;i<lsize;){
        if( EOF == pcx_byte_decode( &chr, &count, fp ) )
            break;

        t_data += (long) count;
        //printf("count = %d\n", count);
        printf("char = %d\n", chr);
        for(j=0;j<count;j++){
            buff++;
            //buff = malloc( sizeof(BYTE) );
           *buff = chr; 
           //*(buff++) = 1; 
        }

        //break;

        i += count;
    }

    return t_data;
}

void pcx_save_file(FILE *fp, PCXHeader *h, PCXExtraPalette *e, char *buff, long d_size){
   long cnt = 0;
   
   fwrite(h, 1, sizeof(PCXHeader), fp);
   //printf("**** Version : %d\n", h->version);
   /*
   while( cnt++ < d_size )
   fputc((int)*buff++, fp);
   */
   fwrite(buff, d_size, 1, fp);
   fwrite(e, sizeof(PCXExtraPalette), 1, fp);

   fflush(fp);
}

void save_bitmap(FILE *fp, char *buff, int width, int height)
{
    fwrite(&width, 1, 2, fp);
    fwrite(&height, 1, 2, fp);
    fwrite(buff, 1, width * height, fp);

    fflush(fp);
}

// This is for testing
int main( int argc, char **argv )
{
    printf("***** PCX LOADER TEST *****\n");
    printf("Size of BYTE %d is BYTE(S).\n", (int)sizeof(BYTE));
    printf("Size of WORD %d is BYTE(S).\n", (int)sizeof(WORD));
    printf("Size of DWORD %d is BYTE(S).\n", (int)sizeof(DWORD));
    printf("Size of QWORD %d is BYTE(S).\n", (int)sizeof(QWORD));
    printf("Size of PCXHeader %d is BYTE(S).\n", (int)sizeof(PCXHeader));
    printf("Size of PCXExtraPalette %d is BYTE(S).\n", (int)sizeof(PCXExtraPalette));
    printf("***************************\n");

    FILE *fp;
    char *file = "all2.pcx";
    PCXHeader p_head;
    PCXExtraPalette p_ex;

    fp = fopen( file, "r" );
    if( fp == NULL ){
    //if( fp = fopen( file, "r" ) == NULL ){
        printf("Error reading file %s.\n", file);
        return -1;
    }

    long fsize = pcx_get_filesize(fp);
    //long d_size = fsize - (long) (sizeof(PCXHeader) + sizeof(PCXExtraPalette) );

    //long d_size = 200000;



    FILE *fp_out = fopen("out.m13", "w+");

    pcx_read_header( fp, &p_head );
    pcx_read_extra_palette( fp, fsize, &p_ex );

    long d_size = 64000;

    char *d_ptr;

    d_ptr = malloc( sizeof(BYTE) * d_size );

    if(d_ptr == NULL){
        printf("Error Allocating Memory for data.\n");
    }
    //memset( d_ptr, 0, d_size );
    pcx_read_data( fp, &p_head, d_ptr );
    //pcx_save_file( fp_out, &p_head, &p_ex, d_ptr, d_size );
    save_bitmap(fp_out, d_ptr, 320, 200);

    printf("File Information\n");
    printf("File Size = %ld BYTE(S).\n", fsize);
    printf("== Header Information ==\n");
    printf("Manufacturer : %d\n", p_head.manufacturer);
    printf("Version : %d\n", p_head.version);
    printf("Encording : %d\n", p_head.encording);
    printf("Bits per Pixel : %d\n", p_head.bitsperpixel);
    printf("HScreen Size : %d\n", p_head.h_screen_size);
    printf("VScreen Size : %d\n", p_head.v_screen_size);
    printf("Estimated data Size : %ld\n", d_size);

    printf("== Reading extra Palette Information ==\n");
    printf("Indicator : %d\n", p_ex.indicator);

    free(d_ptr);

    return 0;
}
