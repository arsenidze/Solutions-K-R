#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAXLINES 5000       /* maximum number of lines */
#define MAXLEN   1000       /* maximum length of a line */
char *lineptr[MAXLINES];
char lines[MAXLINES][MAXLEN];

int getline(char s[], int lim)
{
  int c, i;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    s[i] = c;                                                         
  if (c == '\n') {
    s[i++] = c;   
  }
  s[i] = '\0';
  return i;
}

int readlines(char *lineptr[], int maxlines)
{
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while ((len = getline(line, MAXLEN)) > 0)
    if (nlines >= maxlines || (p = malloc(len)) == NULL)
      return -1;
    else {
      line[len - 1] = '\0';  /* delete the '\n' */
      strcpy(p, line);
      lineptr[nlines++] = p;
    }                       
  return nlines;  
}

int readlines2(char lines[][MAXLEN], int maxlines)
{
  int len, nlines;
  nlines = 0;
  while ((len = getline(lines[nlines], MAXLEN)) > 0)
    if (nlines >= maxlines)                         
      return -1;           
    else
      lines[nlines++][len - 1] = '\0';  /* delete the '\n' */
  return nlines;
}

void writelines(char *lineptr[], int nlines)
{
	while(nlines-- > 0)
	{
		printf("%s\n", *lineptr++);
	}
}
/* Compare the length of strings */
int cmplstr(const void *t1, const void *t2)
{
	char *v1 = *(char**)t1;
	char *v2 = *(char**)t2;
	
	int len1 = strlen(v1);
	int len2 = strlen(v2);
	if(len1 > len2)
		return 1;
	else if(len1 < len2)
		return -1;
	else 
		return 0;
}

int main(int argc, char *argv[])
{
		
	int nlines;
	if((nlines = readlines(lineptr, MAXLINES)) > 0)
	{
		qsort(lineptr, nlines, sizeof(char*), cmplstr);
		writelines(lineptr, nlines);
		return 0;
	}
	else
	{
		printf("error: a lot of strings\n");
		return 1;
	}
}
