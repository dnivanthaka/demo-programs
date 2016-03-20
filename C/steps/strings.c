/*
 * strings.c
 *
 * A program that illustrates strings in C. Designed for C99, but
 * should run fine on C90 with a lot of warnings.
 */

#include <stdio.h>
#include <string.h>
#include <wchar.h>

char s1[] = { 'd', 'o', 'g', (char)0 };
char s2[] = { 'd', 'o', 'g', '\0' };
char* s3 = "dog";
wchar_t* s4 = L"dog";

char* s5 = "c\xe9ili";
char* s6 = "c\u00e9ili";
char* s7 = "c\U000000e9ili";
wchar_t* s8 = L"c\U000000e9ili";

char* s9 = "k\u014dpa`a";
wchar_t* s10 = L"k\u014dpa`a";

void inspectString(char* s){
	int i, n;
	printf( "[%s] length=%d codepoints=[ ", s, (int)strlen(s) );
	for(i=0, n = strlen(s)+1;i<n;i++){
		printf( "%02x ", (unsigned char)s[i] );
	}
	printf(" ]\n");
}

void inspectWideString(wchar_t* s){
	int i, n;

	printf("[%ls] length=%d codepoints=[ ", s, (int)wcslen(s));
	for(i=0, n = (wcslen(s)+1) * sizeof(wchar_t);i < n; i++){
		printf("%02x ", ((unsigned char *)s)[i]);
	}

	printf( " ]\n" );
}

int main(){
	inspectString(s1);
	inspectString(s2);
	inspectString(s3);
	inspectString((char*)s4);
	inspectWideString(s4);

	return 0;
}
