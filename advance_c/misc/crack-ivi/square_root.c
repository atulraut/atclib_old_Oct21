\***
	Updated: 26 August 2021
	Fair Oaks, CA, 95628
*\
#include<stdlib.h>
#include<stdio.h>

/* Simple one */
int floorSqrt__(int x) {
  // Base cases
  if (x == 0 || x == 1)
    return x;

  // Staring from 1, try all
  // numbers until i*i is
  // greater than or equal to x.
  int i = 1, result = 1;

  while (result <= x) {
    i++;
    result = i * i;
  }
  return i - 1;
}

/* Optimized one : */
// Returns floor of square root of x
int floorSqrt(int x) {
  // Base cases
  if (x == 0 || x == 1)
    return x;

  // Do Binary Search for floor(sqrt(x))
  int start = 1, end = x, ans;
  while (start <= end) {
    int mid = (start + end) / 2;

    // If x is a perfect square
    if (mid*mid == x)
      return mid;

    // Since we need floor, we update answer when mid*mid is
    // smaller than x, and move closer to sqrt(x)
    if (mid*mid < x) {
      start = mid + 1;
      ans = mid;
    } else // If mid*mid is greater than x
      end = mid - 1;
  }
  return ans;
}

int main() {
  int x = 36;
  printf ("\n out = %d \n", floorSqrt(x));
  return 0;
}

/***
    => ./a.out
    out = 6
*/
