#include <cstdlib>
#include <cstdio>

#include <vector>

struct obj {
    int x;
    int y;
};

std::vector<obj *> collection;

void 
print_collection()
{
    for(int i=0;i<collection.size();i++){
        printf("x = %d\n", collection[i]->x);
    }
}

void 
set_collection()
{
    for(int i= collection.size() - 1;i>0;i--){
        collection[i]->x = collection[i - 1]->x;
        printf("x = %d\n", collection[i]->x);
    }
}

int
main(int argc, char *argv[])
{
    struct obj *tmp;

    for(int i=0;i<5;i++){
        tmp = new struct obj();
        tmp->x = 5;
        tmp->y = 10;

        collection.push_back( tmp );    
    }

    set_collection();
    //print_collection();
    
    return 0;
}
