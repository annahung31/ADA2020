### Question
和 Graph 有什麼關係？ or 屬於 amortized analysis

不可以開 N*Q


存活時間 * 人數
每一種人在這張圖上的貢獻面積

O(1) 把這坨人的高度, 寬度 算出來 


關係：
數量：


array 中有幾個 style，紀錄這個 style 上一次被改變（插入, 童話)的時間點
下一個時間點 - 上一個時間點，

沒有更動就放著，有更動把上一坨沒更動的 ++ ，重新計算。


先從 sample input 2 寫， front 跟 back 只是顛倒而已
-> debug 方法：生一個 sample input 2  改成 front ，結果應該要相同。

