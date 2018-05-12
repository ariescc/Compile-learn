#pragma once

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


