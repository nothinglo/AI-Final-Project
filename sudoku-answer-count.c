//
//  sudoku-answer-count.c
//  AI-Final-Project
//
//  Created by uglyman.nothinglo on 2012-04-03.
//  Copyright (c) 2012 year nothinglo. All rights reserved.
//

/*** solve problem ***/
/*** http://judge.nccucs.org/ShowProblem?problemid=d068 ***/
/*********************/

#include<stdio.h>

int boardCheck(int matrix[][9], int x, int y, int num){
	int i, j, time_1, time_2;

	for(i=0; i<9; i++) {
		if(matrix[x][i]==num || matrix[i][y]==num) return 0;
	}
	for(i=(x/3)*3, time_1=0; time_1<3; i++, time_1++) {
		for(j=(y/3)*3, time_2=0; time_2<3; j++, time_2++) {
			if(matrix[i][j]==num) return 0;
		}
	}
	return 1;
}

void findPlace(int matrix[][9], int* sum, int x, int y){
	int num;

	if(x==9) {
		y++;
		x = 0;
	}
	if(y==9) {
		++(*sum);
		return;
	}
	if(matrix[x][y] != 0) findPlace(matrix, sum, x+1, y);
	else {
		for(num=1; num<10; num++) {
			if(boardCheck(matrix, x, y, num)) {
				matrix[x][y] = num;
				findPlace(matrix, sum, x+1, y);
				matrix[x][y] = 0;
			}
		}
	}
}

int main(){
	int time, i, j, matrix[9][9], sum;

	scanf("%d",&time);
	while(time>0) {
		sum = 0;
		for(i=0; i<9; i++) {
			for(j=0; j<9; j++) {
				scanf("%d",&matrix[i][j]);
			}
		}
		findPlace(matrix, &sum, 0, 0);
		printf("%d\n", sum);
		time--;
	}
	return 0;
}
