/***
 * LeetCode : Surrounded Regions
 * Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.
 * A region is captured by flipping all 'O's into 'X's in that surrounded region.
 * Example:
 * X X X X
 * X O O X
 * X X O X
 * X O X X
 * After running your function, the board should be:
 * X X X X
 * X X X X
 * X X X X
 * X O X X
 * Explanation:
 * Surrounded regions shouldn’t be on the border, which means that any 'O' on the border of the
 * board are not flipped to 'X'. Any 'O' that is not on the border and it is not connected to
 * an 'O' on the border will be flipped to 'X'. Two cells are connected if they are adjacent
 *  cells connected horizontally or vertically.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/***
 *              (x-1, y)
 *                  |
 *                  |
 * (x, y-1) ------------------ (x, y+1)
 *                  |
 *                  |
 *              (x+1, y)
 */


void mark_current_island(int (*grid)[5], int x, int y, int row, int col) {
  if (grid[x][y] == 1)
    printf ("row = %d col=%d\n", x, y);

  /* Check bondry condition, such that we cant go beyond array bondry. */
  if (x < 0 || x >= row || y <= 0 || grid[x][y] != 1)
    return;
  if ( (row == 0 && y == 0) || (row == 1 && y ==0))
    printf ("row = %d \n", row);
  grid[x][y] = 2;

  /* Make recursive call in all 4 adjacent directories. */
  mark_current_island(grid, x+1, y, row, col); /* DOWN  */
  mark_current_island(grid, x, y+1, row, col); /* RIGHT */
  mark_current_island(grid, x-1, y, row, col); /* TOP   */
  mark_current_island(grid, x, y-1, row, col); /* LEFT  */
}

int numIslands(int  (*grid)[5], int gridSize, int* gridColSize) {
  int i, j, rows;
  int no_of_islands = 0;
  rows = gridSize;

  /* Emptry grid */
  if(*gridColSize == 0)
    return 0;

  /* Iterate for all cells of the array */
  for (i=0; i<4; i++) {
    for (j=0; j<5; j++) {
      if (grid[i][j] == 1) {
	//	printf ("row = %d col=%d\n", i, j);
	mark_current_island(grid, i, j, 4, 5);
	no_of_islands += 1;
      }
    }
  }
  printf ("[%s] no_of_islands = %d \n", __func__, no_of_islands );
  return no_of_islands;
}

int main () {
  int i, j;
  int gridSize;
  int gridColSize;

  int grid[][5] =  {
    {1, 1, 1, 1, 0},
    {1, 1, 0, 1, 0},
    {1 ,1 ,0, 0, 0},
    {0, 0, 0, 0, 0},
  };

  gridSize = 4;
  gridColSize = 5;

  int no_of_islands =  numIslands(grid, gridSize, &gridColSize);
  printf ("Output-> %d \n", no_of_islands);
  for (i=0; i<4; i++) {
    for (j=0; j<5; j++) {
      printf (" |%d| \t", grid[i][j]);
    }
    printf ("\n");
  }

  return 0;
}
