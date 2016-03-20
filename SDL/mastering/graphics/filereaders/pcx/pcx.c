#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "pcx.h"

int
read_header( FILE *fp, pcx_header_t *header )
{
    // reset the file pointer, to begining of file
    if( fseek( fp, 0, SEEK_SET ) == -1 ){
        fprintf( stderr, "Error seeking header data: %s %d", __FILE__, __LINE__  );
        return EXIT_FAILURE;
    }

    rewind(fp);

    if( fread( header, 1, sizeof( pcx_header_t ), fp ) < sizeof( pcx_header_t ) ){
        fprintf( stderr, "Error reading header data: %s %d", __FILE__, __LINE__  );
        return EXIT_FAILURE;
    }

    printf("Width = %d\n", (int)header->pcx_window.y_max );
    printf("Manufacturer : %d\n", header->manufacturer);
    printf("Version : %d\n", header->version);
    printf("Encording : %d\n", header->encording);
    printf("Bits per Pixel : %d\n", header->bitsperpixel);
    //printf("size = %d\n", (int)sizeof(pcx_header_t) );
    
    return 0;
}

int
read_data( FILE *fp, pcx_picture_t *image )
{
    int count, run_len;
    unsigned char data;

    // reset the file pointer, to begining of file
    if( fseek( fp, sizeof( pcx_header_t ), SEEK_SET ) == -1 ){
        fprintf( stderr, "Error seeking header data: %s %d", __FILE__, __LINE__  );
        return EXIT_FAILURE;
    }

    count = 0;

    image->buffer = (unsigned char *)malloc( (image->header.pcx_window.x_max + 1) * (image->header.pcx_window.y_max + 1) );

    while( count < ( (image->header.pcx_window.x_max + 1) * (image->header.pcx_window.y_max + 1) ) ){
        data = (unsigned char)fgetc(fp);

        // Check if this a RLE run
        if( data >= 192 && data <= 255 ){
            run_len = data - 192;
            // Reading actual data
            data = (unsigned char)fgetc(fp);

            while( run_len-- > 0 ){
                image->buffer[ count++ ] = data;
            }
        }else{
            // Copying direct data
            image->buffer[ count++ ] = data;
        }
    }
    
    return count;
}

int 
read_palette( FILE *fp, pcx_picture_t *image )
{
    int i;

    // move the file pointer, to last 768 bytes file
    if( fseek( fp, -768L, SEEK_END ) == -1 ){
        fprintf( stderr, "Error seeking data: %s %d", __FILE__, __LINE__  );
        return EXIT_FAILURE;
    }
    
    for(i=0;i<256;i++){
        image->palette.triples[ i ].red   = (unsigned char)(fgetc( fp ) >> 2);
        image->palette.triples[ i ].green = (unsigned char)(fgetc( fp ) >> 2);
        image->palette.triples[ i ].blue  = (unsigned char)(fgetc( fp ) >> 2);
    }

    return 0;
}

int
read_pcx( char *file, pcx_picture_t *image )
{
    FILE *fp;
    // move the file pointer, to last 768 bytes file
    if( (fp = fopen( file, "r" )) == NULL ){
        fprintf( stderr, "Error opening file: %s %d", __FILE__, __LINE__  );
        return EXIT_FAILURE;
    }

    // reading header data
    read_header( fp, &image->header );

    // reading image data
    read_data( fp, image );

    // reading palette data
    read_palette( fp, image );

    return 0;
}
