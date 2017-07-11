#include <stdio.h>
#include <string.h>

void mstrcpy(char *s, char *t);
void mstrcat(char *s, char *t);
int mstrend(char *s, char *t);

int main(void)
{
	char s[] = "bol`woi kotik";
	char w[] = "test";
	char t[] = "kotichekgawgawgaw";
	printf("s = %s\n", s);
	printf("t = %s\n", t);
	printf("mstrend(s, t) = %d\n",mstrend(s, t));
	printf("s = %s\n", s);
	printf("t = %s\n", t);
}

void mstrcpy(char *s, char *t)
{
	while((*s++ = *t++) != '\0')
	;
}

void mstrcat(char *s, char *t)
{
	while(*s++)
		;
	s--;
	while(*s++ = *t++)
		;
}

int mstrend(char *s, char *t)
{
	int lendiff = strlen(s) - strlen(t);
	if(lendiff < 0)
		return 0;
	s += lendiff;
	while(*s++ == *t++)
	if(*(s - 1) == '\0')
		return 1;
	return 0;
}
