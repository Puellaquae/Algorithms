# HDU6144 Arithmetic of Bomb

## 题目大意

"(12)#(2)4(2)#(3)" 将会被展开为 "12124222"，其中 # 号称为 Bomb，这种被称为 Bomb Number。给定一个这样的数，将其展开，结果对 1 000 000 007 取模。

## 解题过程

在对数进行展开，展开的中间结果还是用字符串保存，因为数字巨大。最后将字符串转换成数字，取模也同时在这一步进行。