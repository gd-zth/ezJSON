
# ezJSON
<font color=#999AAA >C语言下的人性化、高性能、轻量级JSON库

## 目录
* [License](#License)
* [使用](#使用)
  * [特性](#特性)
  * [编译](#编译)
  * [参数](#参数)
  * [示例](#构建和解析)
    * [基础结构](#基础结构)
    * [object对象](#object对象)
    * [array数组](#array数组)
  * [校验](#校验)
* [API](#API)
  * [构建相关](#构建相关)
  * [解析相关](#解析相关)
* [性能测试](#性能测试)
  * [测试内容](#测试内容)
  * [测试代码](#测试代码)
  * [结果](#结果)

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
### 特性
<font color=#999AAA >ezJSON 命名自单词 easy 的谐音，目标是实现以精简的代码实现对复杂数据的处理，包含了一个C文件和一个头文件，对于小容量 MCU 芯片具有良好的支持。其具备以下特性：
人性化，相同于Json协议的结构设计，代码简洁，可读性强；
高性能，超快的构建速度，支持查询式解析；
轻量级，接口的实现基于指针操作，执行不申请占用额外内存。

### 编译
<font color=#999AAA >由于整个库只有一个 C 文件和一个头文件，因此您只需将包含副本 __zJSON.c__ 和 __zJSON.h__ 的文件夹复制到项目源,并添加以下内容：
```
#include "ezJSON/ezJSON.h"
```

### 参数
<font color=#999AAA >ezJSON 支持以下几种数据类型：
| 类型 | 宏定义 | 变量类型 |
| :---- |  :----  | :---- |
 | 对象 | _ezJSON_OBJECT | - |
 | 数组 | _ezJSON_ARRAY| - | 
 | 字符串 | _ezJSON_STRING | char[] |
 | 数字 | _ezJSON_NUMBER | float |
 | 布尔 | _ezJSON_BOOL | int |
 | 空 | _ezJSON_NULL | NULL |

### 示例

#### 基本结构
<font color=#999AAA >构建数据请使用 `ezJSON()` 和 `双括号` 结尾，以下是一个标准的构建结构：
```
  ezJSON(jsonStr) 
  {
      STR("string", "this is a string"); 
      NUM("number", 23.64);    
      BOL("bool", 1);  
      NUL("null"); 
  }}
```
<font color=#999AAA >解析数据请使用 `_ezJSON()` 和 `}_END_}` 结尾，`errPtr` 为 _int_ 型变量的指针，以下是一个标准的解析结构：
```
  _ezJSON(errPtr, jsonStr) 
  {
      _VAL ("value", value);     // 字符、数字、布尔动态获取
      
  }_END_}
```

#### object对象
<font color=#999AAA >现有字符数组 `char string[1024];` 存储有Json字符串如下：
```
  {
      "title": "object test",

      "object_1": 
      {
          "string": "this is object_1 string",
          "number": 10.01,
          "bool": true,
        
          "object_2":
          {
              "string": "this is object_2 string",
              "number": 10.02,
              "bool": false
          }
      }
  }
```

<font color=#999AAA >用于存储数据的结构体如下：
```
  typedef struct DATASTRUCT
  {
      char    title[64];
      struct 
      {
          char    string[64];
          float   number;
          int     bool;
          struct
          {
              char    string[64];
              float   number;
              int     bool;
              
          }object2;
          
      }object1;
  
  } Data;
```

##### 构建代码（示例）：
```
  ezJSON(jsonStr)
  {
      STR("title", "object test");
      
      OBJ("object_1")
      {
          STR("string", "this is object_1 string");
          NUM("number", 10.01);
          BOL("bool", 1);
          
          OBJ("object_2")
          {
              STR("string", "this is object_2 string");
              NUM("number", 10.02);
              BOL("bool", 0);
          }}
      }}
  }}
```

##### 解析代码（示例）：
```
  _ezJSON(NULL, jsonStr)
  {
      _VAL("title", data.title);
      
      _OBJ("object_1")
      {
          _VAL("string", data.object1.string);
          _VAL("number", data.object1.number);
          _VAL("bool",   data.object1.bool);
    
          _OBJ("object_1")
          {
              _VAL("string", data.object1.object2.string);
              _VAL("number", data.object1.object2.number);
              _VAL("bool",   data.object1.object2.bool);
          }}
      }}

  }_END_}
```

#### array数组
<font color=#999AAA >现有字符数组 `char string[1024];` 存储有Json字符串如下：
```
  {
      "strings": ["one", "two", "three"],
      "numbers": [1, 2, 3],
      "objects": [
          {
              "string": "one",
              "number": 1
          },
          {
              "string": "two",
              "number": 2
          },
          {
              "string": "three",
              "number": 3
          }
      ],
      "arrays": [
          ["one", "two", "three"],
          [1, 2, 3]
      ]
  }
```

<font color=#999AAA >用于存储数据的结构体如下：
```
  typedef struct DATASTRUCT
  {
      char    strings[3][16];
      char    numbers[3][16];
      struct
      {
          char    string[16];
          float   number;

      }objects[3];
      struct
      {
          char    string[16];
          float   number[3];

      }arrays;

  }Data;
```

##### 构建代码（示例）：

<font color=#999AAA >_预设值 `size`，大于 __0__ 表示预设元素个数，使用 `_IDX` 标记元素索引，等于 __-1__ 表示不预设个数；键名 `key`，当键值作为数组元素时填 __NULL__；_

```
  char* string[3] = {"one", "two", "three"};
  float number[3] = {1, 2, 3};
```
```
  ezJSON(jsonStr)
  {
      // 使用索引
      ARR("strings", 3) { STR(NULL, string[_IDX]); }}

      // 不使用索引
      ARR("numbers", -1)
      {
          NUM(NULL, number[0]);
          NUM(NULL, number[1]);
          NUM(NULL, number[2]);
      }}

      ARR("objects", 3) {OBJ(NULL) 
      {
          STR("string", string[_IDX]);
          NUM("number", number[_IDX]);
      }}}}
        
      ARR("arrays", -1)
      {
          ARR(NULL, 3) { STR(NULL, string[_IDX]); }}
          ARR(NULL, 3) { NUM(NULL, number[_IDX]); }}
      }}
  }}
```

##### 解析代码（示例）：
```
  _ezJSON(NULL, jsonStr)
  {
      _ARR("strings") {_VAL(NULL, data.strings[_IDX]); }}
        
      _ARR("numbers") 
      {
          _VAL(NULL, data.numbers[_IDX]); 
      }}

      _ARR("objects") {_OBJ(NULL) {
          _VAL("string", data.objects[_IDX].string);
          _VAL("number", data.objects[_IDX].number);
      }}}}
        
      _ARR("arrays") {
          _ARR(NULL) {_VAL(NULL, data.arrays.string[_IDX]); }}
          _ARR(NULL) {_VAL(NULL, data.arrays.number[_IDX]); }}
      }}

  }_END_}
```

### 校验
#### 异常检测
<font color=#999AAA >__`常规检测`__ 由于ezJSON采用的是查询式解析，校验操作不会在入口函数 `_ezJSON(errPtr, jsonStr)` 的开头进行，而是在执行解析函数时同步执行数据的校验，并返回响应的错误码，码值 __小于0__ 表示数据异常。ezJSON 支持的异常类型有：
| 宏定义 | 对应值 | 含义 |
| :----: | :----: |  :----: |
| _ezJSON_ERR_NONE| 0 | 无 |
| _ezJSON_ERR_SYMBOL | -1 | 非法字符 |
| _ezJSON_ERR_NOTEXIST | -2 | 键不存在 |
| _ezJSON_ERR_FORMAT | -3 | 格式错误 |

以下是常规异常检测的示例代码：
```
  _ezJSON(NULL, jsonStr) // 参数`errPtr` 为 NULL
  {
      if (0 > _VAL("title", title))
      {
          printf("parse title error\n");
      }

      int errObj = _OBJ("object")
      {
          if (0 > errObj)
          {
              printf("parse object error\n");
          }
      }}

  }_END/_}
```

<font color=#999AAA >__`全局检测`__ 启用该检测方式时，当解析函数检测到异常，则自动结束解析项目，并将错误码赋值到 `errPtr` 指向的整数型变量。以下是全局检测的示例代码：
```
  int err;
  
  _ezJSON(&err, jsonStr) // 参数`errPtr` 不为 NULL
  {
      _VAL("title", title);
      printf("title: %s\n", title);

      _OBJ("object")
      {
          _VAL("string", string);
          printf("string: %s\n", string);
      }}

  }_END/_}

  if (0 > err)
      printf("error code %d !\n", err);
```

#### 类型检测
<font color=#999AAA >在执行解析动作前，可使用 `_TYPE()` 预先获取键值的类型。以下是类型检测的代码示例：
```
  _ezJSON(NULL, jsonStr)
  {
      switch(_TYPE("value"))
      {
      case ezJSON_NULL:     printf("this is a null\n");     break;
      case ezJSON_OBJECT:   printf("this is a object\n");   break;
      case ezJSON_ARRAY:    printf("this is a array\n");    break;
      case ezJSON_STRING:   printf("this is a string\n");   break;
      case ezJSON_NUMBER:   printf("this is a number\n");   break;
      case ezJSON_BOOL:     printf("this is a bool\n");     break;
      case ezJSON_ERR_NOTEXIST:
          printf("key not exist !\n");
          break;
      default:
          printf("parse err !\n");
      }

  }_END/_}
```

## API

### 构建相关
<font color=#999AAA >创建一个构建工程；内存指针 `string`；
> ezJSON( char* string ) {
> 
> }}

<font color=#999AAA >创建对象类型；键 `key`，为 __null__ 表示添加到数组；
> void OBJ( char* key ) {
>
> }}

<font color=#999AAA >创建数组类型；键 `key`，为 __null__ 表示添加到数组；元素个数 `size`，大于 __0__ 表示预设大小，__-1__ 表示不预设；
> void ARR( char* key , int size ) {
> 
> }}

<font color=#999AAA >创建数字类型；键 `key`，为 __null__ 表示添加到数组；键值 `value`，__float__ 类型；
> void NUM( char* key , float value ) ;

<font color=#999AAA >创建字符类型；键 `key`，为 __null__ 表示添加到数组；键值 `value`，__char *__类型；   
> void STR( char* key , char* value ) ;

<font color=#999AAA >创建布尔类型；键 `key`，为 __null__ 表示添加到数组；键值 `value`，__int__ 类型；
> void BOL(char *key, int value) ;

<font color=#999AAA >创建空类型；键 `key`，不能为 __null__；
> void NUL( char *key ) ;

### 解析相关
<font color=#999AAA >创建解析目标；全局错误码 `err`，为 __null__ 表示启用全局异常检测；目标指针 `string`；
> void _ezJSON( int* errPtr , char* string ) {
>
> }_END\_}

<font color=#999AAA >解析对象类型；键 `key`，为 __null__ 表示上级为数组，返回值为错误码；
> int _OBJ( char* key ) {
> 
> }}

<font color=#999AAA >解析数组类型；键 `key`，为 __null__ 表示上级为数组；返回值为错误码；
> int _ARR( char* key ) {
>
> }}

<font color=#999AAA >获取键值；键 `key`，为 __null__ 表示上级为数组；键值 `value`，动态获取数字、字符、布尔值；返回值 __小于0__ 时表示错误码，否则表示键值的类型；
> int _VAL( char* key , float \char *\int value ) ;

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
      struct  
      {
          char    name[16];
          float   age;
          float   grades[3];
          int     office;
          struct 
          {
              char   address[16];
              float  date;

          }exp[2];

      }student;
  
  }Info;
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
      
  }_END/_}
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
      
  }_END/_}
```

### 结果
<font color=#999AAA >五场测试执行一百万次循环用时（单位：ms）：

| 内容 \ 场| 1 | 2 | 3 | 4 | 5 |
| :----: | :----: | :----: | :----: | :----: | :----: |
| 构建全部 | 5385 | 5291 | 5388 |5430 | 5327 |
| 解析全部 | 10709 |10663 | 10807 |10740 | 10536 |
| 解析部分 | 5107 |5028 | 5040 |5172 | 5125 |
