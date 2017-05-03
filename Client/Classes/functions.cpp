#include "stdafx.h"
#include "functions.h"

using namespace std;
USING_NS_CC;


//解析json文件
rapidjson::Document My_getJsonData(const char* fileName) {
	//[1] 读取json文件内容
	Data tmpData = FileUtils::getInstance()->getDataFromFile(fileName);
	char tStr[2048];
	strcpy(tStr, (char *)tmpData.getBytes());
	tStr[tmpData.getSize()] = '\0';

	//[2] 创建用于处理json代码的类
	// 创建rapidjson::Document类：用于操作json代码
	rapidjson::Document d;

	//[3] 解析json文件内容
	// 其中 rapidjson::kParseDefaultFlags = 0，默认方式
	d.Parse<rapidjson::kParseDefaultFlags>(tStr);
	// d.Parse<0>(str.c_str());  // 也可以直接写<0>

	//[4] 判断解析是否出错
	if (d.HasParseError()) {
		cerr << "GetParseError " << d.GetParseError() << endl;
		return NULL;
	}
	return d;
}

int My_char4ToInt(const char *data) {
	int ret = 0;
	int idx = -1;
	while (data[idx]) {
		ret = (ret << 8) | int(data[idx]);
	}
	return ret;
}

//