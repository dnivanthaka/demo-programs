#ifndef __PART_INFO__
#define __PART_INFO__   1

#define PC_PARTITION_SIGNATURE          0xaa55
#define PARTITION_BOOT_FLAG             0x80

//partiton types
#define PARTITION_TYPE_NONE             0x00
#define PARTITION_TYPE_FAT12            0x01
#define PARTITION_TYPE_FAT16_LT32M      0x04
#define PARTITION_TYPE_EXTENDED         0x05
#define PARTITION_TYPE_FAT16_GT32M      0x06
#define PARTITION_TYPE_NTFS_HPFS        0x07
#define PARTITION_TYPE_FAT32            0x0b
#define PARTITION_TYPE_FAT32_LBA        0x0c
#define PARTITION_TYPE_FAT16_LBA        0x0e
#define PARTITION_TYPE_WIN95_EXTENDED   0x0f
#define PARTITION_TYPE_EZD              0x55
#define PARTITION_TYPE_MINIX            0x80
#define PARTITION_TYPE_LINUX_MINIX      0x81
#define PARTITION_TYPE_EXT2FS           0x83
#define PARTITION_TYPE_LINUX_EXTENDED   0x85
#define PARTITION_TYPE_VSTAFS           0x9e
#define PARTITION_TYPE_FREEBSD          0xa5
#define PARTITION_TYPE_OPENBSD          0xa6
#define PARTITION_TYPE_NETBSD           0xa9
#define PARTITION_TYPE_LINUX_RAID       0xfd

struct partition_info
{
    unsigned char boot_indicator;
    // also called 'side'
    unsigned char part_begin_head;
    unsigned char part_begin_sect;
    // also called 'track'
    unsigned char part_begin_cylinder;
    unsigned char part_type;
    unsigned char part_end_head;
    unsigned char part_end_sect;
    unsigned char part_end_cylinder;
    unsigned int num_sect_after_part;
    unsigned int total_num_sect_part;
} __attribute__((packed));

struct pc_mbr 
{
    char boot_code[446];
    struct partition_info partition[4];
    //char partitions_info[64];
    //char boot_signature[2];
    short int boot_signature;
} __attribute__((packed));

struct pc_boot_record{
    unsigned int abs_sector;
    unsigned int offset;
    int is_extended;
    struct pc_mbr brecord;
    struct pc_boot_record *next;
};

//void print_partition_table(struct partition_info *partition[4]);
void print_partition_info(struct partition_info *);
void print_table_header(int, int);
#endif //__PART_INFO__

