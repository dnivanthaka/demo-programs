// sample memory manager from IBM URL:http://www.ibm.com/developerworks/linux/library/l-memory/

#include <unistd.h>

#include "malloc.h"

int is_initialized = 0;
void *mm_start;
void *last_valid_addr;

void
malloc_init()
{
    last_valid_addr = sbrk(0);
    mm_start = last_valid_addr;
    is_initialized = 1;
}

void
free( void *firstbyte )
{
    struct mm_ctrl_block *mcb;

    mcb = firstbyte - sizeof( mm_ctrl_block );
    mcb->is_available = 1;

    return;
}

void
malloc(long num_bytes)
{
    void *current_location;
    void *allocated_location = 0;

    struct mm_ctrl_block *mcb;

    if( ! is_initialized ){
       malloc_init();     
    }

    num_bytes = num_bytes + sizeof(struct mm_ctrl_block);
    current_location = mm_start;
    while(current_location != last_valid_addr){
        mcb = (struct mm_ctrl_block *)current_location;
        if( mcb->is_available && mcb->size >= num_bytes){
            mcb->is_available = 0;
            allocated_location = current_location;
            break;
        }

        current_location += mcb->size;
    }

    if( ! allocated_location ){
        sbrk(num_bytes);

        allocated_location = last_valid_addr;
        last_valid_addr += num_bytes;
        mcb = allocated_location;
        mcb->is_available = 0;
        mcb->size = num_bytes;
    }

    allocated_location += sizeof(struct mm_ctrl_block);
    return allocated_location;
}
