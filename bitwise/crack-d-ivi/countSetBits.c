/*
  Implementation of Brian Kernighan’s Algorithm:
   1  Initialize count: = 0
   2  If integer n is not zero
      (a) Do bitwise & with (n-1) and assign the value back to n
          n: = n & (n-1)
      (b) Increment count by 1
      (c) go to step 2
   3  Else return count
   Ref : http://www.geeksforgeeks.org/count-set-bits-in-an-integer/
 */
#include<stdio.h>

/* Function to get no of set bits in binary
   representation of passed binary no. */
int countSetBits(int n) {
  unsigned int count = 0;
  while (n) {
    n &= (n-1) ;
    count++;
  }
  return count;
}

int main() {
  int i = 9;

  printf("%d", countSetBits(i));

  return 0;
}
