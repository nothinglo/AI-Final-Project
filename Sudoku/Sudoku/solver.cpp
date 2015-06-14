//
//  solver.cpp
//  Sudoku
//
//  Created by uglyman.nothinglo on 2015/6/14.
//  Copyright (c) 2015年 nothinglo. All rights reserved.
//

#include "solver.h"

void InitSolver();

int solveSudoku(const int board[N2][N2], bool all, bool count, bool th, int thres)
{
    int i, j, k, l, m0, m1, r, p, r1, c, c1, c2, x, y, s, minimum, clues, nodes;
    
    p = 1;
    if (count) p = 0;
    if (all) p = 2;
    
    clock();
    
    for(x=1;x<=N2;x++)
        for(y=1;y<=N2;y++)
            A[x][y]=board[x-1][y-1];
    
    InitSolver();
    
    for (i = 1; i <= nn; i++)
        Ur[i] = 0;
    for (i = 1; i <= mm; i++)
        Uc[i] = 0;
    for (i = 1; i <= N4; i++)
        Node[i] = 0;
    
    clues = 0;
    
    for (x = 1; x <= N2; x++)
        for (y = 1; y <= N2; y++)
            if (A[x][y])
            {
                clues++; r = x*N4 - N4 + y*N2 - N2 + A[x][y];
                for (j = 1; j <= Cols[r]; j++)
                {
                    c1 = Col[r][j]; if (Uc[c1])
                    {
                        //printf("No solution exists.\n");
                        goto m6;
                    }
                    
                    Uc[c1]++;
                    
                    for (k = 1; k <= 9; k++)
                    {
                        Ur[Row[c1][k]]++;
                    }
                }
            }
    
    for (c = 1; c <= mm; c++)
    {
        V[c] = 0; for (i = 1; i <= 9; i++)if (Ur[Row[c][i]] == 0)
        {
            V[c]++; x = Row[c][i]; Row[c][i] = Row[c][V[c]]; Row[c][V[c]] = x;
        }
        Rows[c] = V[c];
    }
    
    m1 = 0;
    
    for (c = 1; c <= mm; c++)
        if (V[c]<2 && Uc[c] == 0)
        {
            m1++; M1[m1] = c;
        }
    
    i = clues; m0 = 0; nodes = 0;
    
m2:
    i++;
    I[i] = 0;
    minimum = nn + 1;
    if (i>N4 || m0)
        goto m4;
    
m22:
    if (m1 == 0)
        goto m21;
    
    if (Uc[M1[m1]] == 0 && V[M1[m1]] == 1)
    {
        C[i] = M1[m1]; m1--; goto m3;
    }
    m1--;
    goto m22;
    
m21:
    if (nodes & 1)
        for (c = 1; c <= mm; c++)
        {
            if (!Uc[c])if (V[c]<minimum)
            {
                minimum = V[c]; C[i] = c;
            }
        }
    if (!(nodes & 1))
        for (c = mm; c >= 1; c--)
        {
            if (!Uc[c])if (V[c]<minimum)
            {
                minimum = V[c]; C[i] = c;
            }
        }
    
    //I don't like this very much. Better let c start at random position
    if (minimum == 0 || minimum>nn)
        goto m4;
    
m3:
    c = C[i]; I[i]++;
    
    if (I[i]>Rows[c])
        goto m4;
    
    r = Row[c][I[i]];
    
    if (Ur[r])
        goto m3;
    
    m0 = 0;
    
    if (p)
    {
        k = N4; j = N2; x = (r - 1) / k + 1; y = ((r - 1) % k) / j + 1; s = (r - 1) % j + 1; A[x][y] = s;
        if (i == N4)
        {
            for (x = 1; x <= N2; x++)
                for (y = 1; y <= N2; y++)
                    printf("%c", L[A[x][y]]);
            printf("\n");
            if (p == 1)
                goto m6;
        }
    }
    
    for (j = 1; j <= Cols[r]; j++)
    {
        c1 = Col[r][j]; Uc[c1]++;
    }
    for (j = 1; j <= Cols[r]; j++)
    {
        c1 = Col[r][j];
        for (k = 1; k <= Rows[c1]; k++)
        {
            r1 = Row[c1][k]; Ur[r1]++;
            
            if (Ur[r1] == 1)
                for (l = 1; l <= Cols[r1]; l++)
                {
                    c2 = Col[r1][l]; V[c2]--;
                    if (Uc[c2] + V[c2] < 1)
                        m0 = c2; 
                    if (Uc[c2] == 0 && V[c2] < 2)
                    { 
                        m1++; 
                        M1[m1] = c2; 
                    }
                }
        }
    }
    
    nodes++;
    
    if (th && Node[N4] == thres)
    {
        return Node[N4];
    }
    
    Node[i]++; 
    goto m2;
    
m4:
    i--; 
    c = C[i]; 
    r = Row[c][I[i]]; 
    if (i == clues)
    { 
        if (p == 0)
            return Node[N4];
    }
    for (j = 1; j <= Cols[r]; j++)
    {
        c1 = Col[r][j]; Uc[c1]--;
        for (k = 1; k <= Rows[c1]; k++)
        {
            r1 = Row[c1][k]; Ur[r1]--;
            if (Ur[r1] == 0)
                for (l = 1; l <= Cols[r1]; l++)
                { 
                    c2 = Col[r1][l]; V[c2]++; 
                }
        }
    }
    goto m3;
    
m6:
    return -1;
}


#define ZeroMemory( array ) memset( (array), 0, sizeof( array ) );

void InitSolver()
{
    /* Here starts initialization code. This code only needs to be executed the first time
     that the solver is called. If the solver then is repeatedly called, the initialization
     code can be lifted out and placed in a separate routine.*/
    
    mm = 4 * N4;
    if (g_bIsSudokuX)
        mm += 2 * N2;
    else if (g_bIsSudokuDG)
        mm += N4;
    
    int r = 0;
    for (int x = 1; x <= N2; x++)
        for (int y = 1; y <= N2; y++)
            for (int s = 1; s <= N2; s++)
            {
                r++;
                Cols[r] = 4;
                Col[r][1] = x*N2 - N2 + y;
                Col[r][2] = (N*((x - 1) / N) + (y - 1) / N)*N2 + s + N4;
                Col[r][3] = x*N2 - N2 + s + N4 * 2;
                Col[r][4] = y*N2 - N2 + s + N4 * 3;
                
                /* Following is additional code for adding columns for "Sudoku X" */
                if (g_bIsSudokuX)
                {
                    if (x == y)
                    {
                        Col[r][5] = s + N4 * 4;
                        if (x == (1 + N2 - y))
                        {
                            Cols[r] = 6;
                            Col[r][6] = s + N2 + N4 * 4;
                        }
                        else
                            Cols[r] = 5;
                    }
                    else if (x == (1 + N2 - y))
                    {
                        Cols[r] = 5;
                        Col[r][5] = s + N2 + N4 * 4;
                    }
                }
                else if (g_bIsSudokuDG)
                {
                    Cols[r] = 5;
                    Col[r][5] = ((x - 1) % 3 + 3 * ((y - 1) % 3))*N2 + s + N4 * 4;
                }
            }
    
    ZeroMemory(Rows);
    for (r = 1; r <= nn; r++)
        for (int c = 1; c <= Cols[r]; c++)
        {
            int x = Col[r][c];
            Rows[x]++;
            Row[x][Rows[x]] = r;
        }
    /* Here ends the initialization code. */
}