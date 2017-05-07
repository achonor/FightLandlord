#include "UIPanel.h"



UIPanel::UIPanel(){
}


UIPanel::~UIPanel() {
}

bool UIPanel::init() {
	//»ÒÉ«±³¾°
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 120))){
		return false;
	}

	return true;
}
