#include <stdio.h>

#include "part_table.h"

void
print_table_header(int drive, int offset)
{
   
    printf("\nPartition info for physical drive %d\n", 1);
    printf("-----------------------------------------------------------------------------");
    printf("\nPartition table st offset %d\n", 1);
    printf("======== ======================= ==== === ==== ==== === ==== =========== =========\n");
    printf("Bootable Type                    Head Cyl Sect Head Cyl Sect Boot Sct    Num Sct  \n");
    printf("======== ======================= ==== === ==== ==== === ==== =========== =========\n");
}

void
print_partition_info(struct partition_info *partition)
{
    //printf("     0x%x ", (partition->boot_indicator & 0x80 == 80) ? 0x80 : 0x00);
    printf("%5c%c%02x", '0', 'x', partition->boot_indicator & 0x80);
    printf("%c", ' ');
    printf("%c%c%02x=", '0', 'x', partition->part_type & 0xff);
    switch(partition->part_type){
        case (unsigned char)PARTITION_TYPE_NONE: 
            printf("%-18s", "Empty");
            break;
        case (unsigned char)PARTITION_TYPE_FAT12: 
            printf("%-18s","FAT-12");
            break;
        case (unsigned char)PARTITION_TYPE_FAT16_LT32M: 
            printf("%-18s","FAT-18");
            break;
        case (unsigned char)PARTITION_TYPE_EXTENDED: 
            printf("%-18s","Extended");
            break;
        case (unsigned char)PARTITION_TYPE_FAT16_GT32M: 
            printf("%-18s","FAT-18");
            break;
        case (unsigned char)PARTITION_TYPE_NTFS_HPFS:
            printf("%-18s","NTFS/HPFS/OS2");
            break;
        case (unsigned char)PARTITION_TYPE_FAT32: 
            printf("%-18s","FAT-32");
            break;
        case (unsigned char)PARTITION_TYPE_FAT32_LBA: 
            printf("%-18s","FAT-32");
            break;
        case (unsigned char)PARTITION_TYPE_FAT16_LBA: 
            printf("%-18s","FAT-18");
            break;
        case (unsigned char)PARTITION_TYPE_WIN95_EXTENDED: 
            printf("%-18s","Extended-W95");
            break;
        case (unsigned char)PARTITION_TYPE_EZD: 
            printf("%-18s","EZD");
            break;
        case (unsigned char)PARTITION_TYPE_MINIX: 
            printf("%-18s","MINIX");
            break;
        case (unsigned char)PARTITION_TYPE_LINUX_MINIX: 
            printf("%-18s","MINIX");
            break;
        case (unsigned char)PARTITION_TYPE_EXT2FS: 
            printf("%-18s","Ext2/Ext3");
            break;
        case (unsigned char)PARTITION_TYPE_LINUX_EXTENDED: 
            printf("%-18s","Extended");
            break;
        case (unsigned char)PARTITION_TYPE_VSTAFS: 
            printf("%-18s","VSTAFS");
            break;
        case (unsigned char)PARTITION_TYPE_FREEBSD: 
            printf("%-18s","Free BSD");
            break;
        case (unsigned char)PARTITION_TYPE_OPENBSD: 
            printf("%-18s","Open BSD");
            break;
        case (unsigned char)PARTITION_TYPE_NETBSD: 
            printf("%-18s","Net BSD");
            break;
        case (unsigned char)PARTITION_TYPE_LINUX_RAID: 
            printf("%-18s","RAID-Linux");
            break;
        default:
            printf("%-18s","Unknown");
        break;
    }
    //printf("%8c", ' ');
    printf("%c", ' ');
    printf("%-4d ", partition->part_begin_head);
    printf("%-3d ", partition->part_begin_cylinder);
    printf("%-4d ", partition->part_begin_sect);
    printf("%-4d ", partition->part_end_head);
    printf("%-3d ", partition->part_end_cylinder);
    printf("%-4d ", partition->part_end_sect);
    printf("%-11d ", partition->num_sect_after_part);
    printf("%-11d ", partition->total_num_sect_part);
    printf("\n");
}
