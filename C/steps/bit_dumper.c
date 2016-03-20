#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dumper{
    unsigned short width;
    unsigned short height;
    void *data;
};

FILE *dump_file;

int open_dump(char *);
int write_dump(struct dumper *);
void dump_close();

int main(int argc, char **argv)
{
    char *ptr;
    //open_dump("test.out");
    open_dump("-");

    struct dumper d;
    d.width = 16;
    d.height = 2;
    d.data = malloc( sizeof(char) * d.width * d.height );
    memset(d.data, '0', sizeof(char) * d.width * d.height);
    ptr = d.data;
    ptr[5] = '1';

    write_dump(&d);
    dump_close();

    return 0;
}

int open_dump(char *file)
{
    if(file != "-"){
        dump_file = fopen(file, "w+");
    }else{
        dump_file = stdout;
    }

    if(dump_file == NULL){
        perror("Opening Dump File");
        return -1;
    }else{
        return 0;
    }
}

int write_dump(struct dumper *d){
    int i;
    char out[d->width + 1];
    void *ptr;

    if( dump_file != NULL ){
        for(i=0;i<d->height;i++){
            ptr = d->data;
            memcpy( out, (char *)(ptr + (d->width * i)), d->width );
            out[d->width]     = '\n';
            out[d->width + 1] = '\0';
            //printf("d = %d\n", d->width);
            fputs( out, dump_file );
        }
        fflush(dump_file);
    }
}

void dump_close()
{
    if(dump_file != NULL){
        fflush(dump_file);
        fclose(dump_file);
    }
}

