#include <stdio.h>
#include <stdlib.h> /* for atof() - in K&R, math.h is referenced - this is an anachronism */
#include <math.h>

#include <math.h>
#include <string.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define FUNCTION 1
#define VARIABLE 2

int getop(char []);
void push(double);
double pop(void);

void printtop(void);
void duplicatetop(void);
void swaptop2(void);			/*Swap the top two elemnts*/
void clearstck(void);			/*Clear the stack*/

int isinteger(double n);
double vars[256]; /*index of array corespond a variable and 
					value by this index equal to a value of this variable
				   */

void applyfunction(const char[]);


/* reverse Polish calculator */

int main(void)
{
	for(int i = 0; i < 256;i ++)
	{
		vars[i] = NAN;			/*if a value by index is NAN then variable correspond this
								 index do not use yet
								*/
	}
	
	
	int type;
  	double op1,op2;
  	char s[MAXOP];
	
	int flag = 0;
	int lastvar = 0;

	while((type = getop(s)) != EOF)
	{
		switch(type)
	    {
	    	case NUMBER:
	        	push(atof(s));
	        	flag = 0;
	        	break;
	      	case '+':
	        	push(pop() + pop());
	        	flag = 0;
	        	break;
	      	case '*':
	        	push(pop() * pop());
	        	flag = 0;
		        break;
	 	    case '-':
	        	op2 = pop();
	        	push(pop() - op2);
	        	flag = 0;
	        	break;
	      	case '/':
	        	op2 = pop();
	        	if(op2 != 0.0)
	        		push(pop() / op2);
	        	else
	          		printf("error: zero divisor\n");
	          	flag = 0;
	        	break;
			case '%':
				op2 = pop();
				if(op2 == 0.0)
				{
					printf("error: division by zero\n");
				}
				else if(isinteger(op1 = pop()) && isinteger(op2))
				{
					push((int)op1 % (int)op2);
				}
				else
				{
					printf("error: binary opertaion %% only for integers\n");
				}
				flag = 0;
				break;
			case FUNCTION:
				applyfunction(s);
				break;
			case VARIABLE:
				lastvar = s[0];
				if(!isnan(vars[lastvar]))
					push(vars[lastvar]);
				break;
			case '=':
				if(isnan(vars[lastvar]))
					vars[lastvar] = pop();
				else
				{
					vars[lastvar] = pop();
					pop();
				}
				break;
	      	case '\n':
	      		if(flag == 0)
	        		printf("\t%.8g\n", pop());
	        	flag = 0;
	        	break;
	      	default:
	        	printf("error: unknown command %s\n", s);
	        	break;
	    }
  }

  return 0;
}

void applyfunction(const char s[])
{
	double op2;
   
   if(     !strcmp(s, "sin"))
      push(sin(pop()));
   else if(!strcmp(s, "cos"))
      push(cos(pop()));
   else if(!strcmp(s, "exp"))
      push(exp(pop()));
   else if(!strcmp(s, "pow"))
   {
      op2 = pop();
      push(pow(pop(), op2));
   }
   else
      printf("%s is not a supported function.\n", s);
}

int isinteger(double n)
{
	return (int)n == n;
}

#define MAXVAL  100 /* maximum depth of val stack */

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f)
{
  if(sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
  if(sp > 0)
    return val[--sp];
  else
  {
    printf("error: stack empty\n");
    return 0.0;
  }
}

#include <ctype.h>

/* getop: get next operator or numeric operand */
int getop(char s[])
{
	static int c = -1;	
	int i = 0;
	while((s[i] = (c = (c == -1) ? getchar() : c))  == ' ' || c == '\t')
		c = getchar();
	
	if(isalpha(c))
	{
		while(isalpha(s[++i] = c = getchar()))
			;
		s[i] = '\0';
		if(strlen(s) == 1)
			return VARIABLE;
		return FUNCTION;
	}
	
	if(!isdigit(c) && c != '.' && c != '-')
	{
		int temp = c;
		c = -1;
		return temp;
	}
	
	if(c == '-')
	{
		if(!isdigit(s[++i] = c = getchar()) && c != '.')
		{
			return '-';
		}
	}
	
	if(isdigit(c))
		while(isdigit(s[++i] = c = getchar()))
			;
	if(c == '.')
		while(isdigit(s[++i] = c = getchar()))
			;
	
  	s[i] = '\0';
  	return NUMBER;
}

