
# ezJSON
<font color=#999AAA >C语言下的人性化、轻量级、高性能JSON库

<hr style=" border:solid; width:100px; height:1px;" color=#000000 size=1">

># 性能测试
<font color=#999AAA >这里使用目前主流的C语言JSON库 “cJSON” 对比测试基本的数据构建与解析。

## 测试数据：
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


## 构建JSON示例

```
	ezJSON(string)
	{
	    STR("school", "Guangdong University Of Petrochemical Technology");
	    STR("location", "Maoming");
	    NUM("ranking", 505);
	    NUM("area", 2020.643);
	    OBJ("student")
	    {
	        STR("name", "zhoutianhao");
	        NUM("age", 23);
	        ARR("grades", 3)
	        {
	            NUM(NULL, grades[_IDX]);
	        }}
	        BOL("office", 1);
	        ARR("exp", 2) {OBJ(NULL)
	        {
	            STR("address", address[_IDX]);
	            NUM("date", date[_IDX]);
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
