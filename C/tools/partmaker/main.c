#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "part_table.h"
#include "io.h"

#define NUM_PARTS_IN_TABLE    4
#define PART_SIZE_BYTES       16
#define BOOTSEC_SIZE_BYTES    512
#define PART_TABLE_SIZE_BYTES (NUM_PARTS_IN_TABLE * PART_SIZE_BYTES)


int main(int argc, char *argv[])
{
    unsigned char *buffer;
    ssize_t ret;
    struct pc_mbr *mbr;
    mbr = malloc( sizeof(struct pc_mbr) );
    //pt->partitions_info = malloc( sizeof(partition_info) );
    //partition_info *partition[4];
    int i;

    //buffer = malloc(NUM_PARTS_IN_TABLE * PART_SIZE_BYTES);
    buffer = malloc(BOOTSEC_SIZE_BYTES);
    //ret = read_disk_data(argv[1], buffer, 64, 446);
    ret = read_disk_data(argv[1], buffer, 512, 0);
    //ret = read_disk_data(argv[1], (char *)pt, 512, 0);
    printf("ret of device %d\n", (int)ret);
    //printf("data = %s\n", buffer);
    //printf("%d\n", (int)sizeof(short int));
    printf("%d\n", (int)sizeof(struct pc_mbr));
    /*
    for(i=0;i<NUM_PARTS_IN_TABLE;i++){
        partition[i] = malloc(sizeof(partition_info));
        memcpy(partition[i], &buffer[(sizeof(partition_info) * i)], sizeof(partition_info));
        printf("==================================================\n");
        printf("partition no: %d\n", (i + 1));
        printf("boot indicator = %x\n", partition[i]->boot_indicator);
        printf("part type = %x\n", partition[i]->part_type);
    }
    */
    memcpy(mbr, buffer, sizeof(struct pc_mbr));
    if((mbr->boot_signature & 0xaa55) == 0xffffaa55){
        printf("This drive is bootable........\n");
    }

    print_table_header(1, 1);
    
    //printf("%x\n", mbr->boot_signature & 0xaa55);
    for(i=0;i<NUM_PARTS_IN_TABLE;i++){
        //partition[i] = malloc(sizeof(partition_info));
        //memcpy(partition[i], &pt->partitions_info[(sizeof(partition_info) * i)], sizeof(partition_info));
        //printf("==================================================\n");
        //printf("Stat  Type    Head\n");
        //printf("partition no: %10d\n", (i + 1));
        //printf("boot indicator = %x\n", pt->partition[i].boot_indicator);
        //printf("part type = %x\n", pt->partition[i].part_type);
        //printf("boot sig = %x\n", *(pt->boot_signature));
        //printf("boot indicator = %5x\n", mbr->partition[i].boot_indicator & 0x80);
        //printf("part type = %x\n", mbr->partition[i].part_type);
        //printf("boot sig = %x\n", mbr->boot_signature);
        //print_partition_table(mbr->partition);
        print_partition_info(&mbr->partition[i]);
    }

    //printf("==================================================\n");

    return 0;
}

