
## ezJSON
<font color=#999AAA >C语言下的人性化、高性能、轻量级JSON库
<hr style=" border:solid; width:100px; height:1px;" color=#000000 size=1">

## 一、对比测试
<font color=#999AAA >这里以目前在C语言下最主流的JSON库：cJSON 为例，从代码阅读性、构建与解析速度、运行内存进行比较。

### 测试内容
> <font color=#999AAA >目标字符串：
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

> <font color=#999AAA >目标结构体：
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

### 通过cJSON构建
> 代码如下（示例）：
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

  strcpy(string, cJSON_PrintUnformatted(info));

  cJSON_Delete(cinfo);
```

### 通过ezJSON构建
> 代码如下（示例）：
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

### 通过cJSON解析
> 代码如下（示例）：
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

### 通过ezJSON解析
> 代码如下（示例）：
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
          _VAL("office", info.student.office);
          _ARR("grades")
          {
              _VAL(NULL, info.student.grades[_IDX]);
          }}
          _ARR("exp") {_OBJ(NULL)
          {
              _VAL("address", info.student.exp[_IDX].address);
              _VAL("date",    info.student.exp[_IDX].date);
          }}}}
      }}
  }}
```


<font color=#999AAA >示例：pandas 是基于NumPy 的一种工具，该工具是为了解决数据分析任务而创建的。

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
