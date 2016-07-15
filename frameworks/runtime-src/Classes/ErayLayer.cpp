#include "ErayLayer.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;

ErayLayer::ErayLayer() {

}

bool ErayLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	ImageView* image = ImageView::create();
	image->loadTexture("res/diamond3.png");
	image->setTouchEnabled(true);
	image->addTouchEventListener([=](Ref *pSender, ui::Widget::TouchEventType type) {
		if (type != ui::Widget::TouchEventType::ENDED)
			return;
		CCLOG("click on Image");
	});
	image->setPosition(Vec2(300.0f, 300.0f));
	addChild(image);
	return true;
}