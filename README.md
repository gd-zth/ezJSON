
# ezJSON
<font color=#999AAA >C语言下的人性化、高性能、轻量级JSON库
<hr style=" border:solid; width:100px; height:1px;" color=#000000 size=1">

## 目录
* [特性](#特性)
* [定义](#定义)
* [API](#API)
* [Demo](#Demo)
  * [构建](#构建)
  * [解析](#解析)
* [性能测试](#性能测试)
  * [内容](#内容)
  * [代码](#代码)
    * [构建](#构建)
    * [解析](#解析)
  * [结果](#结果)

## 特性

* 人性化：基于Json数据结构的设计，代码简洁，可读性强。
* 高性能：构建目标用时为主流JSON库的一半，对长数据局部解析具有良好的支持。
* 轻量级：程序基于指针操作，执行过程不申请占用额外的内存。

## 定义

### 键值类型

| 宏定义 | 对应值 | 键类型 | 变量类型 |
| :----: | :----: |  :----: | :----: | 
| _ezJSON_NONE | 0 | 异常 | - |
| _ezJSON_OBJECT| 1 | 对象 | - | 
| _ezJSON_ARRAY | 2 | 数组 | - | 
| _ezJSON_STRING | 3 | 字符串 | char[] |
| _ezJSON_NUMBER | 4 | 数字 | float | 
| _ezJSON_BOOL | 5 | 布尔 | int | 
| _ezJSON_NONE | 6 | 空 |  NULL | 

### 错误码

| 宏定义 | 对应值 | 含义 |
| :----: | :----: |  :----: |
| _ezJSON_ERR_NONE| 0 | 无 |
| _ezJSON_ERR_SYMBOL | -1 | 非法字符 |
| _ezJSON_ERR_NOTEXIST | -2 | 键不存在 |
| _ezJSON_ERR_FORMAT | -3 | 格式错误 |

## API

## Demo

### 构建

### 解析

## 性能测试
<font color=#999AAA >测试平台使用的是阿里云单核CPU、2G内存的服务器，搭载有64位Ubuntu18.04系统。为了更直观感受性能测试的结果，这里使用目前最主流的JSON库：cJSON 进行对比测试。

### 内容
<font color=#999AAA >对目标字符串进行一百万次循环的构建、全部解析和局部解析，分别使用两种库进行5次测试。

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

### 示例代码

#### 构建
> cJSON构建全部：
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

> ezJSON构建全部：
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
> cJSON解析全部：
```
  cJSON* cinfo = cJSON_Parse(string);

  sprintf(info.school, "%s", cJSON_GetObjectItem(cinfo, "school")->valuestring);
  sprintf(info.location, "%s", cJSON_GetObjectItem(cinfo, "location")->valuestring);
  info.ranking = cJSON_GetObjectItem(cinfo, "ranking")->valuedouble;
  info.area = cJSON_GetObjectItem(cinfo, "area")->valuedouble;

  cJSON* student = cJSON_GetObjectItem(cinfo, "student");
  sprintf(info.student.name, "%s", cJSON_GetObjectItem(student, "name")->valuestring);
  info.student.age = cJSON_GetObjectItem(student, "age")->valuedouble;
  
  cJSON *grades = cJSON_GetObjectItem(student, "grades");
  for (int idx; idx < cJSON_GetArraySize(grades); idx ++)
  {
      info.student.grades[idx] = cJSON_GetArrayItem(grades, idx)->valuedouble;
  }
  
  info.student.office = cJSON_GetObjectItem(student, "office")->valueint;

  cJSON *exp = cJSON_GetObjectItem(student, "exp");
  for (int idx; idx < cJSON_GetArraySize(exp); idx ++)
  {
      cJSON *expItem = cJSON_GetArrayItem(exp, idx);
      sprintf(info.student.exp[idx].address, "%s", cJSON_GetObjectItem(expItem, "address")->valuestring);
      info.student.exp[idx].date = cJSON_GetObjectItem(expItem, "date")->valuedouble;
  }
  
  cJSON_Delete(info);
```

> ezJSON解析全部：
```
  _ezJSON(err, string)
  {
      _VAL("school",   info.school);
      _VAL("location", info.location);
      _VAL("ranking",  info.ranking);
      _VAL("area",     info.area);

      _OBJ("student") 
      {
          _VAL("name",   info.student.name);
          _VAL("age",    info.student.age);
          
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

> cJSON解析局部：
```
  cJSON* cinfo = cJSON_Parse(string);
  cJSON* student = cJSON_GetObjectItem(cinfo, "student");

  cJSON *exp = cJSON_GetObjectItem(student, "exp");
  for (int idx; idx < cJSON_GetArraySize(exp); idx ++)
  {
      cJSON *expItem = cJSON_GetArrayItem(exp, idx);
      sprintf(info.student.exp[idx].address, "%s", cJSON_GetObjectItem(expItem, "address")->valuestring);
      info.student.exp[idx].date = cJSON_GetObjectItem(expItem, "date")->valuedouble;
  }
  
  cJSON_Delete(info);
```

> ezJSON解析局部：
```
  _ezJSON(err, string)
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

> 构建一百万次用时（ms）：

| 库 \ 次 | 1 | 2 | 3 | 4 | 5 |
| :----: | :----: | :----: | :----: | :----: | :----: |
| cJSON  | 10555 | 10568 | 10554 |10613 | 10721 |
| ezJSON | 5385 | 5291 | 5388 |5430 | 5327 |

> 解析全部一百万次用时（ms）：

| 库 \ 次 | 1 | 2 | 3 | 4 | 5 |
| :----: | :----: | :----: | :----: | :----: | :----: |
| cJSON  | 7153 | 6931 | 7649 | 7753 | 6904 |
| ezJSON | 10663 |10740 | 10807 |10709 | 10536 |

> 解析局部一百万次用时（ms）：

| 库 \ 次 | 1 | 2 | 3 | 4 | 5 |
| :----: | :----: | :----: | :----: | :----: | :----: |
| cJSON  | 6334 |6257 | 6330 |6044 | 6163 |
| ezJSON | 5107 |5028 | 5040 |5172 | 5125 |

# 二、使用步骤
## 1.引入库


<font color=#999AAA >代码如下（示例）：



```c
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import warnings
warnings.filterwarnings('ignore')
import  ssl
ssl._create_default_https_context = ssl._create_unverified_context
```

## 2.读入数据

<font color=#999AAA >代码如下（示例）：



```c
data = pd.read_csv(
    'https://labfile.oss.aliyuncs.com/courses/1283/adult.data.csv')
print(data.head())
```



<font color=#999AAA >该处使用的url网络请求的数据。

<hr style=" border:solid; width:100px; height:1px;" color=#000000 size=1">

# 总结
<font color=#999AAA >提示：这里对文章进行总结：
例如：以上就是今天要讲的内容，本文仅仅简单介绍了pandas的使用，而pandas提供了大量能使我们快速便捷地处理数据的函数和方法。
