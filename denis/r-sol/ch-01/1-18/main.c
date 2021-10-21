// WAP to remove trailing blanks and tabs from each line of input
// and to delete entirely blank lines.

#include <stdio.h>

#define MAXLINE 1000

int getLine (char [], int, FILE *);
int atRemove (char []);
void copy (char [], char[]);

int main () {
  
  int max;  /* max length seen so far*/
  char line[MAXLINE];  /* current input line */
  char longest[MAXLINE]; /* longest line save here */
  
  max = 0;  
  FILE *fr = NULL;
  FILE *fw = NULL;
  fr = fopen ("at.txt", "r");
  fw = fopen ("wt.txt", "w");
  if (fr == NULL || fw == NULL) {
    printf ("\nFile can't open !");
    exit (0);
  }
  
  while((getLine(line, MAXLINE,  fr)) > 0) {
    if (atRemove(line) > 0) {
      fputs(line, fw);
      printf ("\nLine = %s\n", line);
    }
  }
  // close file 
  fclose (fr);
  fclose (fw);
  return 0;
}

/* getLine : find the largest word's length. */
int getLine(char s[], int lim, FILE *fr) {
  int i,c;
 
  for (i=0; i<lim-1 && (c = getc(fr)) != EOF && c !='\n'; ++i )
    s[i] = c;
  if (c == '\n') {
    s[i] = c;
    ++i;
  } 
  s[i] = '\0';
   return i;
}

/* atRemove : remove trailing blanks and tabs from character string s*/
int atRemove (char s[]) {
  int i;
  i = 0;

  while (s[i] != '\n') /* Fine new line character */
    ++i;
  --i;                 /* Back off from '\n' */
  
  while (i >= 0 && (s[i] == ' ' || s[i] == '\t'))
    --i;
  if (i >= 0) {   /* Is it no blank line ? */
    ++i;
    s[i] = '\n'; /* Put newline character back */
    ++i;
    s[i] = '\0';  /* Terminate the string */
  }
  printf ("\nAT>>>>>>>>>>>> Line = %s", s);
  return i;
}

/*copy: copy  'from' content to 'to' */
void copy (char to[], char from[]) {
  int i;
  i = 0;
  while ( (to[i] = from[i]) != '\0' )
    i++;
} 


