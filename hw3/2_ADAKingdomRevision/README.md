### Question
能夠找到有 2 個士兵的情況，但是沒辦法找 > 2 。

Q: 
1. 用DFS隨機在一個點找離它最遠的 得到longest path的端點
2. 這個端點再做dfs 得到最長路徑
3. 如果有第三個士兵 要算從這條最長路徑開始 長出去的最長branch
會 TLE ....

A: 不能每次都把每棵樹都看過一次  

### Hint
* 用 dp 紀錄“最遠還可以走多遠“
* 找到一條路之後，從剩下的裡面找 dp 最大，就是答案。
* 過程中記錄下沒有被選到（比較小）的 branch。找到 longest path 之後，sort 這些備選 branch，依序 output，即為答案。 例如，備選 branch 有 {b1,b2,b3}，依照大小順序排列 b1 < b2 < b3，而最長 path 為 L，則答案為 0, L, L+b1, L+b1+b2, L+b1+b2+b3,... 
