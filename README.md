# AI-Final-Project

Chinese version：

	目標: 數獨出題
	1. 可自行選擇題目難易
	2. 自定義題目的 pattern (使用者可以指定題目出在哪些位置)
	3. 產生題目解答及解法

	模式:
	1. 無限制時間
	2. 限制時間
	3. 多人共同遊戲（maybe 81x81)

	如何出唯一解題目（初步想法）:
	1. 隨機填入數字法出題
	2. 解出目前題目所有解
	3. 若剛好只有一個解則結束，否則填入數字至某個位置使得解變最少
	4. Go to 2.

English version:

	TBA.

Schedule:

	2015/05/12-2015/05/19:
		1. reaserch problem for generate different level
		2. write code for solve sudoku
		3. more efficiency algorithm
		4. discuss what type board is easy or difficult
		5. simple visualize solve process

Reference:

	1. [Sudoku Puzzles Generating: from Easy to Evil]:
		http://zhangroup.aporc.org/images/files/Paper_3485.pdf
	2. [Sudoku Generation and Difficulty Metrics]
		http://www.longwood.edu/assets/mathematics/Team2975_ProblemB.pdf
	3. [The Model and Algorithm to Estimate the Difficulty Levels of Sudoku Puzzles]
		http://www.ccsenet.org/journal/index.php/jmr/article/viewFile/3732/3336
	4. [A Retrievable Genetic Algorithm for Efficient Solving of Sudoku Puzzles]
		http://waset.org/publications/9998148/a-retrievable-genetic-algorithm-for-efficient-solving-of-sudoku-puzzles
