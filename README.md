# AI-Final-Project

Chinese version:

	目標: 數獨出題
	1. 可以產生使用者指定難度的數獨題目
	2. 可以產生使用者指定 pattern 的數獨題目 (使用者可以指定有數字的部分出現在哪些位置)
	3. 可以產生 17 clues 的數獨題目越快越好

English version:

	1. Generate Sudoku puzzles with different difficulties.
	2. Generate user-specified-pattern Sudoku puzzle.
	3. Generate 17 clues Sudoku as soon as possible.

Final solution:

	1. Implement logical solver to mimic the way human solve Sudoku.
	   (Simple Elimination, Lone Ranger, Twins Elimination, Wild Guess)
	   Randomly generate Sudoku until it meets the difficulty that we want.
	2. Generate random complete Sudoku and keep the numbers in the pattern area.
	   For each remaining numbers, remove it and fill in candidate that can make current Sudoku easier
	   (maybe reduce solution counts).
	3. For 21 clues or more, local search is quick enough.
	   For 20 clues ~ 19 clues, remove 2 clues and insert 1 clues (Gradient Descent)
	   For 18 clues ~ 17 clues, remove 3 clues and insert 2 clues (Gradient Descent)

![Our Poster](https://github.com/nothinglo/AI-Final-Project/blob/master/Sudoku/Final-Image/Poster.jpg)

Reference:

	1. [Sudoku Puzzles Generating: from Easy to Evil]:
		http://zhangroup.aporc.org/images/files/Paper_3485.pdf
	2. [Sudoku Generation and Difficulty Metrics]
		http://www.longwood.edu/assets/mathematics/Team2975_ProblemB.pdf
	3. [The Model and Algorithm to Estimate the Difficulty Levels of Sudoku Puzzles]
		http://www.ccsenet.org/journal/index.php/jmr/article/viewFile/3732/3336
	4. [A Retrievable Genetic Algorithm for Efficient Solving of Sudoku Puzzles]
		http://waset.org/publications/9998148/a-retrievable-genetic-algorithm-for-efficient-solving-of-sudoku-puzzles
	5. [Programming Sudoku]
		see ch4 and ch5
		這本書裡面的解法會找出唯一可能數值的格子。像人的解法。
		http://tulips.ntu.edu.tw/search~S5*cht?/Xsudoku&searchscope=5&SORT=DZ/Xsudoku&searchscope=5&SORT=DZ&SUBKEY=sudoku/1%2C15%2C15%2CB/frameset&FF=Xsudoku&searchscope=5&SORT=DZ&3%2C3%2C
    	6. [Sudoku PHP]
	        The author has updated it to version 2.0
	        Our demo web page is the old version
	        Ours : http://www.csie.ntu.edu.tw/~r03922058/Sudoku/
	        SudokuPHP : https://github.com/msoftware/phpsudoku

	7. [There is no 16-Clue Sudoku: Solving the Sudoku Minimum Number of Clues Problem via Hitting Set Enumeration]
		High speed solver code
		http://www.math.uci.edu/~brusso/Sudoku16clue2013.pdf

================= 以下是專案進行中的產物 =================

Schedule:

	2015/05/12-2015/05/19:
		1. write code for solve sudoku
		2. more efficiency algorithm
		3. generate any level sudoku board
		4. reaserch problem for generate different level
		5. discuss what type board is easy or difficult
		6. simple visualize solve process
	
Events:
	
	[Milestone #2]: 
					"first version":
					Finish at 2015/05/24 by Uglyman.nothinglo
					Has level 1 to 10 random board
					It can use by [./exe] [level:1~10]
					All level can be generated in 1 sec
					Level is judged by the number of spaces
					
					method :
					while(not done) {
						generateSpaceBoard (not unique solution)
						gradientDescentToBoard (let unique)
					}

					"2-th version":
					level : 1 to 11 (All level can be generated in 1 sec)
					It can use by [./exe] [level:1~11] [-a]
					
					method :
					1. give a finished board
					2. disturb board
					3.
					while(space not enough) {
						let a board cell to space that can be unique solution.
					}
Problems:

	     (Resolved) [Milestone #2]: level 11 may can't be generated in 1 sec.
			(Resolved in 2-th version)
			
	     (Resolved) [Milestone #3]: How to generate blanks > 55 && <= 58 is difficult
			1. Use Random Walk generate until done or it can't remove any position
			2. If not done then generate new random filled board, goto 1.
			
	(Part Resolved) [Milestone #3]: How to generate blanks > 58 is very very difficult
	   version 1-th:
			1. Use Random Walk generate 58 blanks
			2. Choose C(81 - 58, 2) equal C(23, 2) to remove
			3. If one of blank can be assigned a gradient descent cell to ONE solution then done.
			   If need more blanks than goto 2. do similar things.
			4. If 3. not found that two position then goto 1.
	   version 2-th:
			1. Use Random Walk generate 58 blanks
			2. C(23, 2) one to blank, another to assigned a gradient descent cell to ONE solution then done.
			   If need more blanks than goto 2. do similar things.
			3. If 2. not found then goto 1.
	
		(?)	[Milestone #3]: How to quickly decide the board is no solution (will speed up algorithms)

		(?)	[Milestone #3]: How to quickly generate the board solution > 1 (may useful for gradient descent)
			
Project Plan:

	/*** Milestone #1 ***/
	第一個里程碑: 最基本的要求為出一個題目（不分難易）且電腦可以找到只有一組解答。
	
	Deliverable 1:
	name: 如何出唯一解題目 
	description: 數獨的題目，每個空格都只有唯一一個數字可填入
	detail: simple algorithm is
		1. 隨機填入數字法出題
		2. 解出目前題目所有解
		3. 若剛好只有一個解則結束，否則填入數字至某個位置使得解變最少
		4. Go to 2.
	
	Deliverable 2:
	name: 如何解數獨題目
	description: 將所有空格填入數字且符合數獨規則
	detail: simple algorithm is DFS
	
	/*** Milestone #2 ***/
	第二個里程碑: 最基本的要求為電腦任意出一個題目，可以透過計算得知其難度，進階的要求為使用者可以指定難度而電腦要出那個難度的題目。

	Deliverable 1:
	name: 計算數獨題目難度 
	description: 數獨的題目，根據空格多寡或者規則限制會有不同難度
	detail: simple algorithm is 若電腦很快就解出則簡單，反之則困難。

	Deliverable 2:
	name: 電腦出指定難度題目
	description: 使用者可以指定任何難度的數獨題目
	detail: simple algorithm is 根據第一個里程碑的出題法出題，根據第二個里程碑的判斷題目難易度來檢測，不停測試直到出的題目難度是使用者想要的。

    /*** Milestone #3 ***/
	第三個里程碑: 在合理時間內答到下面三個目標
		1. 使用者可以指定難度而電腦要出那個難度的題目。
		2. 使用者可以指定題目出的位置（any pattern）。
		3. 電腦可以產生符合人類思考的解法步驟。

	Deliverable 1:
	name: 合理時間內出題
	description: 若使用太慢的演算法則可能無法在 real time 時間完成
	detail:
		(1) 利用 knowledge base 的方法將搜尋空間減少
		(2) 實作部分關於這部分的研究論文提升效率

	Deliverable 2:
	name: 可指定 pattern 題目
	description: 使用者可以要求題目出的範圍在哪些位置上
	detail: 根據使用者指定範圍加上此限制至出題的演算法中

	Deliverable 3:
	name: 產生解法步驟
	description: 使用者可以輕鬆的了解此題目該如何解決
	detail: simple algorithm is 將電腦的解法 step-by-step show 給使用者看
