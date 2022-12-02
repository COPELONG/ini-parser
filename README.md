# ini-parser
# INI文件解析器

## 所用知识点

1.运算符重载

2.文件操作

3.函数重载

4.构造函数重载

5.面向对象设计

## 零碎知识点

1.将int、double等类型转换为string：使用字节流转化

```c++
    int value = 1
    stringstream ss;
	ss << value;
	m_value = ss.str();
```

2.将string转化为int、double等：

```c++
string m_value;
atoi(m_value.c_str());//先转化为c类型的字符串才能使用atoi将stirng转化为int类型
```

3.根据ini文件数据存储方式设计合适数据结构

```c++
//大map集合嵌套小map集合
typedef map<string, Value> Section;
map<string, Section> m_sections;
//map集合访问元素
m_sections[key] = Section();
m_sections[section][key] = value;
//读取的value是string类型，往Section里存的是Value类型
//可以理解成自动转化为Value v = value;对应1.2功能。
```



## 功能模块

### 1.创建Value类：

用来控制各种类型的值，并且能够进行赋值等操作。

1.1 设计能接收ini文件中各种类型的Value值的构造函数

1.2 设计重载=运算符，能够实现Value v = 1或者其他类型；

1.3 设计类转化为内置数据类型，能够实现 int i = v；

```c++
value v(1);
int i = v；
operator int(){
    return m_value//根据其类型返回，详细看代码
}
```
 ![image]([https://github.com/591774192/MerlandTrade/blob/master/%E6%A2%85%E5%85%B0%E5%95%86%E8%B4%B8%E6%88%AA%E5%9B%BE.png](https://github.com/COPELONG/ini-parser/blob/master/image-1.png))

### 2.创建IniFile类：

读取ini文件数据进行一系列操作。

2.1 设计读取ini文件load函数：读取数据存储到map集合中。

2.2 设计trim函数：对string字符串中的空格删除。

2.3 设计重载数组[]运算符，返回值由嵌套内map接收：目的为了访问value值。

```c++
    IniFile f;
	f.load("pid.ini");
	int i = f["id"]["ID"];//访问文件头section为id的key为ID的value。f["id"]返回的是嵌套内map：map[ID]=？

//f["id"]["ID"]返回值是Value类型，因为功能1.3中已经重载，故可以转化成int类型。
```

2.4 设计set函数：可以添加数据，接受第三个参数设置为Value类型，因为已经重载运算符（功能1.2：将内置数据类型转化为Value类型）

```c++
set(const string& section, const string& key, const Value& value);
```

2.5 设计has函数：判断是否存在section和key。

2.6 设计remove函数：删除对应的key值。

2.7 设计str()函数：遍历所有数据存入string流中，便于输出数据和保存数据。

2.8 设计show函数：调用str()，输出所有ini文件里的数据。

2.9 设计save函数：保存文件。

![image-20221201233840039](C:\Users\51644\AppData\Roaming\Typora\typora-user-images\image-20221201233840039.png)
