#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define PASSWD_PATH "/etc/passwd"
#define SHADOW_PATH "/etc/shadow"

int main(int argc, char** argv){
	int word_list_present = 0;
	char *line = "dinusha:x:1000:1000:Dinusha Nivanthaka Amerasinghe,,,:/home/dinusha:/bin/bash";

	if( argc > 1 ){
		//printf("Args passed!!!");
		word_list_present = 1;
	}

	printf("%s\n", line);

	//show_users_list();
	parse_line(line);

	return 0;
}

int show_users_list(){
	int fp = open(PASSWD_PATH, O_RDONLY);
	char buff[255];
	int ret = 0;
	
	if( fp == -1 ){
		printf("Error occured while trying to read 'passwd' file");
		return -1;
	}

	while( (ret = read(fp, buff, 255)) != 0 ){
		printf("%s", buff);
	}
}

int parse_line(){
	char *username, *passwd;
	char *line = "dinusha:x:1000:1000:Dinusha Nivanthaka Amerasinghe,,,:/home/dinusha:/bin/bash";

	username = strtok( (*line), ":" );
	passwd = strtok( NULL, ":" );

	//printf("%d\n", line[0]);
	printf( "%s\n", username );
	printf( "%s\n", passwd );
}
