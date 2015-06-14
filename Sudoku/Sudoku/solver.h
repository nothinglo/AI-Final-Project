/* modified version for solving "Sudoku X", "Sudoku X"-modifications 
made by Bo Haglund */ 
/* speed-optimized version of a 
simple and short sudoku-solver based on an exact-cover-problem-solver 
put into public domain by Guenter Stertenbrink,sterten@aol.com 
compiles well with GCC3.2 
some explanations are at : http://magictour.free.fr/suexco.txt 
a not speed-optimized DOS/Windows-executable with more features 
and attached source-code is at http://magictour.free.fr/suexk.exe 
Report errors,bugs,improvement suggestions,feedback to sterten@aol.com 
there are other programs here which are ~5 times faster, but 
they are not public domain and presumably more complicated ;-) 
This algo only searches for "naked single" and "hidden single" 
I'm not 100% sure, whether this version works correctly with 
the M1-array and rows-deletion before start 
*/ 
 
#ifndef Sudoku_solver_h
#define Sudoku_solver_h

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <memory.h>
#include <string.h>

#define N 3 // change this for larger sudokus , N=4 for 16*16 etc. 
#define N2 N*N 
#define N4 N2*N2 

static int Rows[ 5 * N4 + 1 ];
static int Row[ 5 * N4 + 1 ][ N2 + 1 ];
static int Cols[ N2 * N4 + 1 ];
static int Col[ N2 * N4 + 1 ][ 6 + 1 ];
static int Ur[ N2 * N4 + 1];
static int Uc[ 5 * N4 + 1 ];
static int V[ 5 * N4 + 1 ];
static int C[ N4 + 1 ];
static int I[ N4 + 1 ];

static int A[N2 + 1][N2 + 1];
static int Node[N4 + 1], M1[N4*N2];
static int nn = N4*N2;
static int mm = 4 * N4 + 2 * N2;
static int diagVers = 2;  /* Normal Suduko diagVers=0, Sudoku X diagVers=1, Disjoint Groups = 2 */
static char L[66] = ".123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz#*~";
// char L[66] is needed here for some compilers 

static bool g_bIsSudokuX = false;
static bool g_bIsSudokuDG = false;

int solveSudoku(const int board[N2][N2], bool all = false, bool count = false, bool th = false, int thres = 0);

#endif