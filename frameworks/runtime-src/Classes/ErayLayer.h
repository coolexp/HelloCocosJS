#pragma once
#include "cocos2d.h"

class ErayDelegate:public cocos2d::Ref {
public:
	virtual void onClick(const std::string& value) {};
	virtual ~ErayDelegate() {};
};

class ErayLayer :public cocos2d::Layer {
public:
	ErayLayer();
	~ErayLayer();
	virtual bool init();
	CREATE_FUNC(ErayLayer);
	void setDelegate(ErayDelegate* _delegate);
private:
	ErayDelegate* m_pDelegate;
};