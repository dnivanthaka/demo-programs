#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "hash_table.h"

/*
 * Generates an index based on the given key.
 * Calculates the size of hash table on its own.
 * Returns -1 if the index value cannot be generated.
 */
int
hash_value(struct hash_table *htable, char *key)
{
    int tbl_size = 0;
    int index = -1;
    int count = 0;
    char *tmp;

    tmp = key;
    //printf("key is %s\n", key);

    while(htable != NULL){
        tbl_size++;
        //printf("1\n");
        htable = htable->next;
    }

    //printf("tbl_size = %d\n", tbl_size);

    if(tbl_size > 0){
        while(*tmp != '\0'){
            count += *tmp;
            printf("%d\n", *tmp);
            tmp++;
        }

        //printf("count = %d\n", count);
        index = count % tbl_size;
    }

    //printf("index = %d\n", index);

    return index;
}

struct 
hash_table *create_hash_table(int size)
{
    int count = 0;
    struct hash_table *ht, *tmp;

    while(count++ != size){
        //printf("2\n");
        if(ht == NULL){
            tmp = malloc((int)sizeof(struct hash_table));
            tmp->is_free = 1;
            ht = tmp;
            continue;
        }

        if(tmp != NULL){
            while(tmp->next != NULL)
                tmp = tmp->next;
        }

        tmp->next = malloc((int)sizeof(struct hash_table));
        if( tmp->next == NULL)
            return NULL;
        tmp->next->is_free = 1;
    }

    //ht = tmp;

    return ht;
}

int 
hash_insert(struct hash_table *htable, char *key, void *element)
{
    int tbl_index;
    struct hash_table *tmp;
    int i = 0;
    int ret = -1;

    tmp = htable;

    tbl_index = hash_value(htable, key);
    printf("tbl_ndex = %d\n", tbl_index);

    while(tbl_index != i){
        tmp = tmp->next;
        i++;
    }

    if(tmp->is_free == 1){
        //printf("Im here\n");
        memcpy(tmp->data, element, strlen((char *)element));
        tmp->is_free = 0;
        ret = 1;
    }else{
        // move to the next cell and see if its available, if not go to next one
        while(tmp->is_free != 1 && tmp->next != NULL)
            tmp = tmp->next;

        // if we did not find an empty cell and we are at the end, alert the table is full
        if(tmp->is_free != 0 && tmp->next == NULL){
            ret = -1;
        }else{
            // yay!!! we found an empty cell
            memcpy(tmp->data, element, strlen((char *)element));
            tmp->is_free = 0;
            ret = 1;
        }
    }

    return ret;
}

void *
hash_remove(struct hash_table *htable, char *key)
{
    int found = 0;
    int count = 0;
    int key_index = hash_value(htable, key);
    struct hash_table *tmp;

    while(htable != NULL ){
        if( count == key_index && 
            htable->is_free == 0 ){
            found = 1;
            tmp = malloc((int)sizeof(struct hash_table));
            tmp = memcpy(tmp, htable, (int)sizeof(struct hash_table));
            htable->is_free = 1;
            break;
        }
        ++count;

        htable = htable->next;
    }

    if(found != 0 && tmp != NULL){
        return tmp;
    }else
        return NULL;
    }
}

int 
hash_num_elements(struct hash_table *htable)
{
    int count = 0;

    while(htable != NULL ){
        if(htable->is_free == 0)
            ++count;

        htable = htable->next;
    }

    return count;
}

void 
destroy_hash_table(struct hash_table *htable)
{
    while(htable != NULL){
        htable->is_free = 1;

        htable = htable->next;
    }
}

void
hash_set_resize_high_density(struct hash_table *htable, int fill_factor)
{

}

int
hash_set_resize_low_density(struct hash_table *htable, int fill_factor)
{

}

int
hash_get_resize_high_density(struct hash_table *htable)
{

}

int
hash_get_resize_low_density(struct hash_table *htable)
{

}
