#include <stdio.h>

#include "hash_table.h"

int 
main(int argc, char **argv)
{
    struct hash_table *htable;
    char *key   = "One";
    char *value = "Dinusha";
    char *key1   = "Four";
    char *value1 = "Dinusha2";
    int ret;
    int count;

    htable = create_hash_table(6);

    ret = hash_insert(htable, key, value);

    printf("ret = %d\n", ret);

    count = hash_num_elements(htable);

    printf("count = %d\n", count);

    ret = hash_insert(htable, key1, value1);

    printf("ret = %d\n", ret);

    count = hash_num_elements(htable);

    printf("count = %d\n", count);
    return 0;
}
