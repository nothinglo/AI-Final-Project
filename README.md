# AI-Final-Project

Chinese version:

	目標: 數獨出題
	1. 使用者可自行選擇題目難易
	2. 自定義題目的 pattern (使用者可以指定題目出在哪些位置)
	3. 產生題目解答及解法（能越符合人類思考或者越容易理解）

	模式:
	1. 無限制時間
	2. 限制時間
	3. 多人共同遊戲（maybe 81x81)

English version:

	TBA.

Schedule:

	2015/05/12-2015/05/19:
		1. write code for solve sudoku
		2. more efficiency algorithm
		3. generate any level sudoku board
		4. reaserch problem for generate different level
		5. discuss what type board is easy or difficult
		6. simple visualize solve process
	
Events:
	
	[Milestone #2]: Finish at 2015/05/24 by Uglyman.nothinglo
					Has level 1 to 10 random board
					It can use by [./exe] [level:1~10]
					All level can be generated in 1 sec
					Level is judged by the number of spaces (first version)
	
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

Reference:

	1. [Sudoku Puzzles Generating: from Easy to Evil]:
		http://zhangroup.aporc.org/images/files/Paper_3485.pdf
	2. [Sudoku Generation and Difficulty Metrics]
		http://www.longwood.edu/assets/mathematics/Team2975_ProblemB.pdf
	3. [The Model and Algorithm to Estimate the Difficulty Levels of Sudoku Puzzles]
		http://www.ccsenet.org/journal/index.php/jmr/article/viewFile/3732/3336
	4. [A Retrievable Genetic Algorithm for Efficient Solving of Sudoku Puzzles]
		http://waset.org/publications/9998148/a-retrievable-genetic-algorithm-for-efficient-solving-of-sudoku-puzzles
