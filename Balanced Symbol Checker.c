#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define TRUE 1              // typical C boolean set-up  
#define FALSE 0
 
typedef struct StackStruck {      // Structure defining stack data structure.
    char *darr;
    int  top;
    int size;
} Stack;

void push( Stack *s , char ch, int DEBUG_MODE);             // All function declarations.
void pop(Stack *s, int DEBUG_MODE);
void grow(Stack *s, int DEBUG_MODE);
void init(Stack *s);
void reset(Stack *s);
char gettop (Stack* s);
int isEmpty (Stack* s);
int checkValid(char open , char close,Stack *s, int DEBUG_MODE);


 
int main(int argc, char *argv[]) 
{
 
  int DEBUG_MODE;                   

    for (int i=0;i<argc;i++)
    {
        if (argv[i][0]=='-'&&argv[i][1]=='d')
        {
	        DEBUG_MODE=TRUE;
        }

        else
        {
        DEBUG_MODE=FALSE; 
        }

    }

    Stack st1;
    
    init(&st1);                    // Function call to initalize stack.

    
	char input[300]; 
	
	printf ( "Type the '-d' to debug the program after the executable file in command line arguement\n\n");
	printf ( "Enter the expression: (q or Q to quit the program)\n");
	

	
    fgets (input,300,stdin);              // Standard userinput.
    
    
    if((strlen(input)-1)==1)
    {
    	if((input[0]=='q')|| (input[0]=='Q'))
    	{
		return 0;
		}	
	}
    
    char temp;
    int flag= 0;
    int i=0;
    
    for(i=0;i<strlen(input)-1;i++)      
    {
        if(input[i]=='{' || input[i]=='(' ||  input[i]=='[' || input[i]=='<' )
        {
        
        push(&st1,input[i],DEBUG_MODE);                  // Function called to push the character in stack.
        
        }
        
        else if (input[i]=='}' || input[i]==')' ||  input[i]==']' || input[i]=='>' )
        {
          temp= st1.darr[st1.top];
        
          flag= checkValid(temp,input[i],&st1,DEBUG_MODE);          // Function called to check for the closing symbol.
          
           if (flag!=0)
           {
        
                if(flag==1)
                 {
                    printf("Expression is imbalanced missing opening symbol."); 
                 } 
                else if(flag==2)
                 {
                    printf("Expression is imbalanced missing closing symbol.");   
                  }
            break;
           }
        
        }
    }
    
   
    
    if(st1.top == -1 && flag==0)
    {
         printf("Expression is balanced");  
    }
    else if(flag==0)
    {
        printf("Expression is imbalanced missing closing symbol.");    
    }
    
    reset(&st1);          // Function called to reset the stack.
    
    return 0;
}

void reset(Stack *s){                     //  Function to reset the stack so that it is ready to be used again.
   free(s->darr);
    s->size=2;
    s->top=-1;
    s-> darr=(char*)malloc(s->size*sizeof(char));
}

char gettop (Stack* s)                    // Function to access the top element of the stack.
{
  return (  s->darr[s->top] );
}


void init(Stack* s)                         // Function to initialize the stack. Note: Top index=-1.
{
    s->size=2;
    s->top=-1;
    s-> darr=(char*)malloc(s->size*sizeof(char));
    }


void push(Stack *s , char ch, int DEBUG_MODE)          // Function to push the character in stack.
{
 
    int size = s ->size ;
    int top = s->top;
    
    if(top==(size-1))
    {
    grow(s, DEBUG_MODE);                          // Function to grow the stack if the array size is full.
    }
    
    top++;
    
    s->darr[top] = ch ;
    
    if(DEBUG_MODE==TRUE)
    {
    printf("Value pushed : %c \n",ch);
    }
    
    s->top = top;
    
}

void grow(Stack *s, int DEBUG_MODE)              // Function to grow the dynamic array of larger size.
{
    char *temp;
    int old_size= s->size ;
    int new_size = old_size + 2;
    int count = 0;
    temp= (char*) malloc(new_size * sizeof(char));
    int i=0;
    
    for(i=0;i<=s->top;i++)
    {
        temp[i]= s->darr[i];
        count++;
    }
    
    if(DEBUG_MODE==1)
    {
        printf("Old Array Size  : %d \n",old_size); 
        printf("New Array Size : %d \n",new_size); 
        printf("No of values copied from old Array to New Array : %d \n",count); 
    }
    
    
    free(s->darr);
    
    s->darr=temp;
    s->size=new_size;
    
}


void pop(Stack *s, int DEBUG_MODE)            // Function to pop the top element in the stack and decrementing the top.
{
    char ch;
    int top = s->top ;
    
    if(!isEmpty(s))
    {
     ch = gettop(s);                         //s->darr[top];
     
    if(DEBUG_MODE==TRUE)
    {
    printf("Value popped : %c \n",ch);
    }
   
    s->top = s->top - 1; 
    
     
    }
    
    
}


int checkValid(char open , char close, Stack *s, int DEBUG_MODE )           /* Function to check the closing symbol with opening symbol.
                                                                             If closing symbol is encountered with the opening symbol, 
                                                                             is called. */
{
if((open=='{' && close=='}') ||  (open=='(' && close==')') || (open=='<' && close=='>') || (open=='[' && close==']'))
{
  pop(s,DEBUG_MODE);                      // Pop function is called as soon as opening and closing symbol matches.
  return 0;
}
else if(s->top==-1)
{
  return 1;
}
else
{
    return 2;
}
 
}


int isEmpty (Stack* s)         // Function to check if the stack is empty.
{
  if ( s->top == -1)
    return 1;
  else
    return 0;
}