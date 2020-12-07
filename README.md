
# ezJSON
<font color=#999AAA >C语言下的人性化、高性能、轻量级JSON库
<hr style=" border:solid; width:100px; height:1px;" color=#000000 size=1">

## 目录
* [License](#License)
* [特性](#特性)
* [使用](#使用)
* [API](#APIs)
* [性能测试](#性能测试)
* [参数](#参数与支持)

## License
MIT License
>  Copyright (c) 2020 zhoutianhao
>  
>  Permission is hereby granted, free of charge, to any person obtaining a copy
>  of this software and associated documentation files (the "Software"), to deal
>  in the Software without restriction, including without limitation the rights
>  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
>  copies of the Software, and to permit persons to whom the Software is
>  furnished to do so, subject to the following conditions:
>  
>  The above copyright notice and this permission notice shall be included in all
>  copies or substantial portions of the Software.
>  
>  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
>  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
>  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
>  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
>  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
>  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
>  SOFTWARE.

## 使用
### 前言
<font color=#999AAA >ezJSON 命名自单词 easy 的谐音，目标是实现以精简的代码实现对复杂数据的处理，包含了一个C文件和一个头文件，对于小容量 MCU 芯片具有良好的支持。库具备以下特性：
<font color=#999AAA >&#8194&#8194&#8194&#8194人性化，相同于Json协议的结构设计，代码简洁，可读性强；
<font color=#999AAA >&#8194&#8194&#8194&#8194高性能，超快的构建速度，支持查询式解析；
<font color=#999AAA >&#8194&#8194&#8194&#8194轻量级，静态库大小仅有1.7K，接口消耗内存极小。

### 编译
<font color=#999AAA >由于整个库只有一个 C 文件和一个头文件，因此您只需将包含副本 __zJSON.c__ 和 __zJSON.h__ 的文件夹复制到项目源,并添加以下内容：
```
#include <ezJSON/ezJSON.h>
```

## API

### 构建相关
<font color=#999AAA >创建构建目标；内存指针 `string`；
> void ezJSON( char* string ) ;

<font color=#999AAA >创建对象类型；键 `key`，为 __null__ 表示添加到数组；
> void OBJ( char* key ) ;  

<font color=#999AAA >创建数组类型；键 `key`，为 __null__ 表示添加到数组；元素个数 `size`，大于 __0__ 表示预设大小，__-1__ 表示不预设；
> void ARR( char* key , int size ) ;

<font color=#999AAA >创建数字类型；键 `key`，为 __null__ 表示添加到数组；键值 `value`，__float__ 类型；
> void NUM( char* key , float value ) ;

<font color=#999AAA >创建字符类型；键 `key`，为 __null__ 表示添加到数组；键值 `value`，__char *__类型；   
> void STR( char* key , char* value ) ;

<font color=#999AAA >创建布尔类型；键 `key`，为 __null__ 表示添加到数组；键值 `value`，__int__ 类型；
> void STR(char *key, int value) ;

<font color=#999AAA >创建空类型；键 `key`，不能为 __null__；
> void STR( char *key ) ;

### 解析相关
<font color=#999AAA >创建解析目标；全局错误码 `err`，可以为 __null__；目标指针 `string`；
> void _ezJSON( int* err , char* string ) ;

<font color=#999AAA >解析对象类型；返回错误码；键 `key`，为 __null__ 表示上级为数组；
> int _OBJ( char* key ) ;

<font color=#999AAA >解析数组类型；返回错误码；键 `key`，为 __null__ 表示上级为数组；
> int _ARR( char* key ) ;

<font color=#999AAA >解析数字、字符、布尔类型；返回错误码；键 `key`，为 __null__ 表示上级为数组；键值 `value`，可为三种类型，动态获取；
> int _ARR( char* key , float \char *\int value ) ;

<font color=#999AAA >获取键值类型；返回值大于 __0__ 表示 __类型码__，否则表示 __错误码__；键 `key`，为 __null__ 表示上级为数组；
> int _TYPE( char* key ) ;

## 性能测试
<font color=#999AAA >测试平台使用的是阿里云单核CPU、2G内存的服务器，搭载有64位Ubuntu18.04系统。对目标字符串进行一百万次循环的构建、全部解析和局部解析，分别使用两种库进行5次计时测试。

### 测试内容

> 目标字符串：
```
  {
      "school": "Guangdong University Of Petrochemical Technology",
      "location": "Maoming",
      "ranking": 505,
      "area": 2020.643,
      "student": {
          "name": "zhoutianhao",
          "age": 23,
          "grades": [
              97,
              62,
              84
          ],
          "office": true,
          "exp": [
              {
                  "address": "Guangdong",
                  "date": 1906
              },
              {
                  "address": "Chengdu",
                  "date": 1910
              }
          ]
      }
  }
```

> 目标结构体：
```
  typedef struct INFOSTRUCT 
  {
      char    school[64];
      char    location[16];
      float   ranking;
      float   area;
  
      struct {
          char    name[16];
          float   age;
          float   grades[3];
          int     office;
          
          struct {
              char    address[16];
              float   date;
              
          } exp[2];
          
      } student;

  } INFO, pINFO;
```

### 测试代码
> 使用ezJSON构建：
```
  ezJSON(string)
  {
      STR("school",   info.school);
      STR("location", info.location);
      NUM("ranking",  info.ranking);
      NUM("area",     info.area);
      OBJ("student")
      {
          STR("name", info.student.name);
          NUM("age",  info.student.age);
          ARR("grades", 3)
          {
              NUM(NULL, info.student.grades[_IDX]);
          }}
          BOL("office", info.student.office);
          ARR("exp", 2) {OBJ(NULL)
          {
              STR("address",  info.student.exp[_IDX].address);
              NUM("date",     info.student.exp[_IDX].date);
          }}}}
      }}
  }}
```

> 使用ezJSON解析全部：
```
  _ezJSON(NULL, string)
  {
      _VAL("school",   info.school);
      _VAL("location", info.location);
      _VAL("ranking",  info.ranking);
      _VAL("area",     info.area);
      _OBJ("student") 
      {
          _VAL("name", info.student.name);
          _VAL("age",  info.student.age);
          _ARR("grades")
          {
              _VAL(NULL, info.student.grades[_IDX]);
          }}
          _VAL("office", info.student.office);
          _ARR("exp") {_OBJ(NULL)
          {
              _VAL("address", info.student.exp[_IDX].address);
              _VAL("date",    info.student.exp[_IDX].date);
          }}}}
      }}
  }}
```

> 使用ezJSON解析局部：
```
  _ezJSON(NULL, string)
  {
      _OBJ("student") {_ARR("exp") {_OBJ(NULL)
          {
              _VAL("address", info.student.exp[_IDX].address);
              _VAL("date",    info.student.exp[_IDX].date);
          }}}}
      }}
  }}
```

### 结果
<font color=#999AAA >五场测试执行一百万次循环用时（单位：ms）：

| 内容 \ 场| 1 | 2 | 3 | 4 | 5 |
| :----: | :----: | :----: | :----: | :----: | :----: |
| 构建全部 | 5385 | 5291 | 5388 |5430 | 5327 |
| 解析全部 | 10709 |10663 | 10807 |10740 | 10536 |
| 解析部分 | 5107 |5028 | 5040 |5172 | 5125 |
  
## 参数与支持

### 文本类型

| 宏定义 | 对应值 | 键类型 | 符号 | 变量类型 |
| :----: | :----: |  :----: | :----: | :----: | 
| _ezJSON_OBJECT| 1 | 对象 | { } | - |
| _ezJSON_ARRAY | 2 | 数组 | [ ] | - | 
| _ezJSON_STRING | 3 | 字符串 | " " | char[] |
| _ezJSON_NUMBER | 4 | 数字 | 0~9, '.', '-'| float |
| _ezJSON_BOOL | 5 | 布尔 | false, ture | int |
| _ezJSON_NONE | 6 | 空 | null | NULL |

### 错误码

| 宏定义 | 对应值 | 含义 |
| :----: | :----: |  :----: |
| _ezJSON_ERR_NONE| 0 | 无 |
| _ezJSON_ERR_SYMBOL | -1 | 非法字符 |
| _ezJSON_ERR_NOTEXIST | -2 | 键不存在 |
| _ezJSON_ERR_FORMAT | -3 | 格式错误 |

