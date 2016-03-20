// This is an array based implementation of a queue

#include <stdio.h>
#include <assert.h>
#include <malloc.h>

static unsigned int queue_capacity;
static int queue_length = -1;

int *queue;
static int head;
static int tail;

void
init_queue( unsigned int s )
{
    queue = (int *)malloc( sizeof(int) * s );
    head = tail = queue_length = 0;
    queue_capacity = s;
}

void
enqueue( int v )
{
    assert( queue_length >= 0 );
    //tail = queue_length;

    *(queue + tail) = v;
    tail++;
    tail = tail % queue_capacity;
}

int
dequeue()
{
    int ret = -1;

    //assert( queue_length > 0 );
    //assert( head <= queue_length );
    assert( tail > 0 );
    ret = *(queue + head);
    head++;
    head = head % queue_capacity;

    return ret;
}

void
clear_queue()
{
    head = tail = queue_length = 0;
}

int
main(int argc, char *argv[])
{
    int i;

    init_queue( 5 );

    enqueue( 1 );
    enqueue( 2 );
    enqueue( 3 );
    enqueue( 4 );
    enqueue( 5 );
    enqueue( 6 );

    i = dequeue();

    printf("i = %d\n", i);
    
    i = dequeue();

    printf("i = %d\n", i);

    i = dequeue();

    printf("i = %d\n", i);

    return 0;
}
