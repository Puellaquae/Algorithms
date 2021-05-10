# HDU6828 Little Rabbit's Equation

## 题目大意

给定一个加减乘除的算式，求在何进制（16进制以内）下算式成立。

## 解题过程

读入算式，从 2 进制到 16 进制各测试一遍。注意这道题需要使用 64 位整型。另外可以根据最大数字预先确定可能的最小进制。这道题数字与运算符号之间没有多余的空格，解析字符串不需要花太多的功夫。