# Header_Fighter

>*Header_Fighter*是一款双人对战棋类游戏，规则如下：

**棋盘**：偶数大小的棋盘。棋盘上至少有1棋子属于红方、蓝方。通常情况下棋盘上红蓝方棋子数量相同。

**玩家**：两人，扮演红、蓝双方。

## 游戏规则：

1. 双方轮流下子，可以且仅可以下载己方所有的任意格子上。下子的结果是该格上的数字加一，并对该格子进入步骤二。

2. 系统会对指定格子进入「爆炸判定」，该判定将判定该格是否处于「过热状态」，若处于过热状态，则会进入步骤三。

3. 指定格子爆炸：本格的棋子减少相当于自己「爆炸上限」的棋子数，并使得其四联通格子各增加一，并使得其四联通格子的颜色变为该格的颜色，并且对周围格子进入步骤二。

## 胜利条件：

- 传统模式：一方拥有所有格子，则取得胜利。

- 低温模式: 当全局温度达到某一设定值时，占格多的胜利。


## 注：

### 爆炸上限：
  
> **爆炸上线是一组预设值，其根据设定的不同有所变化，传统模式下爆炸上限满足以下规则**：
>   - 角：2
>   - 边：3
>   - 中心：4
