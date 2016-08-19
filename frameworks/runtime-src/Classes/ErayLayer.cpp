#include "ErayLayer.h"
#include "ui/CocosGUI.h"
#include "scripting/js-bindings/manual/ScriptingCore.h"

using namespace cocos2d;
using namespace cocos2d::ui;

ErayLayer::ErayLayer() {
	m_pDelegate = nullptr;
}
ErayLayer::~ErayLayer() {
	CC_SAFE_RELEASE(m_pDelegate);
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
		if (m_pDelegate) {
			m_pDelegate->onClick("call from cpp");
		}
		CCLOG("click on Image");
	});
	image->setPosition(Vec2(300.0f, 300.0f));
	addChild(image);
	return true;
}

void ErayLayer::setDelegate(ErayDelegate* _delegate) {
	if (_delegate) {
		m_pDelegate = _delegate;
		m_pDelegate->retain();
	}
}