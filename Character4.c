#include <stdio.h>

int strrindex(const char s[], const char t[]);
const char pattern[] = "w";

int main()
{
	int strrindex(const char [], const char []);
	char s[] = "reaeaaqweaba";
	printf("%s\n%s\n",s,pattern);
	printf("%d\n",strrindex(s,pattern));
}

int strrindex(const char s[], const char t[])
{
	int i,j,k,pos;
	pos = -1;
	for(i = 0; s[i] != '\0'; i++) {
		for(j = i, k = 0; s[j] == t[k] && t[k] != '\0'; j++, k++)
		;
		if(k > 0 && t[k] == '\0')
			pos = i, i += k - 1;
	}
	return pos;		
}
