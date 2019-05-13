#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // Rewrote this function
    // Return a random character using the ASCII values from 32 - 127
    char rChar = ((rand() % 95) + 32);     
    
    // return the random character    
    return rChar;

}

char *inputString()
{
    // Rewrote this function
    // allocate memory for the character array (string)
    char* iString = (char*) calloc(6, sizeof(char));
    int i;
    for (i = 0; i < 5; i++){
	// randomly assign ASCII values from 97 - 117 (a-u) 
        int j = ((rand() % 20) + 97);
        char c = (char) j;
        iString[i] = c;
    }

    // NULL at end of string
    iString[5] = '\0';
    
    // Return final build of string
    char *fString = iString;
    // printf("final string: %s", fString);
    
    return fString;

}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();

    // print statements to confirm I was accessing the string correctly
    // printf("String returned: %s ", s);
    // printf("String character 0: %c ", s[0]);
    // printf("char 3: %c ", s[3]);

    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}

