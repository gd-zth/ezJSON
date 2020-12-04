
# ezJSON
<font color=#999AAA >C语言下的人性化、轻量级、高性能JSON库
<hr style=" border:solid; width:100px; height:1px;" color=#000000 size=1">

# 性能测试
<font color=#999AAA >这里使用目前主流的C语言JSON库 “cJSON” 对比测试基本的数据构建与解析。

## 测试内容
<font color=#999AAA >构建与解析目标：
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
<font color=#999AAA >解析存储的数据：
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
  } INFO;
```
<font color=#999AAA >构建引用的数据：
```
  char    school[]    = "Guangdong University Of Petrochemical Technology";
  char    location[]  = "Maoming";
  float   ranking     = 505;
  float   area        = 2020.643;
  char    student_name[]      = "zhoutianhao";
  float   student_age         = 23;
  float   student_grades[]    = {97, 62, 84};
  int     student_office      = 1;
  char*   student_exp_address[]   = {"Guangdong", "Chengdu"};
  float   student_exp_date[]      = {1906, 1910};
```

## 通过cJSON构建
代码如下（示例）：
```
  cJSON *info = cJSON_CreateObject();
  cJSON_AddStringToObject(info, "school", school);
  cJSON_AddStringToObject(info, "location", location);
  cJSON_AddNumberToObject(info, "ranking", ranking);
  cJSON_AddNumberToObject(info, "area", area);

  cJSON *student = cJSON_CreateObject();
  cJSON_AddStringToObject(student, "name", student_name);
  cJSON_AddNumberToObject(student, "age", student_age);

  cJSON *grades = cJSON_CreateFloatArray(student_grades, 3);
  cJSON_AddItemToObject(student, "grades", grades);

  cJSON_AddBoolToObject(student, "office", student_office);

  cJSON *exp = cJSON_CreateArray();
  for (int idx = 0; idx <2 ; idx ++) 
  {
      cJSON *expItem = cJSON_CreateObject();
      cJSON_AddStringToObject(expItem, "address", student_exp_address[idx]);
      cJSON_AddNumberToObject(expItem, "date", student_exp_date[idx]);
      cJSON_AddItemToArray(exp, expItem);
  }
  cJSON_AddItemToObject(student, "exp", exp);

  cJSON_AddItemToObject(info, "student", student);

  cJSON_Delete(info);
```

## 通过ezJSON构建
代码如下（示例）：
```
  ezJSON(string)
  {
      STR("school",   school);
      STR("location", location);
      NUM("ranking",  ranking);
      NUM("area",     area);
      OBJ("student")
      {
          STR("name", student_name);
          NUM("age",  student_age);
          ARR("grades", 3)
          {
              NUM(NULL, grades[_IDX]);
          }}
          BOL("office", student_office);
          ARR("exp", 2) {OBJ(NULL)
          {
              STR("address",  student_exp_address[_IDX]);
              NUM("date",     student_exp_date[_IDX]);
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
