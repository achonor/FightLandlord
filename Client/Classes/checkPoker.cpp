#include "checkPoker.h"

checkPoker::checkPoker() {
}


checkPoker::~checkPoker() {
}


//从有序的字符串中查找数量为num的字符
void checkPoker::findCharByNumber(char *retStr, std::string &srcStr, int num) {
	int retNum = 0;
	int maxNumber = 1;
	for (int i = 0; i < srcStr.size(); i++) {
		if (0 < i && srcStr[i - 1] == srcStr[i]) {
			maxNumber++;
		} else {
			maxNumber = 1;
		}
		if (maxNumber == num) {
			retStr[retNum++] = srcStr[i];
		}
	}
	retStr[retNum] = 0;
}

//检测字符串中的字符是否连续
bool  checkPoker::checkCharIsConnect(const char *str) {
	int len = strlen(str);
	for (int i = 1; i < len; i++) {
		if ('9' == str[i - 1] && 'a' == str[i]) {
			//特殊情况
			continue;
		}
		if (str[i - 1] != (str[i] - 1)) {
			return false;
		}
	}
	return true;
}

//检测牌的类型
checkResult checkPoker::checkType(std::string &pokerList) {
	checkResult ret;
	int pokerNum = pokerList.size();
	if (0 == pokerNum) {
		ret = checkResult(pokerType::illegal);
		return ret;
	}
	//判断王炸
	if (2 == pokerNum && strcmp("gg", pokerList.c_str()) == 0) {
		ret = checkResult(pokerType::rocket, 'g');
		return ret;
	}
	//将字符串排序
	sort(pokerList.begin(), pokerList.end());
	//依次判断是否是包含相同的4个，3个，2个， 1个牌
	char retStr[15];
	for (int i = 4; i > 0; i--) {
		findCharByNumber(retStr, pokerList, i);
		//有多少个数大于i的牌
		int connectNum = strlen(retStr);
		if (0 == connectNum) {
			//没有结果
			continue;
		}
		if (false == checkCharIsConnect(retStr)) {
			//不连续的不合法
			continue;
		}
		if (connectNum * mostTake[i] < pokerNum - connectNum * i) {
			//带的牌太多了
			continue;
		}
		/////////////下面判读细节
		if (4 == i) {
			//如果只有4个牌那么就是炸弹
			ret = checkResult((4 == pokerNum) ? pokerType::bomb : pokerType::four, retStr[connectNum - 1]);
			return ret;
		} else if (3 == i) {
			int lastPokerNum = pokerNum - connectNum * i;
			if (0 != lastPokerNum && lastPokerNum != connectNum && lastPokerNum != (connectNum << 1)) {
				//3只能带1个或者1对
				continue;
			} else if (0 == lastPokerNum || lastPokerNum == connectNum) {
				//三带一或者不带的情况
				ret = checkResult(pokerType::three, retStr[connectNum - 1]);
				return ret;
			} else {
				char tmpChar[15];
				findCharByNumber(tmpChar, pokerList, 2);
				if (strlen(tmpChar) == (connectNum << 1)) {
					//三带一对的情况
					ret = checkResult(pokerType::three, retStr[connectNum - 1]);
					return ret;
				}
				//有单牌，不合法
				continue;
			}
		} else if (2 == i) {
			if (1 == connectNum || 3 <= connectNum) {
				//一对，或者三连对以上
				ret = checkResult(pokerType::couple, retStr[connectNum - 1]);
				return ret;
			}
		} else if (1 == i) {
			if (1 == connectNum || 5 <= connectNum) {
				//单牌或者顺子
				ret = checkResult(pokerType::single, retStr[connectNum - 1]);
				return ret;
			}
		}
	}
	ret = checkResult(pokerType::illegal);
	return ret;
}

//判断牌的大小
bool checkPoker::pokerCmp(std::string &a, std::string &b) {
	int alen = a.size();
	int blen = b.size();
	checkResult aRet = checkType(a);
	checkResult bRet = checkType(b);
	if (pokerType::rocket == aRet.pType || pokerType::rocket == bRet.pType) {
		//有火箭
		return pokerType::rocket == aRet.pType;
	} else if (pokerType::bomb == aRet.pType && pokerType::bomb == bRet.pType) {
		//都是炸弹
		return bRet.maxChar < aRet.maxChar;
	} else if (pokerType::bomb == aRet.pType || pokerType::bomb == bRet.pType) {
		//有一个有炸弹
		return pokerType::bomb == aRet.pType;
	}
	if (0 == b.length()) {
		return pokerType::illegal != aRet.pType;
	}
	if (alen != blen) {
		//牌数量不相等
		return false;
	}
	if (aRet.pType == bRet.pType) {
		//类型相同
		return bRet.maxChar < aRet.maxChar;
	}
	return false;
}