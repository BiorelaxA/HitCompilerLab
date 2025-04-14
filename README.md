# HitCompilerLab
这里是哈工大编译原理实验，参考来自南京大学编译原理实验

# Usage
如果您需要验证结果，只需要执行Makefile中的指令即可，例如
如果您要编译Lab1的结果，则只需要输入
```bash
make lab1
```
之后您可以在根目录看到可执行文件
在2025年4月加入lab3分支，鉴于lab2已经和lab1使用交叉编译混在一起了，索性不搭建分支了，使用lab3您只需要如下操作即可编译lab3
```bash
git checkout lab3
```

## 暂时只有lab1,lab2的结果

# File Struct
文件结构如下：
```
Lab
├─ Cmmlexer.l
├─ LICENSE
├─ Makefile
├─ README.md
├─ file
│  ├─ Appendix_A.pdf
│  ├─ 实验教程-Project_1.pdf
│  ├─ 实验教程-Project_3.pdf
│  ├─ 实验教程_Project_2.pdf
│  ├─ 编译原理实验指导书-中间代码生成.pdf
│  └─ 编译原理实验指导书-词法分析与语法分析.pdf
├─ include
│  ├─ CmmparserTypes.h
│  ├─ HashTable.h
│  ├─ SemanticInfo.h
│  ├─ TreeNode.h
│  └─ error.h
├─ lab1.c
├─ lab2
├─ lab2.c
├─ lex.yy.c
├─ method.txt
├─ scanner
├─ src
│  ├─ HashTable.c
│  ├─ SemanticInfo.c
│  ├─ Stack.c
│  ├─ TreeNodes.c
│  └─ error.c
├─ syntax.output
├─ syntax.tab.c
├─ syntax.tab.h
├─ syntax.y
└─ test
   ├─ Lab1_test
   │  ├─ output
   │  │  ├─ test1.cmm
   │  │  ├─ test10.cmm
   │  │  ├─ test11.cmm
   │  │  ├─ test12.cmm
   │  │  ├─ test13.cmm
   │  │  ├─ test14.cmm
   │  │  ├─ test15.cmm
   │  │  ├─ test16.cmm
   │  │  ├─ test17.cmm
   │  │  ├─ test2.cmm
   │  │  ├─ test3.cmm
   │  │  ├─ test4.cmm
   │  │  ├─ test5.cmm
   │  │  ├─ test6.cmm
   │  │  ├─ test7.cmm
   │  │  ├─ test8.cmm
   │  │  └─ test9.cmm
   │  ├─ test1.cmm
   │  ├─ test2.cmm
   │  ├─ test3.cmm
   │  └─ test4.cmm
   ├─ Lab2_test
   │  ├─ test1.cmm
   │  ├─ test10.cmm
   │  ├─ test11.cmm
   │  ├─ test12.cmm
   │  ├─ test13.cmm
   │  ├─ test14.cmm
   │  ├─ test15.cmm
   │  ├─ test16.cmm
   │  ├─ test17.cmm
   │  ├─ test2.cmm
   │  ├─ test3.cmm
   │  ├─ test4.cmm
   │  ├─ test5.cmm
   │  ├─ test6.cmm
   │  ├─ test7.cmm
   │  ├─ test8.cmm
   │  └─ test9.cmm
   └─ Lab3_test
      ├─ extra1.cmm
      ├─ extra2.cmm
      ├─ test1.cmm
      └─ test2.cmm

```