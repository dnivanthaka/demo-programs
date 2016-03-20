#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct node{
    struct node *LEFT_CHILD;
    int data;
    struct node *RIGHT_CHILD;
}NODE;

void insert_data( NODE **n, int data ){
    NODE *tmp;
    if( *n == NULL ){
        printf("Im creating the root!!!\n");
        tmp = malloc( sizeof( NODE ) );
        tmp->LEFT_CHILD = NULL;
        tmp->data = data;
        tmp->RIGHT_CHILD = NULL;
        *n = tmp;
        /*
        *n = malloc( sizeof( NODE ) );
        (*n)->LEFT_CHILD = NULL;
        (*n)->data = data;
        (*n)->RIGHT_CHILD = NULL;
        //n = &tmp;
        */
    }else if( (*n)->data < data ){
        if( (*n)->RIGHT_CHILD != NULL ){
            insert_data(&((*n)->RIGHT_CHILD), data);
        }else{
            printf("Im creating a new node on right!!!\n");
            tmp = malloc( sizeof( NODE ) );
            tmp->LEFT_CHILD = NULL;
            tmp->data = data;
            tmp->RIGHT_CHILD = NULL;

            (*n)->RIGHT_CHILD = tmp;
        }
    }else if( (*n)->data > data ){
        if( (*n)->LEFT_CHILD != NULL ){
            insert_data(&((*n)->LEFT_CHILD), data);
        }else{
            printf("Im creating a new node on left!!!\n");
            tmp = malloc( sizeof( NODE ) );
            tmp->LEFT_CHILD = NULL;
            tmp->data = data;
            tmp->RIGHT_CHILD = NULL;

            (*n)->LEFT_CHILD = tmp;
        }
    }
}

void delete_node( NODE **n, int val ){
    if( *n != NULL ){
        if( ((*n)->LEFT_CHILD)->data == val ){
            (*n)->LEFT_CHILD = NULL;
        }else if( ((*n)->RIGHT_CHILD)->data == val ){
            (*n)->RIGHT_CHILD = NULL;
        }else{
            if( (*n)->data > val ){
                // Traverse the left sub tree
                printf( "Delete is going to traverse the left sub tree\n" );
                delete_node(&((*n)->LEFT_CHILD), val);
            }else if( (*n)->data < val ){
                // Traverse the right sub tree
                printf( "Delete is going to traverse the right sub tree\n" );
                delete_node(&((*n)->RIGHT_CHILD), val);
            }
        }
    }else{
        printf( "\nTree is Empty\n" );
    }
}

void search_node( NODE **n, int val ){
    if( *n != NULL ){
        if( (*n)->data == val ){
            printf("Found value %d\n", val);
        }else if( (*n)->data > val ){
            // Traverse the left sub tree
            printf( "Going to traverse the left sub tree\n" );
            search_node(&((*n)->LEFT_CHILD), val);
        }else if( (*n)->data < val ){
            // Traverse the right sub tree
            printf( "Going to traverse the right sub tree\n" );
            search_node(&((*n)->RIGHT_CHILD), val);
        }
    }else{
        printf( "\nTree is Empty\n" );
    }
}
void traverse_preorder( NODE **n ){
    printf( "preorder value = %d\n", (*n)->data );
    if( (*n)->LEFT_CHILD != NULL ){
        traverse_preorder( &((*n)->LEFT_CHILD) );
    }
    if( (*n)->RIGHT_CHILD != NULL ){
        traverse_preorder( &((*n)->RIGHT_CHILD) );
    }
}
void traverse_postorder( NODE **n ){
    if( (*n)->LEFT_CHILD != NULL ){
        traverse_postorder( &((*n)->LEFT_CHILD) );
    }
    if( (*n)->RIGHT_CHILD != NULL ){
        traverse_postorder( &((*n)->RIGHT_CHILD) );
    }
    printf( "postorder value = %d\n", (*n)->data );
}

void traverse_inorder( NODE **n ){
    if( (*n)->LEFT_CHILD != NULL ){
        traverse_inorder( &((*n)->LEFT_CHILD) );
    }
    printf( "inorder value = %d\n", (*n)->data );
    if( (*n)->RIGHT_CHILD != NULL ){
        traverse_inorder( &((*n)->RIGHT_CHILD) );
    }
    
}

int main(int argc, char **argv){
    int i;
    NODE *n = NULL;
    //n = malloc(sizeof(NODE));
    //n->data = 10;
    int  k[] = {5, 10, 2, 20, 1, 100, 3};
    //printf("Size of k = %lu",sizeof(k)/sizeof(int));

    for( i = 0; i < sizeof(k)/sizeof(int); i++ ){
        insert_data( &n, k[i] );
    }

    search_node( &n, 1 );
    traverse_inorder( &n );
    traverse_preorder( &n );
    traverse_postorder( &n );
    delete_node( &n, 1 );
    traverse_inorder( &n );
    traverse_preorder( &n );
    traverse_postorder( &n );
    return 0;
}
