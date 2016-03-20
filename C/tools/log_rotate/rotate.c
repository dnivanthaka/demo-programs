#include <stdio.h>

void
rotate(char *filename, int num_copies)
{
    char file[60];
    char old_name[60];
    char new_name[60];
    int i;
    char suffix[3];
    int status = 0;

    //sprintf(file, "%s.%d", filename, num_copies);
    /*
    if(remove( file ) == 0)
        status = 1;
    */
    for(i=num_copies;i>0;i--){
        if(i == num_copies){
            sprintf(file, "%s.%d", filename, num_copies);
            if( remove(file) == 0)
                continue;
        }

        sprintf(old_name, "%s.%d", filename, i);
        sprintf(new_name, "%s.%d", filename, (i + 1));
        rename(old_name, new_name);
    }

    sprintf(old_name, "%s", filename);
    sprintf(new_name, "%s.%d", filename, 1);
    rename(old_name, new_name);

    fopen(filename, "a");
}

int
main(int argc, char *argv[])
{
    char *file = "test.out";

    rotate(file, 4);
    return 0;
}
