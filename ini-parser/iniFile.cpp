#include "iniFile.h"

Value::Value() {
	
}
Value::Value(bool value) {
	 *this = value;
}
Value::Value(int value) {
	 *this = value;
}
Value::Value(double value) {
	*this = value;
}
Value::Value(const string& value){
	*this = value;
}

Value::Value(const char* value){
	*this = value;
}
Value&  Value::operator=(bool value) {
	m_value = value?"true":"false";
	return* this;
}
Value& Value::operator=(int value) {
	stringstream ss;
	ss << value;
	m_value = ss.str();
	return*this;
}
Value& Value::operator=(double value) {
	stringstream ss;
	ss << value;
	m_value = ss.str();
	return*this;
}
Value& Value::operator=(const string& value) {
	m_value = value;
	return*this;
}
Value& Value::operator=(const char* value) {
	m_value = value;
	return*this;
}
Value::operator bool() {
	return m_value == "true";
}
Value::operator int() {
	return atoi(m_value.c_str());//��ת��Ϊc���͵��ַ�������ʹ��atoi��stirngת��Ϊint����
}
Value::operator double() {
	return atof(m_value.c_str());
}
Value::operator string() {
	return m_value;
}
bool IniFile::load(const string& filename) {
	m_filename = filename;
	ifstream fin(filename);
	if (!fin.is_open()) {
		cout << "�Ҳ����ļ����ʧ��" << endl;
		return false;
	}
	string line;
	string section;
	while (getline(fin, line) ){
		if (line == "") {
			continue;
		}
		if (line[0] == '[') {
			section=line.substr(1,line.find(']')-1);
			trim(section);
			m_sections[section] = Section();
		}
		else {
			line.find('=');
			string key = line.substr(0, line.find('='));
			trim(key);
			string value = line.substr(line.find('=')+1);
			trim(value);
			m_sections[section][key] = value;
		}
	}
	fin.close();
	return true;
}
Section& IniFile::operator[](const string& section) {
	return m_sections[section];
}
void IniFile::set(const string& section, const string& key, const Value& value) {
	if (!has(section, key)) {
		m_sections[section][key] = value;
		cout << "��ӳɹ�" << endl;
	}else {
			cout << "�Ѿ�������ͬkey�������ظ����" << endl;
		}
	}
	

bool IniFile::has(const string& section, const string& key) {
	auto it = m_sections.find(section);
	if (it != m_sections.end()) {
		auto itt1 = it->second.find(key);
		auto itt2 = it->second.end();
		if (itt1 != itt2) {
			return true;
		}
	}
	return false;
}
void IniFile::remove(const string& section, const string& key) {
	if (has(section, key)) {
		auto it = m_sections.find(section);
		it->second.erase(key);//��ȡmap���ϣ�ֱ��ɾ�����ɡ�
		cout << "ɾ���ɹ�" << endl;
	}
	else {
		cout << "û�ж�Ӧ��keyֵ��ɾ��ʧ��" << endl;
	}
}
void IniFile::remove(const string& section) {
	auto it = m_sections.find(section);
	if (it != m_sections.end()) {
     m_sections.erase(section);
	 cout << "ɾ���ɹ�" << endl;
	}
	cout << "ɾ��ʧ��" << endl;
}
void IniFile::clear() {
	m_sections.clear();
	cout << "����������ݳɹ�" << endl;
}
string IniFile::getstr() {
	stringstream ss;
	auto it = m_sections.begin();
	auto it1 = m_sections.end();
	for (it; it != it1; it++) {
		ss << "[" << it->first << "]" << endl;
		auto it2 = it->second.begin();
		auto it3 = it->second.end();
		for (it2; it2 != it3; it2++) {
			ss << it2->first << "=" << string(it2->second) << endl;
		}
		ss << endl;
	}
		return ss.str();
	}

void IniFile::show() {
	cout << "������������" << endl;
	cout << getstr();
}
bool IniFile::save(const string& filename) {
	ofstream fout(filename);
	if (fout.fail()) {
		return false;
	}
	fout << getstr();
	fout.close();
	return true;
}
string IniFile::trim(string& s) {
	if (s.empty()) {
		return 0;
	}
	s.erase(0, s.find_first_not_of(" /n/r"));
	s.erase(s.find_last_not_of(" /n/r")+1);
	return s;

}