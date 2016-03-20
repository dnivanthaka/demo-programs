#ifndef __HASH_ALGO__
#define __HASH_ALGO__

#define DATA_SIZE_BYTES 255

struct hash_table {
    char data[255];
    unsigned short is_free;
    struct hash_table *next;
};

struct hash_table *create_hash_table(int size);
int hash_insert(struct hash_table *htable, char *key, void *element);
void *hash_remove(struct hash_table *htable, char *key);
int hash_num_elements(struct hash_table *htable);
void destroy_hash_table(struct hash_table *htable);
int hash_value(struct hash_table *htable, char *key);
// extended api functions
void hash_set_resize_high_density(struct hash_table *htable, int fill_factor);
int hash_set_resize_low_density(struct hash_table *htable, int fill_factor);
int hash_get_resize_high_density(struct hash_table *htable);
void hash_get_resize_low_density(struct hash_table *htable);
#endif //__HASH_ALGO__
