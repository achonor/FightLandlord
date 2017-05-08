#include "GGData.h"
#include "UIMessageBox.h"
#include "ui/UIButton.h"

using namespace ui;

My_MessageBox::My_MessageBox() {
	this->textLabel = NULL;
	this->callback = NULL;
}


My_MessageBox::~My_MessageBox() {
}


My_MessageBox* My_MessageBox::create(const std::string &text, function<void(CLICKTYPE cType)> call) {
	My_MessageBox* retNode = My_MessageBox::create();
	retNode->setText(text);
	retNode->setCallback(call);
	return retNode;
}

bool My_MessageBox::init() {
	if (!UIPanel::init()) {
		return false;
	}

	//添加背景
	auto backSp = Sprite::create("messageBox.png");
	backSp->setPosition(Vec2(My_visibleSize.width * 0.5, My_visibleSize.height * 0.5));
	this->addChild(backSp);
	//添加Label
	this->textLabel = Label::create("", "fonts/My_font.ttf", 22);
	this->textLabel->setPosition(Vec2(220, 120));
	this->textLabel->setColor(ccc3(0, 0, 0));
	this->textLabel->setDimensions(220, 80);
	backSp->addChild(this->textLabel);
	//关闭按钮
	auto closeButton = ui::Button::create("close.png");
	closeButton->setPosition(Vec2(320, 200));
	closeButton->setAnchorPoint(Vec2(0.5, 0.5));
	backSp->addChild(closeButton);
	closeButton->addTouchEventListener([&](Ref* node, ui::Widget::TouchEventType tType) {
		if (tType == Widget::TouchEventType::ENDED) {
			this->_callBacck(CLICKTYPE::CLOSE);
		}
	});
	//确认按钮
	auto yesButton = ui::Button::create("yes_button.png");
	yesButton->setPosition(Vec2(91, 35));
	yesButton->setAnchorPoint(Vec2(0.5, 0.5));
	backSp->addChild(yesButton);
	yesButton->addTouchEventListener([&](Ref* node, ui::Widget::TouchEventType tType) {
		if (tType == Widget::TouchEventType::ENDED) {
			this->_callBacck(CLICKTYPE::YES);
		}
	});
	//取消按钮
	auto cancelButton = ui::Button::create("cancel_button.png");
	cancelButton->setPosition(Vec2(267, 35));
	cancelButton->setAnchorPoint(Vec2(0.5, 0.5));
	backSp->addChild(cancelButton);
	cancelButton->addTouchEventListener([&](Ref* node, ui::Widget::TouchEventType tType) {
		if (tType == Widget::TouchEventType::ENDED) {
			this->_callBacck(CLICKTYPE::CANCEL);
		}
	});

	return true;
}

void My_MessageBox::setText(const std::string &text) {
	if (NULL == this->textLabel) {
		cerr << "ERROR: textLabel is NULL!" << endl;
		return;
	}
	this->textLabel->setString(text);
}

void My_MessageBox::setCallback(function<void(CLICKTYPE cType)> call) {
	this->callback = call;
}

void My_MessageBox::_callBacck(CLICKTYPE cType) {
	if (NULL == this->callback) {
		return;
	}
	auto tmpCallBack = this->callback;
	My_gameScene->popPanel();
	tmpCallBack(cType);
}