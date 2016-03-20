#ifndef __ASM_IO_H__
#define __ASM_IO_H__
void inline outb(char value, unsigned short port)
{
    __asm__ volatile(
        "outb %0, %1;"
        ::"a"((char) value), "d"((unsigned short) port)
    );
}
unsigned char inline inb(unsigned short port)
{
    unsigned char v;
    __asm__ volatile(
        "inb %1 %0;"
        :"=a" (v): "d" ((unsigned short) port)
    );

    return v;
}
#endif // __ASM_IO_H__
