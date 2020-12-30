
## Introduction

- `exampleForHelper.cpp`: show the way to use `helper.h`, which is given by the TA.
- `dlxSudoku.cpp`: using DLX and helper.h to solve a general Sudoku. (Empty board in the beginning, no need for input.)
- `main.cpp`: program to solve the main task of the homework -  the killer Sudoku.(color constraint given)


* Basic idea:  
|--------------|-----------------|---------------|-------------------|----------------|
  在哪一格填數字    在哪一列填了什麼    在哪一欄填了什麼  在哪個 block 填了什麼  在哪個顏色填了什麼

所有組合同時使用
(v)每個數字填了幾次/位置
(x)這個顏色填了哪一個數字 * c 個數字




* key words: Integer partition: https://www.geeksforgeeks.org/generate-unique-partitions-of-an-integer/  
https://stackoverflow.com/questions/14162798/generating-all-distinct-partitions-of-a-number  

## Reference
### Algorithm
* Exact cover problem: 

* Dancing Links (DLX)/ Algorithm X:  https://www.geeksforgeeks.org/exact-cover-problem-algorithm-x-set-2-implementation-dlx/?ref=rp
* DLX for Sudoku: https://www.cnblogs.com/grenet/p/3163550.html


### C++ notes
* char to ASCII: https://www.programiz.com/cpp-programming/examples/ASCII-value-character 