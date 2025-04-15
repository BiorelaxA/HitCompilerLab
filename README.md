<!--
 * @Author: Peter/peterluck2021@163.com
 * @Date: 2025-04-15 00:32:32
 * @LastEditors: Peter/peterluck2021@163.com
 * @LastEditTime: 2025-04-15 15:44:37
 * @FilePath: /Lab/README.md
 * @Description: readme file
 * 
 * Copyright (c) 2025 by peterluck2021@163.com, All Rights Reserved. 
-->
# HitCompilerLab
这里是哈工大编译原理实验，参考来自南京大学编译原理实验



# Usage
如果您需要验证结果，只需要执行Makefile中的指令即可，例如
如果您要编译Lab1,Lab2的结果，则只需要输入
```bash
make lab1
```
之后您可以在根目录看到可执行文件

在2025年4月加入lab3分支，鉴于lab2已经和lab1使用交叉编译混在一起了，索性不搭建分支了，使用lab3您只需要如下操作即可编译lab3
```bash
git checkout lab3
```

## 已经完全通过lab1,lab2,lab3的所有必做测试案例
需要说明的是，本项目暂时只通过了所有必做测例，如果您需要通过extra测试案例，需要继续优化本项目。

## 项目调试
为了方便项目调试，在/.vscode/launch.json中修改可执行路径即可调试对应的test测试案例,之后F5即可
```json
   "args": ["${workspaceFolder}/test/Lab3_test/test2.cmm","-g"], 
```
## 关于项目

**本项目使用flex+bison格式进行词法和语法分析，并使用自底向上规约（S属性文法）的方式进行语义分析，在最后使用自底向上方式产生中间代码，并通过自顶向下方式打印出来** 

在根目录下的method.txt记录了本人在编写项目时的一些思路，如果您有兴趣，可以参考，可能会对您了解本项目有帮助。

建议您在使用本项目前，参考/file中的指导书，如果您有任何疑问或者发现任何错误欢迎与我联系peterluck2023@163.com

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
│  ├─ 编译原理实验指导书-词法分析与语法分析.pdf
│  └─ （新）实验三Web版虚拟机使用说明.pdf
├─ include
│  ├─ CmmparserTypes.h
│  ├─ HashTable.h
│  ├─ SemanticInfo.h
│  ├─ TreeNode.h
│  └─ error.h
├─ lab1.c
├─ lab2
├─ lab2.c
├─ lab3
├─ lab3.c
├─ lex.yy.c
├─ method.txt
├─ scanner
├─ src
│  ├─ HashTable.c
│  ├─ Intercode.c
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