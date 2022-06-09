# HDU 2300 Crashing Robots

## 题目大意

A × B 大小的空间内有 N 个机器人，会有 M 条指令依次来操作机器人。指令格式为 <机器人编号> <动作> <重复次数>。动作包括 L 左转 90 度，R 右转 90 度，F 前进 1 个单位。要求判断 M 指令内机器人是否会发生碰撞（和边界或其他机器人），若碰撞则输出第一条碰撞信息。

### 输入

共有 T 个测试数据，每个测试数据的格式：
```
A B
N M
[指令; M]
```

### 输出

根据结果输出一种

```
Robot i crashes into the wall
Robot i crashes into robot j
Ok
```

## 解题过程

依旧是按照题目要求，逐条指令模拟就可以了。