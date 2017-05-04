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
		chr[i] = tmpInt;
	}
	chr[4] = '\0';
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

	//���ݳ���
	int protoLen = protoStr.length();
	char chr[5];
	My_intToChar4(chr, protoLen);
	//ƴ��
	protoStr = string(chr) + protoStr;
	return protoStr;
}

//