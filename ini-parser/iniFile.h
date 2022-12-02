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
	Value(const string& value);//c++�ַ���
	Value(const char* value);//c���Է���ַ���
	//����=�����:V v = 1....
	Value& operator=(bool value);
	Value& operator=(int value);
	Value& operator=(double value);
	Value& operator=(const string& value);
	Value& operator=(const char* value);
	//����=��������������ת��Ϊ�����������ͣ�����int i = v;
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
	bool load(const string& filename);//����ini�ļ�����ȡ���ݴ洢��map��
	string trim(string& s);//�����ַ����Ŀո�
	Section& operator[](const string& section);//�������������
	void set(const string& section,const string &key, const Value& value);//���ļ����ݽ������
	bool has(const string& section, const string& key);//�ж��Ƿ����keyֵ
	void remove(const string& section, const string& key);//ɾ��ָ��key
	void remove(const string& section);//ɾ��ָ��ͷ
	void clear();//�����������
	void show();//չʾ��������
	string getstr();//�������ݴ���string���С�
	bool save(const string& filename);//�����ļ�
private:
	string m_filename;
	map<string, Section> m_sections;

};