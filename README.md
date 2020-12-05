
# ezJSON
<font color=#999AAA >C语言下的人性化、高性能、轻量级JSON库
<hr style=" border:solid; width:100px; height:1px;" color=#000000 size=1">

## 目录
* [特性](#特性)
* [参数](#参数)
  * [文本类型](#文本类型)
  * [错误码](#错误码)
* [API](#APIs)
  * [构建](#构建相关)
  * [解析](#解析相关)
  * [增删改](#增删改)
* [Demo](#Demo)
  * [内容](#内容)
  * [代码](#代码)
    * [构建](#构建)
    * [解析](#解析)
* [性能测试](#性能测试)
  * [内容](#测试内容)
  * [结果](#结果)

## 特性

* 人性化：基于Json数据结构的设计，代码简洁，可读性强。
* 高性能：构建目标用时为主流JSON库的一半，对长数据局部解析具有良好的支持。
* 轻量级：程序基于指针操作，执行过程不申请占用额外的内存。

## 参数

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

### 增删改
<font color=#999AAA >内测中..

## Demo

### 内容
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

### 代码

#### 构建
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

#### 解析
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



### 性能测试
<font color=#999AAA >测试平台使用的是阿里云单核CPU、2G内存的服务器，搭载有64位Ubuntu18.04系统，这里加入目前最主流的C语言库“cJSON” 进行对比测试。

#### 测试内容
<font color=#999AAA >对 __Demo__ 中的目标字符串进行一百万次循环的构建、全部解析和局部解析，分别使用两种库进行5次计时测试。

#### cJSON测试代码
> 构建：
```
  cJSON *cinfo = cJSON_CreateObject();

  cJSON_AddStringToObject(cinfo, "school", info.school);
  cJSON_AddStringToObject(cinfo, "location", info.location);
  cJSON_AddNumberToObject(cinfo, "ranking", info.ranking);
  cJSON_AddNumberToObject(cinfo, "area", info.area);

  cJSON *student = cJSON_CreateObject();
  cJSON_AddStringToObject(student, "name", info.student.name);
  cJSON_AddNumberToObject(student, "age", info.student.age);

  cJSON *grades = cJSON_CreateFloatArray(info.student.grades, 3);
  cJSON_AddItemToObject(student, "grades", grades);
    
  cJSON_AddBoolToObject(student, "office", info.student.office);

  cJSON *exp = cJSON_CreateArray();
  for (int idx = 0; idx <2 ; idx ++) 
  {
      cJSON *expItem = cJSON_CreateObject();
      cJSON_AddStringToObject(expItem, "address", info.student.exp[idx].address);
      cJSON_AddNumberToObject(expItem, "date", info.student.exp[idx].date);
      cJSON_AddItemToArray(exp, expItem);
  }
  cJSON_AddItemToObject(student, "exp", exp);

  cJSON_AddItemToObject(cinfo, "student", student);

  char *_string = cJSON_PrintUnformatted(info);
  strcpy(string, _string);

  cJSON_free(_string);
  cJSON_Delete(info);
```

> 解析全部：
```
  cJSON* cinfo = cJSON_Parse(string);

  strcpy(info.school, cJSON_GetObjectItem(cinfo, "school")->valuestring);
  strcpy(info.location, cJSON_GetObjectItem(cinfo, "location")->valuestring);
  info.ranking = cJSON_GetObjectItem(cinfo, "ranking")->valuedouble;
  info.area = cJSON_GetObjectItem(cinfo, "area")->valuedouble;

  cJSON* student = cJSON_GetObjectItem(cinfo, "student");

  strcpy(info.student.name, cJSON_GetObjectItem(student, "name")->valuestring);
  info.student.age = cJSON_GetObjectItem(student, "age")->valuedouble;
  cJSON *grades = cJSON_GetObjectItem(student, "grades");
  for (int idx = 0; idx < cJSON_GetArraySize(grades); idx ++)
  {
      info.student.grades[idx] = cJSON_GetArrayItem(grades, idx)->valuedouble;
  }

  info.student.office = cJSON_GetObjectItem(student, "office")->valueint;

  cJSON *exp = cJSON_GetObjectItem(student, "exp");
  cJSON *expItem  = exp->child;
  for (int idx = 0; expItem != NULL; idx ++)
  {
      strcpy(info.student.exp[idx].address, cJSON_GetObjectItem(expItem, "address")->valuestring;
      info.student.exp[idx].date = cJSON_GetObjectItem(expItem, "date")->valuedouble;
      expItem  = expItem->next;
  }

  cJSON_Delete(cinfo);
```

> 解析局部：
```
  cJSON* cinfo = cJSON_Parse(string);

  strcpy(info.school, cJSON_GetObjectItem(cinfo, "school")->valuestring);
  cJSON* student = cJSON_GetObjectItem(cinfo, "student");

  cJSON *exp = cJSON_GetObjectItem(student, "exp");
  cJSON *expItem  = exp->child;
  for (int idx = 0; expItem != NULL; idx ++)
  {
      strcpy(info.student.exp[idx].address, cJSON_GetObjectItem(expItem, "address")->valuestring;
      info.student.exp[idx].date = cJSON_GetObjectItem(expItem, "date")->valuedouble;
      expItem  = expItem->next;
  }

  cJSON_Delete(cinfo);
```

#### 结果
<font color=#999AAA >执行构建代码用时（ms）：
| 库 \ 次 | 1 | 2 | 3 | 4 | 5 |
| :----: | :----: | :----: | :----: | :----: | :----: |
| cJSON  | 10555 | 10568 | 10554 |10613 | 10721 |
| ezJSON | 5385 | 5291 | 5388 |5430 | 5327 |

<font color=#999AAA >执行全部解析代码用时（ms）：
| 库 \ 次 | 1 | 2 | 3 | 4 | 5 |
| :----: | :----: | :----: | :----: | :----: | :----: |	
| cJSON  | 7153 | 6931 | 7649 | 7753 | 6904 |
| ezJSON | 10709 |10663 | 10807 |10740 | 10536 |

<font color=#999AAA >构建局部解析代码用时（ms）：
| 库 \ 次 | 1 | 2 | 3 | 4 | 5 |
| :----: | :----: | :----: | :----: | :----: | :----: |
| cJSON  | 6334 | 6257 | 6330 | 6044 | 6163 |
| ezJSON | 5107 |5028 | 5040 |5172 | 5125 |
