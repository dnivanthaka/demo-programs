#include "bits.h"

int 
bitAND(int x, int y)
{
    // NOR Gate
    int z = ~x | ~y;
    //int z = x | y;
    return ~z;
}

int 
bitXOR(int x, int y)
{
    return ~(x & y) & ~(~x & ~y);
}

int 
isEqual(int x, int y)
{
    return !(x ^ y);
}

int 
evenBITS()
{
    
    return 2;
}

int 
fitsBITS(int x, int n)
{
    return 2;
}

int
bitMask(int highbit, int lowbit)
{
    return 2;
}

int
conditional(int x, int y, int z)
{
    return 2;
}

int
reverseBytes(int x)
{
    return 2;
}

int 
bang(int x)
{
    return 2;
}

int
bitCount(int x)
{
    return 2;
}

int
tmin()
{
    return 2;
}

int
isNegative(int x)
{
    return 2;
}

int
multiFiveEights(int x)
{
    return 2;
}

static int
sum(int x, int y)
{
    return x+y;
}

int 
sum3(int x, int y, int z)
{
    int word1 = 0;
    int word2 = 0;


    return sum(word1, word2);
}

int 
addOK(int x, int y)
{
    return 2;
}

int
isLess(int x, int y)
{
    return 2;
}

int 
abs(int x)
{
    return 2;
}

int 
isNonZero(int x)
{
    return 2;
}

int
tc2sm(int x)
{
    return 2;
}
