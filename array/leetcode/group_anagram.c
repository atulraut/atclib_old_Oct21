/***
    Medium: Group Anagrams

    Given an array of strings strs, group the anagrams together. You can
    return the answer in any order.

    An Anagram is a word or phrase formed by rearranging the letters of a differen
    word or phrase, typically using all the original letters exactly once.

    Input: strs = ["eat","tea","tan","ate","nat","bat"]
    Output: [["bat"],["nat","tan"],["ate","eat","tea"]]

    Input: strs = [""]
    Output: [[""]]

    Input: strs = ["a"]
    Output: [["a"]]

    Constraints:

    1 <= strs.length <= 104
    0 <= strs[i].length <= 100
    strs[i] consists of lower-case English letters.

    https://leetcode.com/problems/group-anagrams/
    Date: 27 April 2021
    San Diego, CA.
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


#include <stdio.h>
#include <stdlib.h>

void calculate_hash(char *a, int l, int r) {
  char privot = a[l];
  int i, j;
  char temp;
  j = l;
  if (l < r) {
    for (i = l; i <= r; i++) {
      if (a[i] < privot) {
	temp = a[j];
	a[j] = a[i];
	a[i] = a[j + 1];
	a[j + 1] = temp;
	j++;
      }
    }
    calculate_hash(a, l, j - 1);
    calculate_hash(a, j + 1, r);
  }
}

void quicksort(char** strs, char** hash, int l, int r) {
  char* privot;
  privot = hash[l];
  char* temp;
  int i, j;
  j = l;
  if (l < r) {
    for (i = l; i <= r; i++) {
      if (0 > strcmp(hash[i], privot)) {
	temp = hash[j];
	hash[j] = hash[i];
	hash[i] = hash[j + 1];
	hash[j + 1] = temp;
	temp = strs[j];
	strs[j] = strs[i];
	strs[i] = strs[j + 1];
	strs[j + 1] = temp;
	j++;
      }
    }
    quicksort(strs, hash, l, j - 1);
    quicksort(strs, hash, j + 1, r);
  }
}

char* hash(char* str) {
  char* result;
  int length;
  int i;
  length = strlen(str);
  result = (char*)malloc((length + 1) * sizeof(char));
  for (i = 0; i < length; i++) {
    result[i] = str[i];
  }
  result[length] = '\0';
  calculate_hash(result, 0, length - 1);
  return result;
}

char*** groupAnagrams(char** strs, int strsSize, int** columnSizes, int* returnSize) {
  int i;
  char** hash_value;
  char*** result;
  if (0 == strsSize) {
    return NULL;
  }
  *returnSize = 0;
  result = (char***)malloc(sizeof(char**));
  result[0] = (char**)malloc(sizeof(char*));
  *columnSizes = (int*)malloc(sizeof(int));
  hash_value = (char**)malloc(strsSize * sizeof(char*));
  for (i = 0; i < strsSize; i++) {
    hash_value[i] = hash(strs[i]);
  }
  quicksort(strs, hash_value, 0, strsSize - 1);

  for(int i=0; i<6; i++) {
    printf ("strs--> %s \n", strs[i]);
  }

  result[0][0] = strs[0];
  (*columnSizes)[0] = 1;
  for (i = 1; i < strsSize; i++) {
    if (0 != strcmp(hash_value[i], hash_value[i - 1])) {
      *returnSize += 1;
      result = realloc(result, (*returnSize + 1) * sizeof(char**));
      result[*returnSize] = (char**)malloc(sizeof(char*));
      *columnSizes = realloc(*columnSizes, (*returnSize + 1) * sizeof(int));
      (*columnSizes)[*returnSize] = 0;
    }
    (*columnSizes)[*returnSize] += 1;
    result[*returnSize] = realloc(result[*returnSize], ((*columnSizes)[*returnSize] + 1) * sizeof(char*));
    result[*returnSize][(*columnSizes)[*returnSize] - 1] = strs[i];
  }
  *returnSize += 1;
  return result;
}

int main() {
  char *arr[] = {"eat", "tea", "tan", "ate", "nat", "bat"};
  int sz = 5;
  int retsz;
  int *retCsz;
  char ***op;
  op = groupAnagrams(arr, sz, &retsz, &retCsz);
  for(int i=0; i<retsz; i++) {
    printf ("--> %s \n", op[i]);
  }
  printf("Hello World");
  return 0;
}
