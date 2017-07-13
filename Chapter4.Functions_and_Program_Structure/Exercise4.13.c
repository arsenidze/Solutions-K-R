#include <stdio.h>
#include <string.h>

void reverse(char s[]);
	void helpreverse(int k, char s[]);

int main(void)
{
	char line[] = "computer";
	printf("%s\n", line);
	reverse(line);
	printf("%s\n", line);
	
	return 0;
}

void reverse(char s[])
{
	helpreverse(0,s);
}

void helpreverse(int k, char s[])
{
	if(k < strlen(s) - k - 1)
	{
		char temp = s[k];
		s[k] = s[strlen(s) - k - 1];
		s[strlen(s) - k - 1] = temp;
		helpreverse(k + 1, s);
	}
}
