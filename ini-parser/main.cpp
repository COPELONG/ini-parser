#include<iostream>
using namespace std;
#include "iniFile.h"




int main() {
	IniFile f;
	int i = 0;
	f.load("test.ini");
	f.show();
	f.set("id", "cardID", 123456789);
	int cardid = f["id"]["cardid"];
	f.has("id", "cardid");
	f.remove("id", "cardid");
	f.save("pid.ini");
	

}
