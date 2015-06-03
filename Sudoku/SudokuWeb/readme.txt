### If you want to run the demo ###

1. Make sure the command line can accept "-php" parameter
    e.g. sudoku-generator 10 -php
    e.g. sudoku-generator 10 -a -php
    
   When adding -php parameter, the output format should be :
    a. a line containing 81 numbers segmented by semi-colon
    b. unknown number should be zero
    e.g. 1;2;3;4;5;6;7;8;9;0;2;3;5.........
    
2. Compile the source code
3. Create a folder in server
    For CSIE server : ~/htdocs/your_folder
    For CMLAB server : ~/public-html/your_folder
    
4. Put files to the folder in step 3.
    (index.php sudoku.css sudoku.js)

5. Move executable program generated in step 1. to the folder in step 3.
    (Make sure the program name should be "sudoku-generator")

6. Open the link and play