#include <stdio.h>

#define swap(t,x,y) { \
						t temp = y; \
						y =  x;	\
						x = temp; \
					}
					
					
int main(void)
{
	char *s = "hello\n";
	char *t = "world\n";
	printf("s = %s\n", s);
	printf("t = %s\n", t);
	swap(char *,s,t);
	printf("s = %s\n", s);
	printf("t = %s\n", t);
}
