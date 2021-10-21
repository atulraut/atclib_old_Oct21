/***
    Q. What's the difference between memcpy and memmove? [Ref: http://c-faq.com/ansi/memmove.html]
    A: memmove offers guaranteed behavior if the memory regions pointed to by the source and
    destination arguments overlap. memcpy makes no such guarantee, and may therefore be
    more efficiently implementable. When in doubt, it's safer to use memmove.
    It seems simple enough to implement memmove; the overlap guarantee apparently
    requires only an additional test:
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

/**
 * memmove - Copy one area of memory to another
 * @dest: Where to copy to
 * @src: Where to copy from
 * @count: The size of the area.
 *
 * Unlike memcpy(), memmove() copes with overlapping areas.
 * https://elixir.bootlin.com/linux/latest/source/lib/string.c#L99L
 */
void *memmove_linux(void *dest, const void *src, size_t count) {
  char *tmp;
  const char *s;

  if (dest <= src) {
    tmp = dest;
    s = src;
    while (count--)
      *tmp++ = *s++;
  } else {
    tmp = dest;
    tmp += count;
    s = src;
    s += count;
    while (count--)
      *--tmp = *--s;
  }
  return dest;
}

/**
   Ref: http://www.danielvik.com/2010/02/fast-memcpy-in-c.html
**/
void* mymemcpy(void* dest, const void* src, size_t count) {
  char* dst8 = (char*)dest;
  char* src8 = (char*)src;
  //printf ("InSide mymemcpy:: src = %s, cnt = %d \n", src, count);
  while (count--) {
    *dst8++ = *src8++;
  }
  //printf ("InSide mymemcpy:: dest = %s \n", dest);
  return dest;
}

/**
   Ref: http://c-faq.com/ansi/memmove.html
**/
void *mymemmove(void *dest, void const *src, size_t n) {
  register char *dp = dest;
  register char const *sp = src;
  if(dp < sp) {
    while(n-- > 0)
      *dp++ = *sp++;
  } else {
    dp += n;
    sp += n;
    while(n-- > 0)
      *--dp = *--sp;
  }

  return dest;
}

int main(int argc, char* argv[]) {
  char *p1, *p2;
  char *p3, *p4;
  int size;

  /*  CASE 1 : From (SRC) < To (DEST) * From To  */

  p1 = (char *) malloc(12);
  memset(p1,12,'\0');
  size=10;
  strcpy(p1,"Atul Raut");
  p2 = p1 + 2;
  printf("\nFrom (before-p1) = [%s]",p1);
  printf("\nTo   (before-p2) = [%s]",p2);
  mymemmove(p2,p1,size); /*O/p: To   (after-p2)  = [Atul Raut] */
  // or try below
  //memcpy(p2,p1,size); /*O/p: To   (after-p2)  = [Atul Rauau]*/
  printf("\nFrom (after-p1)  = [%s]",p1);
  printf("\nTo   (after-p2)  = [%s]",p2);
  printf("\n--------------------------------");

  /* CASE 2 : From (SRC) > To (DEST) To From */

  p3 = (char *) malloc(12);
  memset(p3,12,'\0');
  p4 = p3 + 2;
  strcpy(p4, "Atul Raut");
  printf("\nFrom (before-p4) = [%s]",p4);
  printf("\nTo (atul before-p3)   = [%s]",p3);
  mymemmove(p3, p4, size);
  printf("\nFrom (after-p4)  = [%s]",p4);
  printf("\nTo (after-p3)    = [%s]",p3);

  /* CASE 3 : No overlap */

  p1 = (char *) malloc(30);
  memset(p1,30,'\0');
  size=10;
  strcpy(p1,"Amit Rauo");
  p2 = p1 + 15;
  printf("\n--------------------------------");
  printf("\nFrom (before-p1) = [%s]",p1);
  printf("\nTo (before-p2)   = [%s]",p2);
  mymemmove(p2,p1,size);
  printf("\nFrom (after-p1)  = [%s]",p1);
  printf("\nTo (after-p2)    = [%s]",p2);
  printf("\n--------------------------------\n");
  printf("\n\n");
  return 0;
}

/**
   => ./a.out

   From (before-p1) = [Atul Raut]
   To   (before-p2) = [ul Raut]
   From (after-p1)  = [AtAtul Raut]
   To   (after-p2)  = [Atul Raut]
   --------------------------------
   From (before-p4) = [Atul Raut]
   To (atul before-p3)   = []
   From (after-p4)  = [ul Raut]
   To (after-p3)    = [Atul Raut]
   --------------------------------
   From (before-p1) = [Amit Rauo]
   To (before-p2)   = []
   From (after-p1)  = [Amit Rauo]
   To (after-p2)    = [Amit Rauo]
   --------------------------------
**/
