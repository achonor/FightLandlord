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
	for (int i = 0; i < 4; i++){
		ret = (ret << 8) | int(data[i]);
	}
	return ret;
}

void My_intToChar4(char* chr, int num) {
	for (int i = 3; i >= 0; i--) {
		int tmpInt = ((255 << (8 * i))) & num;
		chr[3 - i] = tmpInt;
	}
	chr[4] = '\0';
}

std::string My_charToString(const char* sChr, int sLen) {
	int cLen = 0;
	std::string retStr;
	while (cLen < sLen) {
		std::string tmpStr(sChr + cLen);
		if (cLen + tmpStr.length() < sLen) {
			tmpStr = tmpStr + '\0';
		}
		cLen = cLen + tmpStr.length();
		retStr = retStr + tmpStr;
	}
	retStr = retStr.substr(0, sLen);
	return retStr;
}

google::protobuf::Message* My_CreateMessage(const std::string& messageName) {
	google::protobuf::Message* message = NULL;
	const google::protobuf::Descriptor* descriptor = google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(messageName);
	if (NULL == descriptor) {
		return message;
	}
	const google::protobuf::Message* prototype = google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
	if (NULL == prototype) {
		return message;
	}
	message = prototype->New();
	return message;
}

std::string My_Serialization(google::protobuf::Message* proto) {
	string protoStr = proto->SerializeAsString();

	//数据长度
	int protoLen = protoStr.length();
	char chr[5];
	My_intToChar4(chr, protoLen);
	//拼接
	protoStr = string(chr, 4) + protoStr;
	return protoStr;
}

//