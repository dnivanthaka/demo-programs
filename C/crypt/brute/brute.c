#include    <stdio.h>
#include    <stdlib.h>
#include    <memory.h>
#include    <crypt.h>

#define     _XOPEN_SOURCE
#define     MAX 62

char        num[MAX + 1];
int         n; 
char* perms = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ1234567890";
char* pwd_hash = NULL;

void matrixPermute (int), createCyclicMatrix (), rightRotate (int, int);
void get_user_selection(char*);
void show_usernames(char*);
void set_hash(char*, int);
void check_string(char *str);
void print_chars(char** p, int i);

main (int argc, char *argv[])
{
	get_user_selection( argv[1] );

}

void get_user_selection(char* file){
	int i, j;
 	n = 62;
	int sel = 0;

	//while(TRUE){
		show_usernames(file);
		printf("\n Your selection (0 = quit) : ");
		scanf("%d", &sel);
		if(sel == 0)
			exit(0);
		set_hash(file, sel);
		//printf("%s\n", pwd_hash);
		printf("\t---------- Starting brute force attack ---------");
		printf("\n");
		 for (n = 1; n <= 35; ++n){
	    		for (i = 3; i <= n; ++i){
            			num [i] = i;
	    		}
            		matrixPermute (n);
	    	}
	//}
}
//main user menu
void show_usernames(char* file){
	char line[256] = "";
	char *username, *passwd;
	int count = 0;

	FILE *fp = fopen(file, "r");

	if( fp != NULL ){
		printf("%s %20s %s\n", "id","Username","Password hash");
		printf("----------------------------------------\n");
		while( !feof(fp) && fgets(line, 256, fp) != NULL ){
			count++;
			//fputs( line, stdout );
			
			if(strlen(line) > 5){
				username = strtok( line, ":" );
				passwd = strtok( NULL, ":" );
				printf( "%2d ", count );
				if(strlen(username) > 0){
					printf( "%20s ", username );
					printf( "%s\n", passwd );
				}
			}
		}
	}
}
//setting password hash to be calculated
void set_hash(char* file, int sel){
	char line[256] = "";
	char *username, *passwd;
	int count = 0;

	FILE *fp = fopen(file, "r");

	if( fp != NULL ){
		while( !feof(fp) && fgets(line, 256, fp) != NULL ){
			count++;

			if(count == sel){
				username = strtok( line, ":" );
				pwd_hash = strtok( NULL, ":" );
				return;
			}
		}
	}
}

void matrixPermute (int k)
{
    int     i, temp;
    if  (k == 3) 
        {
        createCyclicMatrix ();
        return;
        }
    temp = k - 1;
    for (i = 0; i < temp ; ++i) 
        {
        rightRotate (1, temp);
        matrixPermute (temp);
        } 
}
//creating a cyclic matrix to get all the possilbe permutations
void createCyclicMatrix (){
    char    *p[MAX], temp[2*MAX];
    int     i, j;
    /* create the cyclic permutation matrix P as an array of pointers */ 
    memcpy (temp, num + 1, n);
    memcpy (temp + n , num + 1, n);
   
    for (i = 0; i < n; ++i)

	p[i] = &(perms[*(temp + n - i)]);
   
    /* generate the 2n permutations from the cyclic permutation matrix P */
    for (i = 0; i < n; ++i){
		print_chars(p, i);
        }
}
void rightRotate (int f, int l)
{
    char    temp [2*MAX], *saveptr;
    int     i;
    saveptr = num + f;
    memcpy (temp , saveptr, l);
    memcpy (temp + l, saveptr, l);
    memcpy (saveptr, temp + l - 1, l);
}

void print_chars(char** p, int i){
 int j;
char str[MAX + 1];
	strncpy(str, p[i], n-1);

	str[ n ] = '\0';
	check_string(str);

	strncpy(str, p[n], i);
	str[ i ] = '\0';
	check_string(str);
}

void check_string(char *str){
char* str2 = NULL;

	if( crypt(str, "$1$") == pwd_hash ){
		printf("------------- Match Found -------------");
		printf("Password is : %s\n", str);
		exit(0);
	}
}

