#include "stdafx.h"
#include "functions.h"

using namespace std;
USING_NS_CC;


//����json�ļ�
rapidjson::Document My_getJsonData(const char* fileName) {
	//[1] ��ȡjson�ļ�����
	Data tmpData = FileUtils::getInstance()->getDataFromFile(fileName);
	char tStr[2048];
	strcpy(tStr, (char *)tmpData.getBytes());
	tStr[tmpData.getSize()] = '\0';

	//[2] �������ڴ���json�������
	// ����rapidjson::Document�ࣺ���ڲ���json����
	rapidjson::Document d;

	//[3] ����json�ļ�����
	// ���� rapidjson::kParseDefaultFlags = 0��Ĭ�Ϸ�ʽ
	d.Parse<rapidjson::kParseDefaultFlags>(tStr);
	// d.Parse<0>(str.c_str());  // Ҳ����ֱ��д<0>

	//[4] �жϽ����Ƿ����
	if (d.HasParseError()) {
		cerr << "GetParseError " << d.GetParseError() << endl;
		//return NULL;
	}
	return d;
}

//