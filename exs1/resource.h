/**
==================================================================================================================================
头文件引入
==================================================================================================================================
*/

#include "relation.h"
#include "result.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>



/**
==================================================================================================================================
全局常量
==================================================================================================================================
*/

#define LETTER_NUM 26
#define DIGIT_NUM 10



/**
==================================================================================================================================
词法解析得到的单词类型定义
==================================================================================================================================
*/

#define ILLEGAL_STRING 1000
#define IDENTIFIER_STATEMACHINE 1001
#define DECIMAL_STATEMACHINE 1002
#define KEYWORDS_STATEMACHINE 1003
#define SYMBOLS_STATEMACHINE 1004

// 关键字定义
#define THREAD 10005
#define FEATURES 10006
#define FLOWS 10007
#define PROPERTIES 10008
#define END 10009
#define NONE 10010
#define IN 10011
#define OUT 10012
#define DATA 10013
#define PORT 10014
#define EVENT 10015
#define PARAMETER 10016
#define FLOW 10017
#define SOURCE 10018
#define SINK 10019
#define PATH 10020
#define CONSTANT 10021
#define ACCESS 10022

// 符号定义
#define EQUAL_GREATER 101
#define PLUS_EQUAL_GREATER 102
#define FEN 103
#define MAO 104
#define TWO_MAO 105
#define LEFT_HUA_KH 106
#define RIGHT_HUA_KH 107
#define MISE_GREARER 108

