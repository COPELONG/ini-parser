#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<map>
#include <algorithm>
using namespace std;

class Value {
public:
	Value();
	Value(bool value);
	Value(int value);
	Value(double value);
	Value(const string& value);//c++字符串
	Value(const char* value);//c语言风格字符串
	//重载=运算符:V v = 1....
	Value& operator=(bool value);
	Value& operator=(int value);
	Value& operator=(double value);
	Value& operator=(const string& value);
	Value& operator=(const char* value);
	//重载=运算符：类的类型转换为内置数据类型，比如int i = v;
	operator bool();
	operator int();
	operator double();
	operator string();
	
private:
	string m_value;
};
typedef map<string, Value> Section;
 
class IniFile {
public:
	IniFile() = default;
	bool load(const string& filename);//解析ini文件：读取数据存储到map中
	string trim(string& s);//消除字符串的空格
	Section& operator[](const string& section);//重载数组运算符
	void set(const string& section,const string &key, const Value& value);//对文件数据进行添加
	bool has(const string& section, const string& key);//判断是否存在key值
	void remove(const string& section, const string& key);//删除指定key
	void remove(const string& section);//删除指定头
	void clear();//清空所有数据
	void show();//展示所有数据
	string getstr();//遍历数据存入string流中。
	bool save(const string& filename);//保存文件
private:
	string m_filename;
	map<string, Section> m_sections;

};