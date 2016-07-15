#include "ErayUIHelper.h"
#include "scripting/js-bindings/manual/ScriptingCore.h"
#include "ErayLayer.h"

using namespace cocos2d;

void ErayUIHelper::log(const std::string& value, cocos2d::Node* parent) {
	CCLOG("ErayUIHelper::log:%s",value.c_str());
	auto layer = ErayLayer::create();
	parent->addChild(layer);
	ScriptingCore::getInstance()->evalString("callfromcpp(2,3)");
}